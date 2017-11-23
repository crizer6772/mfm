#include "listener.hpp"
#include "clientsession.hpp"


unsigned int __stdcall ConnectionListener(void* param)
{
	WSADATA wsaData;
	int res = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(res != NO_ERROR)
	{
		MessageBoxA(NULL, "WSAStartup failed", "error kurwa w chuj", MB_OK|MB_ICONSTOP);
		return 0;
	}
	SOCKET SocketTCP = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sinTCP;
	memset(&sinTCP, 0, sizeof(sockaddr_in));
	sinTCP.sin_family = AF_INET;
	sinTCP.sin_addr.s_addr = INADDR_ANY;
	sinTCP.sin_port = htons(10311);
	SOCKET acceptTCP = SOCKET_ERROR;
	int bResTCP = bind(SocketTCP, (SOCKADDR*)&sinTCP, sizeof(sockaddr_in));
	int lResTCP = listen(SocketTCP, 1);

	if(bResTCP == SOCKET_ERROR)
	{
		MessageBoxA(NULL, "bind() failed", "error kurwa w chuj", MB_OK|MB_ICONSTOP);
		return 0;
	}
	if(lResTCP == SOCKET_ERROR)
	{
		MessageBoxA(NULL, "listen() failed", "error kurwa w chuj", MB_OK|MB_ICONSTOP);
		return 0;
	}

	while(1)
	{
		sockaddr_in clientaddr;
		int ss = sizeof(sockaddr_in);
		acceptTCP = accept(SocketTCP, (SOCKADDR*)&clientaddr, &ss);
		if(acceptTCP != SOCKET_ERROR)
		{
			HANDLE hNewClientSession;
			unsigned int hCSThreadID=0;
			unsigned int fData[2];

			fData[0] = acceptTCP;
			fData[1] = clientaddr.sin_addr.s_addr;
			hNewClientSession = (HANDLE)_beginthreadex(NULL, 0, &ClientSession, (void*)&fData, 0, &hCSThreadID);
			acceptTCP = SOCKET_ERROR;
		}
	}

	WSACleanup();
	return 0;
}
