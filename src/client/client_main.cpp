#include "client_main.hpp"

unsigned int __stdcall ClientMain(void* hostname) //hostname - LPCTSTR
{
	Sleep(86);

	
	if(wcscmp((WCHAR*)hostname, L"fuck you") == 0)
	{
		WCHAR* nsc = new WCHAR[31111];
		LoadString(NULL, IDS_NAVYSEALCP, nsc, 31111);
		MessageBox(NULL, nsc, TEXT("test"), MB_OK | MB_ICONSTOP);
		delete[] nsc;
	}
	else
		MessageBox(NULL, LPCWSTR(hostname), TEXT("test"), MB_OK | MB_ICONINFORMATION);

	return 0;
}