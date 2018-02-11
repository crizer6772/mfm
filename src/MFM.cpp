#include "MFM.h"
#include "shared/wcreg.hpp"
#include "shared/wcreate.hpp"
#include "shared/mainmenu.hpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hInst_sf = hInstance;
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MAINMENU), NULL, WndProc_MainMenu);
	HANDLE hSvThread = NULL;
	HANDLE hClThread = NULL;
	unsigned int ThreadID_SV = 0;
	unsigned int ThreadID_CL = 1;

	WSADATA wsaData;
	int res = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(res != NO_ERROR)
	{
		MessageBoxA(NULL, "WSAStartup failed", "error kurwa w chuj", MB_OK|MB_ICONSTOP);
		return 0;
	}

	char clArg[512];
	if(mfmMode == MFM_CLIENTMODE || mfmMode == MFM_SVCMODE)
	{
		if(mfmMode == MFM_SVCMODE)
		{
			LoadStringA(hInstance, IDS_LOOPBACKIP, clArg, 16);
		}
		else
		{
			strcpy(clArg, mfm_cHostname);
		}
		hClThread = (HANDLE)_beginthreadex(NULL, 0, &ClientMain, (void*)clArg, 0, &ThreadID_CL);
	}
	if(mfmMode == MFM_SVMODE || mfmMode == MFM_SVCMODE)
	{
		hSvThread = (HANDLE)_beginthreadex(NULL, 0, &ServerMain, NULL, 0, &ThreadID_SV);
	}
	if(hSvThread)
		WaitForSingleObject(hSvThread, INFINITE);
	if(hClThread)
		WaitForSingleObject(hClThread, INFINITE);
}
