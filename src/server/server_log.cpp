#include "server_log.hpp"
#include "log_window.hpp"

char* svLogBuffer = NULL;
FILE* svLogFile = NULL;

int svLogBufferSize;

bool InitServerLog(int bufferSize)
{
	delete[] svLogBuffer;
	if(svLogFile)
	{
		fclose(svLogFile);
	}

	svLogBufferSize = bufferSize;
	if(bufferSize < 0 || bufferSize > MFM_MAX_LOG_BUFFER_SIZE)
	{
		return false;
	}
	svLogBuffer = new char[bufferSize];
	memset(svLogBuffer, 0, bufferSize);
	_mkdir("server");
	svLogFile = fopen(MFM_SVLOG_FILENAME, "w");
	if(!svLogFile)
		MessageBox(NULL, TEXT("Failed to create server log file"), TEXT("fatal error"), MB_OK|MB_ICONERROR);
}

void ServerLog(LPCSTR msg)
{
	int msglen = strlen(msg)+1;
	int buflen = strlen(svLogBuffer);
	int shift = std::max((msglen+buflen)-(svLogBufferSize-2), 0);
	for(int i=0; i<buflen-shift && shift; i++)
	{
		svLogBuffer[i] = svLogBuffer[i+shift];
	}
	fprintf(svLogFile, "%s\n", msg);
	sprintf(&svLogBuffer[(buflen-shift)], "%s\r\n", msg);
	svLogBuffer[svLogBufferSize-1] = 0;
	SetWindowTextA(ServerGUI.LogWindow, svLogBuffer);
	SendMessage(ServerGUI.LogWindow, EM_SETSEL, 0, -1);
	SendMessage(ServerGUI.LogWindow, EM_SETSEL, -1, -1);
	SendMessage(ServerGUI.LogWindow, EM_SCROLLCARET, 0, 0);
}
