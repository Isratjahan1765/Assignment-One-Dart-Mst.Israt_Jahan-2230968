#include <windows.h>
#include <iostream>
#include <cstring>

using namespace std;

HWND g_hwnd = NULL;
HWND g_nextViewer = NULL;

void sabotageClipboard() {
    if (!OpenClipboard(NULL)) return;
    EmptyClipboard();

    const char* junk = "CLIPBOARD BLOCKED";
    size_t len = strlen(junk) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    if (hMem) {
        char* ptr = (char*)GlobalLock(hMem);
        if (ptr) {
            strcpy(ptr, junk);
            GlobalUnlock(hMem);
            SetClipboardData(CF_TEXT, hMem);
        }
    }
    CloseClipboard();
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            g_nextViewer = SetClipboardViewer(hwnd);
            return 0;

        case WM_CHANGECBCHAIN:
            if ((HWND)wParam == g_nextViewer) {
                g_nextViewer = (HWND)lParam;
            } else if (g_nextViewer) {
                SendMessage(g_nextViewer, msg, wParam, lParam);
            }
            return 0;

        case WM_DRAWCLIPBOARD:
            sabotageClipboard();
            cout << "Clipboard destroyed!" << endl;

            if (g_nextViewer) {
                SendMessage(g_nextViewer, msg, wParam, lParam);
            }
            return 0;

        case WM_DESTROY:
            ChangeClipboardChain(hwnd, g_nextViewer);
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

int main() {
    cout << "Clipboard Annoyer Running...\n";
    cout << "Try copying text.\n";
    cout << "Close the console or kill the process to exit.\n\n";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "ClipboardAnnoyerClass";

    if (!RegisterClass(&wc)) {
        cout << "Failed to register window class.\n";
        return 1;
    }

    g_hwnd = CreateWindow(
        "ClipboardAnnoyerClass",
        "Hidden Clipboard Annoyer",
        WS_OVERLAPPEDWINDOW,
        0, 0, 0, 0,  // size 0x0 to stay hidden
        NULL, NULL,
        GetModuleHandle(NULL),
        NULL
    );

    if (!g_hwnd) {
        cout << "Failed to create window.\n";
        return 1;
    }

    // No ShowWindow needed - remains hidden

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}