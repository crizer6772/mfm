#pragma once

#include "server_log.hpp"

#define PERM_ADMIN      0x01
#define PERM_USER       0x02
#define PERM_HOSTONLY   0x04
#define PERM_ALL PERM_ADMIN|PERM_USER

#define USERID_HOST 311

#define SVHELP_HIDDEN 0

typedef int (*mfmSvCommand)(LPCSTR, int);

struct CommandInfo
{
    mfmSvCommand funcPtr;
    int helpID;
    int permissions;
};

extern std::map<std::string, CommandInfo> commands;

void RegisterCommand(LPCSTR name, mfmSvCommand func, int helpID, int perm);
void SendServerCommand(LPCWSTR cmd, int UserID);
void SendServerCommand(LPCSTR cmd, int UserID);
