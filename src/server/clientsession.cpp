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
	int size = 1;
	while(1)
	{
		char cmdbuf[512];
		memset(cmdbuf, 0, 512);
		size = recv(s, cmdbuf, 512, 0);

		if(size == SOCKET_ERROR)
		{
			memset(lm, 0, 512);
			strcat(lm, "connection from ");
			strcat(lm, inet_ntoa(ipAddr));
			strcat(lm, " closed");
			ServerLog(lm);
			break;
		}
		send(s, cmdbuf, 512, 0); //TODO handle partial send()s
		SendServerCommand(cmdbuf, size, USERID_HOST);
	}

	close(s);
}
