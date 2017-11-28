#pragma once

#include "../stdafx.h"

struct ClientSessionInfo
{
	//UserAccount* acc;
	uint32_t address;
	int userID;
	char* token;
	int time; //in seconds
};

/*
COMMAND HEADER:
32 bytes - command ID
4 bytes - length
(command)
*/

unsigned int __stdcall ClientSession(void* data);
