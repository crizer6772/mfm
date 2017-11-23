#include "clientsession.hpp"
#include "server_log.hpp"

unsigned int __stdcall ClientSession(void* socket)
{
    SOCKET s = *(unsigned int*)(socket);
	ServerLog("new connection");
}
