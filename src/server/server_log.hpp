#pragma once

#include "../stdafx.h"
#include "../resource.h"

#define MFM_SVLOG_FILENAME "server/server.log"
#define MFM_MAX_LOG_BUFFER_SIZE 1048576

extern char* svLogBuffer;
extern FILE* svLogFile;
extern WCHAR* cmdLineBuf;

bool InitServerLog(int buffer_size);
void ServerLog(LPCSTR msg);
void ClearServerWindow();
