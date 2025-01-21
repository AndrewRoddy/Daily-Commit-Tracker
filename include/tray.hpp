#pragma once

#ifndef TRAY
#define TRAY

#include <windows.h>
#include <shellapi.h>
#include <tchar.h>
#include <iostream>
#include <string>

// Define the unique identifier for the tray icon
#define TRAY_ICON_ID 1001
#define WM_TRAY_ICON_MESSAGE (WM_USER + 1)

// Function prototype for the window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Runs tray stuff

WNDCLASS trayStart();
HWND createWindow();
HICON createIcon(std::string icon_path);
NOTIFYICONDATA createData(HWND hwnd, HICON hIcon);
void removeIcon(NOTIFYICONDATA nid, HICON hIcon);


#endif