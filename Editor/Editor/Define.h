#pragma once

#define			WINCX							900
#define			WINCY							600
#define			PI									3.141592f
#define			PURE								= 0 

#define			OBJ_NOEVENT			0
#define			OBJ_DEAD					1

#define			VK_MAX						0xff

#define			SAFE_DELETE(p)		if(p) { delete p; p = nullptr;}

#define			CENTERED(fCX)		(WINCX - FCX)*0.5

#define			ASHBLUE						RGB(156,175,217)
#define			BLOCK_CX					100
#define			BLOCK_CY					113

extern HWND			g_hWnd