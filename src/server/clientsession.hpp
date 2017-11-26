#pragma once

#include "../stdafx.h"

struct ClientSessionInfo
{
	//UserAccount* acc;
	int UserID;
	bool LoggedIn;
	char* SessionToken;
	int SessionTime; //in seconds
};

unsigned int __stdcall ClientSession(void* data);
