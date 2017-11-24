#include "log_window.hpp"
#include "server_log.hpp"
#include "server_main.hpp"
#include "send_cmd.hpp"

int wcCounter = 0;
WNDPROC defEditWndProc;
WCHAR* cmdLineBuf;

LRESULT CALLBACK WndProc_ServerWindow(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(!cmdLineBuf)
		cmdLineBuf = new WCHAR[1024];
	GetWindowText(ServerGUI.CommandLine, cmdLineBuf, 1024);
	int nw, nh, lw, lh;
	switch(msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		break;
	case WM_KEYDOWN:
		break;
	case WM_SIZE:
		nw = LOWORD(lParam);
		nh = HIWORD(lParam);
		lw = nw-SVW_SIDEBAR_HEADROOM_H-SVW_LOGBOX_OFFSET;
		lh = nh-SVW_SIDEBAR_HEADROOM_V-SVW_LOGBOX_OFFSET;
		SetWindowPos(ServerGUI.LogWindow, NULL, SVW_LOGBOX_OFFSET, SVW_LOGBOX_OFFSET, lw, lh, 0);
		SetWindowPos(ServerGUI.CommandLine, NULL, SVW_LOGBOX_OFFSET, SVW_LOGBOX_OFFSET+lh, lw, 20, 0);
		//TODO
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK sCmdLine_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WCHAR EmptyStr[2] = {0, 0};
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			SendServerCommand(cmdLineBuf, wcslen(cmdLineBuf), USERID_HOST);
			SetWindowText(ServerGUI.CommandLine, EmptyStr);
			break;
		}
	default:
		return CallWindowProc(defEditWndProc, hwnd, msg, wParam, lParam);
	}
	return 0;
}
