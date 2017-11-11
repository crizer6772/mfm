#pragma once

#include "../stdafx.h"
#include "../resource.h"

#define MFM_WINDOWTYPE_DEFAULT 311
#define MFM_WINDOWTYPE_RESIZABLE 312

HWND CreateRegularWindow(HINSTANCE hInstance, LPCWSTR ClassName, LPCWSTR Caption, int w, int h, int type);