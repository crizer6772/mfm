#include "wcreate.hpp"

HWND CreateRegularWindow(HINSTANCE hInstance, LPCWSTR ClassName, LPCWSTR Caption, int w, int h, int type)
{
	int style = WS_OVERLAPPEDWINDOW;
	if(type == MFM_WINDOWTYPE_DEFAULT)
		style ^= WS_THICKFRAME;
	HWND res = CreateWindowEx(0, ClassName, Caption, style,
		CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, hInstance, NULL);
	if(res == NULL)
	{
		MessageBox(NULL, TEXT("Window creation failed"), TEXT("error"), MB_ICONSTOP);
		exit(1);
	}
	return res;
}
