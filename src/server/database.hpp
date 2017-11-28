#pragma once
#include "../stdafx.h"
#include "../shared/crypto/random.hpp"

struct ChatMessage
{
	int sender;
	uint64_t timestamp;
	int length;
	char* content;
};

struct Conversation
{
	std::vector<int> members;
};

struct UserAccount
{
	int id;
	char username[32];
	char pwdhash[32]; //sha256(sha256(password)+salt), binary
	char pwdsalt[32];
	char emailAddr[64];
	int authority;
	bool online;

	std::vector<Conversation> activeConversations;
};
