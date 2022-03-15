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


#define			PLAYER_CX				200
#define			PLAYER_CY				200	

#define			BLOCK_CX					100
#define			BLOCK_CY					113

#define			CAT_CX						130  
#define			CAT_CY						130

#define			SPEED_SCR				3

#define			KEY_SPACE				0x00100000
#define			KEY_DOWN					0x00000008

extern HWND			g_hWnd;