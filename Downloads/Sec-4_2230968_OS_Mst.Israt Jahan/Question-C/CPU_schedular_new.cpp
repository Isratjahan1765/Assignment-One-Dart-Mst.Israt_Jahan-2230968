#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// -------------------------
// Process struct
// -------------------------
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int startTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;

    Process(int i, int a, int b, int p) {
        id = i;
        arrivalTime = a;
        burstTime = b;
        remainingTime = b;
        priority = p;
        startTime = -1;
        completionTime = -1;
        waitingTime = 0;
        turnaroundTime = 0;
        responseTime = -1;
    }
};

// Comparator for Priority Queue (Q1)
struct ComparePriority {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.priority > p2.priority; // lower numeric value = higher priority
    }
};

int main() {
    int numProcesses;
    cout << "Enter number of processes: ";
    cin >> numProcesses;

    vector<Process> allProcesses;

    // -------------------------
    // Input process details
    // -------------------------
    for (int i = 0; i < numProcesses; ++i) {
        int arrival, burst, priority;
        cout << "Process " << i+1 << " arrival time: ";
        cin >> arrival;
        cout << "Process " << i+1 << " burst time: ";
        cin >> burst;
        cout << "Process " << i+1 << " priority (1=high, 2=medium, 3=low): ";
        cin >> priority;
        allProcesses.push_back(Process(i+1, arrival, burst, priority));
    }

    // -------------------------
    // Queues
    // -------------------------
    priority_queue<Process, vector<Process>, ComparePriority> q1_priority;
    queue<Process> q2_round_robin;
    queue<Process> q3_fifo;
    vector<Process> completedProcesses;

    int currentTime = 0;
    int cpuTimeUsed = 0; // For CPU utilization

    // -------------------------
    // Main scheduling loop
    // -------------------------
    while ((int)completedProcesses.size() < numProcesses) {

        // Step 1: Handle arrivals
        for (size_t i = 0; i < allProcesses.size(); ++i) {
            Process &p = allProcesses[i];
            if (p.arrivalTime == currentTime && p.remainingTime > 0) {
                if (p.priority == 1)
                    q1_priority.push(p);
                else if (p.priority == 2)
                    q2_round_robin.push(p);
                else
                    q3_fifo.push(p);

                cout << "Time " << currentTime << ": Process " << p.id
                     << " arrived (Priority " << p.priority << ")\n";
            }
        }

        // Step 2: Select next process
        Process currentProcess(0,0,0,0);
        bool processRunning = false;

        if (!q1_priority.empty()) {
            currentProcess = q1_priority.top();
            q1_priority.pop();
            processRunning = true;
        } else if (!q2_round_robin.empty()) {
            currentProcess = q2_round_robin.front();
            q2_round_robin.pop();
            processRunning = true;
        } else if (!q3_fifo.empty()) {
            currentProcess = q3_fifo.front();
            q3_fifo.pop();
            processRunning = true;
        }

        // Step 3: Execute process for 1 time unit
        if (processRunning) {
            cpuTimeUsed++;

            if (currentProcess.startTime == -1)
                currentProcess.startTime = currentTime;
            if (currentProcess.responseTime == -1)
                currentProcess.responseTime = currentTime - currentProcess.arrivalTime;

            currentProcess.remainingTime -= 1;
            cout << "Time " << currentTime << ": Running Process " << currentProcess.id << "\n";

            if (currentProcess.remainingTime == 0) {
                currentProcess.completionTime = currentTime + 1;
                currentProcess.turnaroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
                completedProcesses.push_back(currentProcess);

                cout << "Time " << currentTime+1 << ": Process " << currentProcess.id << " completed\n";
            } else {
                // Put back into appropriate queue
                if (currentProcess.priority == 1)
                    q1_priority.push(currentProcess);
                else if (currentProcess.priority == 2)
                    q2_round_robin.push(currentProcess);
                else
                    q3_fifo.push(currentProcess);
            }
        } else {
            cout << "Time " << currentTime << ": CPU Idle\n";
        }

        currentTime++;
    }

    // -------------------------
    // Calculate performance metrics
    // -------------------------
    double totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;

    for (size_t i = 0; i < completedProcesses.size(); ++i) {
        totalTurnaround += completedProcesses[i].turnaroundTime;
        totalWaiting += completedProcesses[i].waitingTime;
        totalResponse += completedProcesses[i].responseTime;
    }

    double avgTurnaroundTime = totalTurnaround / numProcesses;
    double avgWaitingTime = totalWaiting / numProcesses;
    double avgResponseTime = totalResponse / numProcesses;
    double cpuUtilization = (cpuTimeUsed * 100.0) / currentTime;
    double throughput = numProcesses / (double)currentTime;

    // -------------------------
    // Print final table
    // -------------------------
    cout << "\nProcess\tArrival\tBurst\tStart\tCompletion\tWaiting\tTurnaround\tResponse\n";
    for (size_t i = 0; i < completedProcesses.size(); ++i) {
        Process &p = completedProcesses[i];
        cout << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime
             << "\t" << p.startTime << "\t" << p.completionTime
             << "\t\t" << p.waitingTime << "\t" << p.turnaroundTime
             << "\t\t" << p.responseTime << "\n";
    }

    // -------------------------
    // Print performance metrics
    // -------------------------
    cout << "\n--- Performance Metrics ---\n";
    cout << "Total Simulation Time: " << currentTime << "\n";
    cout << "CPU Utilization: " << cpuUtilization << "%\n";
    cout << "Throughput: " << throughput << " processes/time unit\n";
    cout << "Average Turnaround Time: " << avgTurnaroundTime << "\n";
    cout << "Average Waiting Time: " << avgWaitingTime << "\n";
    cout << "Average Response Time: " << avgResponseTime << "\n";

    return 0;
}
