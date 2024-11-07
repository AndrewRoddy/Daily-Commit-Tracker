#include <windows.h>
#include <shellapi.h>
#include <tchar.h>
#include <iostream>
#include <string>

#include "tray.hpp"

int main() {
    WNDCLASS wc = trayStart();
    HWND hwnd = createWindow();
    HICON hIcon = createIcon("green_square.ico");
    NOTIFYICONDATA nid = createData(hwnd, hIcon);

    MSG msg; // Message Loop
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    removeIcon(nid, hIcon);

    return 0;
}
