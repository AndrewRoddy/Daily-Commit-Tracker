#include <windows.h>
#include <shellapi.h>
#include <tchar.h>

// Define the unique identifier for the tray icon
#define TRAY_ICON_ID 1001
#define WM_TRAY_ICON_MESSAGE (WM_USER + 1)

// Function prototype for the window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main() {
    // Register a window class
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

    // Load an icon to display in the tray
    //HICON hIcon = LoadIcon(NULL, IDI_APPLICATION); // Default application icon
    //HICON hIcon = LoadIcon(NULL, IDI_APPLICATION); // Default application icon

    // The L beforehand means it is a wide character literal
    // Stored as a wchar_t instead of char
    HICON hIcon = (HICON)LoadImage(NULL, "green_square.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);


    // Set up the NOTIFYICONDATA structure
    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = TRAY_ICON_ID;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.hIcon = hIcon;
    nid.uCallbackMessage = WM_TRAY_ICON_MESSAGE; // Custom message for tray icon events
    _tcscpy_s(nid.szTip, _T("My Tray Icon"));

    // Add the icon to the system tray
    Shell_NotifyIcon(NIM_ADD, &nid);

    // Run a basic message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Remove the icon from the system tray when exiting
    Shell_NotifyIcon(NIM_DELETE, &nid);
    DestroyIcon(hIcon);

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