#pragma once
#include "../stdafx.h"

struct UserAccount
{
	int id;
	char username[32];
	char pwdhash[32]; //sha256(sha256(password)+salt), binary
	char pwdsalt[32];
	int authority;
};

struct ChatMessage
{
	int id;
	int timestamp;
	int length;
	char* content;
};

struct Conversation
{
	int UserID[2];

};
