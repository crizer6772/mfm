#include "wcreg.hpp"

bool RegisterRegularWindowClass(LPCTSTR name, WNDPROC wpPtr, HINSTANCE hInstance)
{

	WNDCLASSEX wc;
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = wpPtr;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground =(HBRUSH)(COLOR_WINDOW);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = name;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		//MessageBox(NULL, L"RegisterClassEx failed", L"somethings fucked up", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	return true;
}