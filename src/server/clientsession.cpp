#include "clientsession.hpp"
#include "server_log.hpp"

unsigned int __stdcall ClientSession(void* data)
{
    SOCKET s = *(SOCKET*)(socket);
    in_addr ipAddr = *(in_addr*)(data+sizeof(int));

    char lm[512];
    memset(lm, 0, 512);
    strcat(lm, "new connection from ");
    strcat(lm, inet_ntoa(ipAddr));
	ServerLog(lm);
}
