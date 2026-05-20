#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <thread>
#include <mutex>
#include <openssl/md5.h> 
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;


vector<string> fileQueue; 
mutex queueMutex;         
mutex printMutex;         


string calculateMD5(const string& filename) {
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5_CTX ctx;
    MD5_Init(&ctx);

    ifstream file(filename, ios::binary);
    if (!file) return "ACCESS_DENIED";

    char buffer[8192]; 
    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        MD5_Update(&ctx, buffer, file.gcount());
    }
    
    MD5_Final(result, &ctx);

    stringstream ss;
    ss << hex << setfill('0');
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        ss << setw(2) << (int)result[i];
    }
    return ss.str();
}


void worker() {
    while (true) {
        string currentFile;

        
        {
            lock_guard<mutex> lock(queueMutex); 
            if (fileQueue.empty()) {
                return; 
            }
            currentFile = std::move(fileQueue.back());
            fileQueue.pop_back();
        } 

        
        string hash = calculateMD5(currentFile);

        
        {
            lock_guard<mutex> lock(printMutex);
            cout << "[" << hash << "]  " << currentFile << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <directory_path>" << endl;
        return 1;
    }

    string path = argv[1];

    try {
       
        if (fs::exists(path) && fs::is_directory(path)) {
            cout << "Scanning directory, please wait..." << endl;
            for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
                if (fs::is_regular_file(entry)) {
                    fileQueue.push_back(entry.path().string());
                }
            }
        } else {
            cerr << "Error: Invalid directory path." << endl;
            return 1;
        }

        
        unsigned int numThreads = std::thread::hardware_concurrency();
        if (numThreads == 0) numThreads = 8;

        cout << "Found " << fileQueue.size() << " files. Starting " << numThreads << " threads..." << endl;
        cout << "----------------------------------------------------------------------" << endl;

        
        vector<thread> threads;
        for (unsigned int i = 0; i < numThreads; ++i) {
            threads.emplace_back(worker);
        }

        
        for (auto& t : threads) {
            if (t.joinable()) t.join();
        }

        cout << "----------------------------------------------------------------------" << endl;
        cout << "Scan Complete!" << endl;

    } catch (const exception& e) {
        cerr << "System Error: " << e.what() << endl;
    }

    return 0;
}