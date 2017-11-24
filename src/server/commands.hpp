#pragma once

#include "../stdafx.h"
#include "send_cmd.hpp"
#include "server_log.hpp"

int cServerHelp	(const char* arg, int cmdsize, int userID);
int cFuckYou	(const char* arg, int cmdsize, int userID);
int cKickUser	(const char* arg, int cmdsize, int userID);
int cExecFile	(const char* arg, int cmdsize, int userID);
int cClear		(const char* arg, int cmdsize, int userID);
int cCls		(const char* arg, int cmdsize, int userID);
