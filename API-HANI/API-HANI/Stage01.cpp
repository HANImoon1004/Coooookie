#include "stdafx.h"
#include "Stage01.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "CScrollMgr.h"
#include "AbstractFactory.h"
#include "Soup.h"
#include "Player.h"
#include "Pet.h"
#include "MapMgr.h"
#include "SoundMgr.h"
#include "Effect.h"
#include "SceneMgr.h"
//#define MAX_COMPUTERNAME_LENGTH 31

CStage01::CStage01()
{
}

CStage01::CStage01(TCHAR* pFrameKey)
{
}


CStage01::~CStage01()
{
	Release();
}

void CStage01::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map1.bmp", L"Map1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Run.bmp", L"Player_Run"); //플레이어
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Block.bmp", L"Block"); 
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Cat.bmp", L"Cat");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/SilverCoin.bmp", L"SilverCoin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/GoldCoin.bmp", L"GoldCoin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BigSilverCoin.bmp", L"BigSilverCoin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BigGoldCoin.bmp", L"BigGoldCoin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Otte.bmp", L"Otte");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Jelly.bmp", L"Jelly");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Booster.bmp", L"Booster");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Big.bmp", L"Big");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Magnet.bmp", L"Magnet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/MidBlock.bmp", L"MidBlock");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Gaeguri.bmp", L"Gaeguri");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HPback.bmp", L"HPback");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HPbar.bmp", L"HPbar");

	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/쑥쑥튼튼채소마을.mp3", SOUND_BGM, CObj::g_fSound);

	CSoundMgr::Get_Instance()->PlaySound(L"쑥쑥튼튼채소마을.mp3", SOUND_BGM, CObj::g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Coin.wav", SOUND_EFFECT, CObj::g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Jelly.wav", SOUND_EFFECT, CObj::g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/KingCoin.wav", SOUND_EFFECT, CObj::g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/슬라이드.wav", SOUND_PLAYER, CObj::g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/거인끝.wav", SOUND_EFFECT, CObj::g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/아이템.wav", SOUND_EFFECT, CObj::g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/에헷.wav", SOUND_PLAYER, CObj::g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/파박.wav", SOUND_EFFECT, CObj::g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/냐옹.wav", SOUND_EFFECT, CObj::g_fSound);



	CObj* pObj = nullptr;
	
	//if(pFrameKey)
	pObj = CAbstractFactory<Player>::Create();
	pObj = new Player(L"Player_Run");
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pObj);

	pObj = CAbstractFactory<CPet>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PET, pObj);

	CMapMgr::Get_Instance()->Initialize();

	

	m_dwTime = GetTickCount();

}

int CStage01::Update(void)
{
	CMapMgr::Get_Instance()->Update();

	CScrollMgr::Get_Instance()->Set_ScrollX(-m_fScroll);

	if (GetAsyncKeyState(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (GetAsyncKeyState(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	//if (GetAsyncKeyState(VK_UP))
	//	CScrollMgr::Get_Instance()->Set_ScrollY(5.f);

	//if (GetAsyncKeyState(VK_DOWN))
	//	CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	}
	CMapMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CStage01::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update(); //위반뜸

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	if (iScrollX < -11500)
  		CSceneMgr::Get_Instance()->Set_Scene(SC_ENDING);

	int iY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY;
	if(iY >= 600)
		CSceneMgr::Get_Instance()->Set_Scene(SC_ENDING);

	bool isDead = CObjMgr::Get_Instance()->Get_Player()->Get_Dead();
	DWORD dwTime = GetTickCount();
	if (isDead)
	{
		if(dwTime + 500 < GetTickCount())
		CSceneMgr::Get_Instance()->Set_Scene(SC_ENDING);
	}


}

void CStage01::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Map1");//메뉴 배경


	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	//if(iScrollX <= - 900)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(900); //이러면 맵이 진행이 안됨

	//if (iScrollX <= -1800)
	//	iScrollX = 0;
	
	BitBlt(hDC,
		iScrollX % 900 ,
		iScrollY,
		1800, //이미지 사이즈 x
		600, //이미지 사이즈 y
		hMemDC,
		0,
		0,
		SRCCOPY);

	CMapMgr::Get_Instance()->Render(hDC);

	int iHp = dynamic_cast<Player*>(CObjMgr::Get_Instance()->Get_Player())->Get_Hp();

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"HPback");
	
	GdiTransparentBlt(hDC,
		WINCX*0.2, 20,
		500, 51,	hMemDC,
		0, 0,	500,  51, ASHBLUE); 
	

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"HPbar");

	GdiTransparentBlt(hDC,
		WINCX * 0.2, 20,
		iHp, 51, hMemDC,
		0, 0, iHp, 51, ASHBLUE); //hp가 180이 되면 죽어야함


	CObjMgr::Get_Instance()->Render(hDC);

	int iMoney = dynamic_cast<Player*>(CObjMgr::Get_Instance()->Get_Player())->Get_Money();
	int iScore = dynamic_cast<Player*>(CObjMgr::Get_Instance()->Get_Player())->Get_Score();

	TCHAR szMoney[32];
	TCHAR szScore[32];
	TCHAR szHp[32];
	SetBkMode(hDC, 1);
	SetTextColor(hDC, WHITE);
	HFONT hFont, oldFont;
	hFont = CreateFont(30, //높이
		0, 0, 0, 0, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH || FF_ROMAN,
		TEXT("CookieRun Black")); //폰트
	oldFont = (HFONT)SelectObject(hDC, hFont);

	//TextOut(hDC, 300, 300, szComName, lstrlen(szComName)); //단순히 지영하니 뜸
	wsprintf(szScore, L"%i 점!", iScore); //세번째 인수는 %s, 2인자를 1인자에 복사해주는 것 같다
	TextOut(hDC, 810, 20, szScore, lstrlen(szScore));
	
	wsprintf(szMoney, L"%i 원", iMoney);
	TextOut(hDC, 810, 40, szMoney, lstrlen(szMoney));

	////wsprintf(szMoney, L"가진 돈 : %i", iMoney);
	//wsprintf(szScore, L"점수 : %i", iScore);
	//wsprintf(szHp, L"체력 : %i", iHp);

	//TextOut(hDC, 0, 100, szMoney, lstrlen(szMoney));
	//TextOut(hDC, 0, 130, szScore, lstrlen(szScore));
	//TextOut(hDC, 0, 160, szHp, lstrlen(szHp));

	//TCHAR szX[32];
	//float fX = CScrollMgr::Get_Instance()->Get_ScrollX();
	//wsprintf(szX, L"x : %i", fX);
	//TextOut(hDC, 810, 60, szX, lstrlen(szX));

}

void CStage01::Release(void)
{
	CMapMgr::Get_Instance()->Destroy_Instance();
}
