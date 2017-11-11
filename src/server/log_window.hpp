#pragma once

#include "../stdafx.h"
#include "../resource.h"

#define MFM_SVW_LOGBOX 311
#define MFM_SVW_CMDBOX 312
#define MFM_LOG_BUFFER_SIZE 313

#define MFM_CMD_BUF_SIZE 1024

extern WNDPROC defEditWndProc;

struct SERVER_GUI
{
	HWND MainWindow;
	HWND LogWindow;
	HWND CommandLine;
	HWND PropertiesButton;
};

extern SERVER_GUI ServerGUI;

LRESULT CALLBACK WndProc_ServerWindow(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK sCmdLine_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);