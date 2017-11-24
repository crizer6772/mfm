#include "send_cmd.hpp"
#include "commands.hpp"

///HELPER FUNCTIONS
void __DisplayHelp(std::string name, int code)
{
	if(code==0)
		return;
	char help[4096];
	LoadStringA(NULL, code, help, 4096);
	std::string helpS(help);
	std::string cLine = name + " " + helpS;
	ServerLog(cLine.c_str());
}
///.///////////////////////////////////////////////////////////////////

/** COMMAND: "help" **/
int cServerHelp(const char* arg, int cmdsize, int userID)
{
	bool mode = 1; //0 - specific command, 1 - all
	std::string argS(arg);
	if(commands.find(argS) != commands.end())
		mode = 0;

	if(mode)
	{
		std::map<std::string, CommandInfo>::iterator it;
		for(it=commands.begin();it!=commands.end();it++)
		{
			__DisplayHelp(it->first, it->second.helpID);
		}
	}
	else
	{
		__DisplayHelp(argS, commands[argS].helpID);
	}
}

/** COMMAND: "fuck you" **/
int cFuckYou(const char* arg, int cmdsize, int userID)
{
	if(strcmp(arg, "you")==0)
	{
		char buf[4096];
		LoadStringA(NULL, IDS_NAVYSEALCP, buf, 4096);
		ServerLog(buf);
	}
}

/** COMMAND: "kick" **/
int cKickUser(const char* arg, int cmdsize, int userID)
{
	ServerLog("this does nothing fuck off");
}

/** COMMAND: "exec" **/
int cExecFile(const char* arg, int cmdsize, int userID)
{
	std::string relPath = "server/" + std::string(arg);
	std::ifstream file(relPath.c_str());
	if(!file.good())
	{
		ServerLog("error: file corrupted or does not exist");
		return -1;
	}
	else while(!file.eof())
	{
		std::string cmd;
		std::getline(file, cmd);
		SendServerCommand(cmd.c_str(), cmd.size(), userID);
	}
}

/** COMMAND: "clear" **/
int cClear(const char* arg, int cmdsize, int userID)
{
	ClearServerWindow();
}
/** COMMAND: "cls" **/
int cCls(const char* arg, int cmdsize, int userID)
{
	cClear(arg, cmdsize, userID);
}
