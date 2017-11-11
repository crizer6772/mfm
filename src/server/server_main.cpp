#include "server_main.hpp"
#include "log_window.hpp"
#include "server_log.hpp"
#include "send_cmd.hpp"
#include "commands.hpp"

#include "../shared/wcreate.hpp"
#include "../shared/wcreg.hpp"

SERVER_GUI ServerGUI;
unsigned int __stdcall ServerMain(void* param)
{
	int w = SVW_DEFAULT_WINDOW_WIDTH;
	int h = SVW_DEFAULT_WINDOW_HEIGHT;
	int lw = w-SVW_SIDEBAR_HEADROOM_H-SVW_LOGBOX_OFFSET;
	int lh = w-SVW_SIDEBAR_HEADROOM_V-SVW_LOGBOX_OFFSET;
	int lbOffset = SVW_LOGBOX_OFFSET;
	int svLogBoxStyle =  WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY;
	int svCmdLineStyle = WS_CHILD | WS_VISIBLE | WS_BORDER;
	MSG msg;

	//initializing shit
	RegisterRegularWindowClass(TEXT("ServerWindow"), WndProc_ServerWindow, NULL);
	HFONT DefaultFont =(HFONT)GetStockObject(DEFAULT_GUI_FONT);

	//window&control creation
	ServerGUI.MainWindow = CreateRegularWindow(NULL, TEXT("ServerWindow"), TEXT("MFM Server"), w, h, MFM_WINDOWTYPE_RESIZABLE);
	ServerGUI.LogWindow = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), NULL, svLogBoxStyle, lbOffset, lbOffset, 280, 200, ServerGUI.MainWindow, NULL, NULL, NULL);
	ServerGUI.CommandLine = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), NULL, svCmdLineStyle, lbOffset+lw, lbOffset+lh, lw, 20, ServerGUI.MainWindow, NULL, NULL, NULL);

	//setting shit up
	SetWindowText(ServerGUI.LogWindow, TEXT("console log test"));
	SendMessage(ServerGUI.LogWindow, WM_SETFONT,(WPARAM)DefaultFont, 0);
	SendMessage(ServerGUI.CommandLine, WM_SETFONT,(WPARAM)DefaultFont, 0);

	ShowWindow(ServerGUI.MainWindow, 10);
	UpdateWindow(ServerGUI.MainWindow);

	defEditWndProc = (WNDPROC)SetWindowLongPtr(ServerGUI.CommandLine, GWLP_WNDPROC, (LONG_PTR)sCmdLine_WndProc);


    //initializing server log
	InitServerLog(32768);
	ServerLog("MFM Server v0.311");
	ServerLog("Enter 'help' to list available commands.");

    //registering server commands
    RegisterCommand("help", cServerHelp, SVHELP_HELP, PERM_HOSTONLY);
    RegisterCommand("kick", cKickUser, SVHELP_KICK, PERM_ADMIN);
    RegisterCommand("exec", cExecFile, SVHELP_EXEC, PERM_HOSTONLY);
    RegisterCommand("fuck", cFuckYou, SVHELP_HIDDEN, PERM_HOSTONLY);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)(msg.wParam);
}
