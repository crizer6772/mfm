#include "client_main.hpp"

unsigned int __stdcall ClientMain(void* hostname) //hostname - LPSTR
{
	Sleep(86);
	char* c_hostname = (char*)hostname;
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	printf("Connecting to %s... ", (char*)hostname);
	Sleep(200);
	char f_hostname[512];
	memset(f_hostname, 0, 512);
	int fPos = 0;
	for(int i=0; i<strlen(c_hostname); i++)
	{
		if((c_hostname[i] >= '0' && c_hostname[i] <= '9') || c_hostname[i] == '.')
			f_hostname[fPos++] = c_hostname[i];
	}

	SOCKET cs = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sv;
	memset(&sv, 0, sizeof(sockaddr_in));
	sv.sin_family = AF_INET;
	sv.sin_addr.s_addr = inet_addr(f_hostname);
	sv.sin_port = htons(10311);


	if(sv.sin_addr.s_addr == INADDR_NONE || sv.sin_addr.s_addr == INADDR_ANY)
	{
		MessageBoxA(NULL, "invalid address specified", "error", MB_OK);
		return 0;
	}

	if(connect(cs, (SOCKADDR*)&sv, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		MessageBoxA(NULL, "failed to connect", "error", MB_OK);
		return 0;
	}

	printf("connection successful\n");

	return 0;
}
