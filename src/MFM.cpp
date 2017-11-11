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

	if(mfmMode == MFM_CLIENTMODE || mfmMode == MFM_SVCMODE)
	{
		if(mfmMode == MFM_SVCMODE)
		{
			TCHAR* loopback = new TCHAR[16];
			LoadString(hInstance, IDS_LOOPBACKIP, loopback, 16);
			mfm_cHostname = loopback;
		}
		hClThread = (HANDLE)_beginthreadex(NULL, 0, &ClientMain, (void*)mfm_cHostname, 0, &ThreadID_CL);
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