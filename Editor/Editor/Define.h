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


extern HWND			g_hWnd

#define			KEY_S							0x00000080
#define			KEY_L							0x00000100
#define			KEY_C							0x00000200
#define			KEY_J							0x00000400
#define			KEY_O							0x00000800
#define			KEY_B							0x00001000
#define			KEY_I							0x00002000

#define			KEY_1							0x00004000
#define			KEY_2							0x00008000
#define			KEY_3							0x00010000
#define			KEY_4							0x00200000
#define			KEY_5							0x00400000