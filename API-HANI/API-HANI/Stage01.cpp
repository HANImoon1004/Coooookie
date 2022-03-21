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

//#define MAX_COMPUTERNAME_LENGTH 31

CStage01::CStage01()
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

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Gaeguri.bmp", L"Gaeguri");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HPback.bmp", L"HPback");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HPbar.bmp", L"HPbar");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Coin_Effect.bmp", L"Coin_Effect");


	CObj* pObj = nullptr;
	
	pObj = CAbstractFactory<Player>::Create();
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

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CStage01::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update(); //위반뜸


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
		WINCX*0.2, 30,
		500, 51,	hMemDC,
		0, 0,	500,  51, ASHBLUE); 
	
	//GdiTransparentBlt(hDC,
	//		int(m_tInfo.fX - m_tInfo.fCX * 0.5),//복사 받을 위치 좌표
	//		int(m_tInfo.fY - m_tInfo.fCY * 0.5),
	//		m_tInfo.fCX, //복사 받을 가로 길이
	//		m_tInfo.fCY,
	//		hMemDC,
	//		int(m_tInfo.fCX) * m_tFrame.iFrameStart, //비트맵의 시작 좌표값 출력 시작 지점
	//		int(m_tInfo.fCY) * m_tFrame.iFrameAnimation, //비트맵의 시작 좌표값 출력 시작 지점,
	//		m_tInfo.fCX, //복사 할 비트맵 가로 길이
	//		m_tInfo.fCY,
	//		ASHBLUE);

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"HPbar");

	GdiTransparentBlt(hDC,
		WINCX * 0.2, 30,
		iHp, 51, hMemDC,
		0, 0, iHp, 51, ASHBLUE); //hp가 180이 되면 죽어야함


	CObjMgr::Get_Instance()->Render(hDC);

	int iMoney = dynamic_cast<Player*>(CObjMgr::Get_Instance()->Get_Player())->Get_Money();
	int iScore = dynamic_cast<Player*>(CObjMgr::Get_Instance()->Get_Player())->Get_Score();

	TCHAR szMoney[32];
	TCHAR szScore[32];
	TCHAR szHp[32];

	wsprintf(szMoney, L"가진 돈 : %i", iMoney);
	wsprintf(szScore, L"점수 : %i", iScore);
	wsprintf(szHp, L"체력 : %i", iHp);

	TextOut(hDC, 0, 100, szMoney, lstrlen(szMoney));
	TextOut(hDC, 0, 130, szScore, lstrlen(szScore));
	TextOut(hDC, 0, 160, szHp, lstrlen(szHp));


}

void CStage01::Release(void)
{
	CMapMgr::Get_Instance()->Destroy_Instance();
}
