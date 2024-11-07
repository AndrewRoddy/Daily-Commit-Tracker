#include <windows.h>
#include <shellapi.h>
#include <tchar.h>
#include <iostream>
#include <string>

// I reformatted all of the code to a Class that I can actually use
// After getting the code from the internet
// But it didn't really work when I got it

// Define the unique identifier for the tray icon
#define TRAY_ICON_ID 1001
#define WM_TRAY_ICON_MESSAGE (WM_USER + 1)

// Function prototype for the window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Tray{
    public:
        void start();
        void pickIcon(std::string icon_path);
        void iconSetup();
        void destroy();
    private:
        WNDCLASS wc_;
        HWND hwnd_;
        HICON hIcon_;
        NOTIFYICONDATA nid_;
};

void Tray::start(){
    // Register a window class
    WNDCLASS wc_ = {};
    wc_.lpfnWndProc = WindowProc;
    wc_.hInstance = GetModuleHandle(NULL);
    wc_.lpszClassName = _T("TrayIconClass");  // Using _T macro for compatibility

    if (!RegisterClass(&wc_)) {
        MessageBox(NULL, _T("Failed to register window class!"), _T("Error"), MB_OK | MB_ICONERROR);
        exit(0);
    }

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
}

void Tray::pickIcon(std::string icon_path="green_square.ico"){
    // Load an icon to display in the tray
    //HICON hIcon = LoadIcon(NULL, IDI_APPLICATION); // Default application icon
    //HICON hIcon = LoadIcon(NULL, IDI_APPLICATION); // Default application icon

    // The L beforehand means it is a wide character literal
    // Stored as a wchar_t instead of char

    // Using .c_str() converts the string into a string that can be used with C programs
    hIcon_ = (HICON)LoadImage(NULL, icon_path.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
}

void Tray::iconSetup(){
    // Set up the NOTIFYICONDATA structure
    nid_ = {};
    nid_.cbSize = sizeof(NOTIFYICONDATA);
    nid_.hWnd = hwnd_;
    nid_.uID = TRAY_ICON_ID;
    nid_.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid_.hIcon = hIcon_;
    nid_.uCallbackMessage = WM_TRAY_ICON_MESSAGE; // Custom message for tray icon events
    _tcscpy_s(nid_.szTip, _T("My Tray Icon"));

    // Add the icon to the system tray
    Shell_NotifyIcon(NIM_ADD, &nid_);
}

void Tray::destroy(){
    // Remove the icon from the system tray when exiting
    Shell_NotifyIcon(NIM_DELETE, &nid_);
    DestroyIcon(hIcon_);
}

int main() {
    
    /*
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = _T("TrayIconClass");  // Using _T macro for compatibility

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, _T("Failed to register window class!"), _T("Error"), MB_OK | MB_ICONERROR);
        return 1;
    }

    // Create a window to handle tray icon messages
    HWND hwnd = CreateWindowEx(
        0, _T("TrayIconClass"), _T("Tray Icon Window"),
        0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    if (!hwnd) {
        MessageBox(NULL, _T("Failed to create window!"), _T("Error"), MB_OK | MB_ICONERROR);
        return 1;
    }
    */
    Tray window;
    window.start();
    window.pickIcon("green_square.ico");
    window.iconSetup();

    
    // Run a basic message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    window.destroy();

    return 0;
}

// Window procedure to handle messages for the tray icon
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_TRAY_ICON_MESSAGE) {
        // Check for mouse events on the tray icon
        if (lParam == WM_RBUTTONDOWN) {
            // Display a message box on right-click
            MessageBox(NULL, _T("Tray Icon Right-Clicked!"), _T("Tray Icon"), MB_OK);
        }
    } else if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
