#pragma once

#include "../resource.h"
#include "../stdafx.h"
#include "../client/client_main.hpp"
#include "../server/server_main.hpp"

#define MFM_CLIENTMODE 13
#define MFM_SVMODE 14
#define MFM_SVCMODE 15

extern HINSTANCE hInst_sf;
extern LPTSTR mfm_cHostname;
extern int mfmMode;
extern bool svcmode;
extern const int mmBufSize;

BOOL CALLBACK WndProc_MainMenu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);