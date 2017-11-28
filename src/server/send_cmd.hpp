#pragma once

#include "server_log.hpp"
#include "database.hpp"

#define USERID_HOST 311

#define SVHELP_HIDDEN 0

typedef int (*mfmSvCommand)(LPCSTR, int, int);

struct CommandInfo
{
	mfmSvCommand funcPtr;
	int helpID;
	int permissions;
};

extern std::map<std::string, CommandInfo> commands;

void RegisterCommand(LPCSTR name, mfmSvCommand func, int helpID, int perm);
void SendServerCommand(LPCWSTR cmd, int cmdsize, int UserID);
void SendServerCommand(LPCSTR cmd, int cmdsize, int UserID);
