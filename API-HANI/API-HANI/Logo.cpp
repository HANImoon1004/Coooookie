#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "Obj.h"
CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo.bmp", L"Logo");
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Night_Sea_Under_The_Moonlight.mp3", SOUND_BGM, CObj::g_fSound);
	CSoundMgr::Get_Instance()->PlaySound(L"Night_Sea_Under_The_Moonlight.mp3", SOUND_BGM, CObj::g_fSound);
}

int CLogo::Update(void)
{
	return 0;
}

void CLogo::Late_Update(void)
{
	if(GetAsyncKeyState(VK_RETURN))//엔터 
	{
	CSceneMgr::Get_Instance()->Set_Scene(SC_MENU);
	return;
	}
}

void CLogo::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo"); //국기런 ~ 

	BitBlt(hDC,		
		0,			
		0,
		WINCX,		
		WINCY,
		hMemDC,		
		0,			
		0,
		SRCCOPY);

	/*StretchBlt(hDC, 
		0, 0, 
		WINCX, WINCY,
		hMemDC, 
		0, 0, 
		WINCX, WINCY,
		SRCCOPY);*/
}

void CLogo::Release(void)
{
}
