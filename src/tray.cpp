#include <windows.h>
#include <shellapi.h>
#include <tchar.h>
#include <iostream>
#include <string>

#include "..\\include\\tray.hpp"

// Handles when tray icon is clicked/interacted with
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_TRAY_ICON_MESSAGE) { // Checks for mouse stuff
        if (lParam == WM_RBUTTONDOWN) { // Close program if right clicked
            exit(0);
        }
        if (lParam == WM_LBUTTONDOWN) {
            MessageBox(NULL, _T("Tray Icon Left-Clicked!"), _T("Tray Icon"), MB_OK);
        }
    } else if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

WNDCLASS trayStart(){
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = _T("TrayIconClass");  // Using _T macro for compatibility
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, _T("Failed to register window class!"), _T("Error"), MB_OK | MB_ICONERROR);
        exit(0);
    }
    return wc;
}

HWND createWindow(){
    // Create a window to handle tray icon messages
    HWND hwnd_ = CreateWindowEx(
        0, _T("TrayIconClass"), _T("Tray Icon Window"),
        0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    if (!hwnd_) {
        MessageBox(NULL, _T("Failed to create window!"), _T("Error"), MB_OK | MB_ICONERROR);
        exit(0);
    }
    return hwnd_;
}

HICON createIcon(std::string icon_path){
    /*
    Load an icon to display in the tray
    HICON hIcon = LoadIcon(NULL, IDI_APPLICATION); // Default application icon
    HICON hIcon = LoadIcon(NULL, IDI_APPLICATION); // Default application icon

    The L beforehand means it is a wide character literal
    Stored as a wchar_t instead of char
    */
    HICON hIcon = (HICON)LoadImage(NULL, icon_path.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    return hIcon;
}

NOTIFYICONDATA createData(HWND hwnd, HICON hIcon){
    // Set up the NOTIFYICONDATA structure
    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = TRAY_ICON_ID;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.hIcon = hIcon;
    nid.uCallbackMessage = WM_TRAY_ICON_MESSAGE; // Custom message for tray icon events
    _tcscpy_s(nid.szTip, _T("My Tray Icon"));
    Shell_NotifyIcon(NIM_ADD, &nid); // Add the icon to the system tray
    return nid;
}

void removeIcon(NOTIFYICONDATA nid, HICON hIcon){
    // Remove the icon from the system tray when exiting
    Shell_NotifyIcon(NIM_DELETE, &nid);
    DestroyIcon(hIcon);
}
