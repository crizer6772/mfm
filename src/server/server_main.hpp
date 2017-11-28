#pragma once

#include "../stdafx.h"
#include "../resource.h"

#define AUTH_GUEST 0x01
#define AUTH_USER 0x02
#define AUTH_ADMIN 0x04
#define AUTH_HOST 0x08

#define SVW_DEFAULT_WINDOW_WIDTH 540
#define SVW_DEFAULT_WINDOW_HEIGHT 360
#define SVW_SIDEBAR_HEADROOM_H 144
#define SVW_SIDEBAR_HEADROOM_V 36
#define SVW_LOGBOX_OFFSET 2

int FuckYou(const char* arg);
unsigned int __stdcall ServerMain(void* param);
