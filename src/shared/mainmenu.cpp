#include "mainmenu.hpp"

HINSTANCE hInst_sf;
char* mfm_cHostname;
int mfmMode;
bool svcmode = false;
const int mmBufSize = 512;

BOOL CALLBACK WndProc_MainMenu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	bool delBuffer = true;
	char* buf = new char[mmBufSize];
	GetDlgItemTextA(hwnd, IDC_MM_IPBOX, buf, mmBufSize);
	HWND hSvcCheckbox = GetDlgItem(hwnd, IDC_MM_SVMODE_CLIENT);
	HWND hHostnameBox = GetDlgItem(hwnd, IDC_MM_IPBOX);
	switch(msg)
	{
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	case WM_COMMAND:
		if(GetAsyncKeyState(VK_RETURN) & 0x8000 && GetFocus() == hHostnameBox && buf[0]!=0)
		{
			if(LOWORD(wParam) != IDC_MM_CONNECT)
			{
				SendMessage(hwnd, WM_COMMAND, IDC_MM_CONNECT, 0);
			}
		}
		switch(LOWORD(wParam))
		{
		case IDC_MM_CONNECT:
			mfm_cHostname = buf;
			mfmMode = MFM_CLIENTMODE;
			delBuffer = false;
			EndDialog(hwnd, 1);
			break;
		case IDC_MM_SVMODE:
			mfmMode = MFM_SVMODE;
			if(svcmode)
				mfmMode = MFM_SVCMODE;
			EndDialog(hwnd, 1);
			break;
		case IDC_MM_SVMODE_CLIENT:
			svcmode = !svcmode;
			//MessageBox(NULL, L"toggled", L"toggled", MB_OK);
		}
		break;
	}
	if(delBuffer)
	{
		delete[] buf;
	}
	return 0;
}
