#include "send_cmd.hpp"

std::map<std::string, CommandInfo> commands;

///HELPER FUNCTIONS
void STLStringToLowercase(std::string* str)
{
	std::string res = *str;
	for(int i=0; i<str->size(); i++)
	{
		char* cPtr =&res[i];
		*cPtr = (*cPtr>='A'&&*cPtr<='Z')?*cPtr+32:*cPtr;
	}
	*str = res;
}
///./////////////////////////////////////////////////

void RegisterCommand(LPCSTR name, mfmSvCommand func, int helpID, int perm)
{
	std::string sName = name;
	STLStringToLowercase(&sName);

	CommandInfo c;
	c.funcPtr = func;
	c.helpID = helpID;
	c.permissions = perm;

	commands[sName] = c;
}

void SendServerCommand(LPCSTR cmd, int cmdsize, int UserID)
{
	//part 0
	int cmdLength = cmdsize; //strlen(cmd);
	if(!cmdLength)
		return;

	//part 1 - echo
	int cmdEBufSize = 64;
	char* cmdecho = new char[cmdEBufSize];
	char* svlog = new char[cmdLength+cmdEBufSize];
	memset(cmdecho, 0, cmdEBufSize);
	memset(svlog, 0, cmdLength+cmdEBufSize);
	LoadStringA(NULL, IDS_CMDECHO, cmdecho, cmdEBufSize);
	strncat(svlog, cmdecho, cmdLength+cmdEBufSize);
	strncat(svlog, cmd, cmdLength+cmdEBufSize);
	ServerLog(svlog);
	delete[] cmdecho;
	delete[] svlog;

	//part 2 - parsing the actual command
	char* cmdPart;
	char* argPart;
	int cmdSize = 0;
	int argSize = 0;
	bool phase = 0;
	bool nsc = 0; //for ignoring leading spaces
	for(int i=0; cmd[i]!='\0'; i++)
	{
		if(cmd[i] == ' ')
		{
			if(!phase && nsc)
			{
				phase = 1;
				while(cmd[i]==' ')
					i++;
			}
		}
		else
			nsc=1;
		if(phase==0)
			cmdSize++;
		else
			argSize++;
	}
	cmdPart = new char[cmdSize+1];
	argPart = new char[argSize+1];
	memset(cmdPart, 0, cmdSize+1);
	memset(argPart, 0, argSize+1);

	strncpy(cmdPart, cmd, cmdSize);
	strncpy(argPart, &cmd[cmdSize+1], argSize);

	std::string cmdPartS(cmdPart);
	STLStringToLowercase(&cmdPartS);
	if(commands.find(cmdPartS) == commands.end())
		ServerLog("Command not recognized. Type 'help' to list available commands.");
	else
	{
		mfmSvCommand cmdFunc = commands[cmdPartS].funcPtr;
		cmdFunc(argPart, cmdLength, UserID);
	}


	delete[] cmdPart;
	delete[] argPart;
}

void SendServerCommand(LPCWSTR cmd, int cmdsize, int UserID)
{
	int utf8size = WideCharToMultiByte(CP_UTF8, 0, cmd, cmdsize, NULL, 0, NULL, NULL);
	char* utf8cmd = new char[utf8size+1];
	memset(utf8cmd, 0, utf8size+1);
	WideCharToMultiByte(CP_UTF8, 0, cmd, cmdsize, utf8cmd, utf8size, NULL, NULL);
	SendServerCommand(utf8cmd, utf8size, UserID);
	delete[] utf8cmd;
}
