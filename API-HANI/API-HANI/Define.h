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

#define			SCOINS_CX				48
#define			SCOINS_CY				48

#define			GCOINS_CX				58
#define			GCOINS_CY				59

#define			SCOINB_CX				160
#define			SCOINB_CY				161

#define			GCOINB_CX				161
#define			GCOINB_CY				161

#define			OTTE_CX					120
#define			OTTE_CY					230

#define			SPEED_SCR				3

#define			KEY_SPACE				0x00100000
#define			KEY_DOWN					0x00000008


extern HWND			g_hWnd;