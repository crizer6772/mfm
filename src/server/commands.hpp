#pragma once

#include "../stdafx.h"
#include "send_cmd.hpp"
#include "server_log.hpp"

int cServerHelp(const char* arg, int userID);
int cFuckYou(const char* arg, int userID);
int cKickUser(const char* arg, int userID);
int cExecFile(const char* arg, int userID);

