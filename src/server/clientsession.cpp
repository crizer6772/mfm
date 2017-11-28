#include "clientsession.hpp"
#include "server_log.hpp"
#include "send_cmd.hpp"

unsigned int __stdcall ClientSession(void* data)
{
    SOCKET s = *(SOCKET*)(data);
    in_addr ipAddr = *(in_addr*)(data+sizeof(int));

    char lm[512];
    memset(lm, 0, 512);
    strcat(lm, "new connection from ");
    strcat(lm, inet_ntoa(ipAddr));
	ServerLog(lm);

	while(s != SOCKET_ERROR)
	{
		char cmdbuf[512];
		memset(cmdbuf, 0, 512);
		int size = recv(s, cmdbuf, 512, 0);
		SendServerCommand(cmdbuf, size, USERID_HOST);
	}
}
