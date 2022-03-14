#include "stdafx.h"
#include "Stage01.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "CScrollMgr.h"
#include "AbstractFactory.h"
#include "Soup.h"
#include "Player.h"

//#define MAX_COMPUTERNAME_LENGTH 31

CStage01::CStage01()
{
}


CStage01::~CStage01()
{
}

void CStage01::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map1.bmp", L"Map1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Run.bmp", L"Player_Run"); //플레이어


	CObj* pObj = nullptr;
	
	pObj = CAbstractFactory<Player>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pObj);

	
}

int CStage01::Update(void)
{
	if (GetAsyncKeyState(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (GetAsyncKeyState(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	if (GetAsyncKeyState(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);

	if (GetAsyncKeyState(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);

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
	//CObjMgr::Get_Instance()->Late_Update(); //위반뜸
}

void CStage01::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Map1");//메뉴 배경

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC,
		iScrollX,
		iScrollY,
		1063, //이미지 사이즈 x
		1131, //이미지 사이즈 y
		hMemDC,
		0,
		0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

	AddFontResourceA("../Font/PF스타더스트.ttf");

	SetBkMode(hDC, 1);
	SetTextColor(hDC, RGB(255, 255, 255));
	HFONT hFont, oldFont;
	hFont = CreateFont(20, //높이
		0, 0, 0, 0, 0, 0, 0, 
		HANGUL_CHARSET, 0, 0, 0, 
		VARIABLE_PITCH || FF_ROMAN, 
		TEXT("PF스타더스트")); //폰트

	oldFont = (HFONT)SelectObject(hDC, hFont);
	TextOut(hDC, 300, 600, L"안녕!", lstrlen(L"안녕"));

	TextOut(hDC, 300, 300, L"안녕", lstrlen(L"안녕"));

	TCHAR szComName[255]; //hani 컴퓨터, 유저 이름
	TCHAR szUserName[255];
	TCHAR str[255];
	DWORD len;
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(g_hWnd, &ps);
	len = 255;
	GetComputerName(szComName, &len);
	len = 255;
	GetUserName(szUserName, &len);

	TextOut(hDC, 300, 300, szComName, lstrlen(szComName)); //단순히 지영하니 뜸
	wsprintf(szComName, L"%s 안녕!", szComName); //세번째 인수는 %s, 2인자를 1인자에 복사해주는 것 같다
	TextOut(hDC, 300, 400, szComName, lstrlen(szComName)); //지영하니 안녕!
	TextOut(hDC, 300, 500, L"1. 일하기  2. 일하기", lstrlen(L"1. 일하기  2. 일하기"));


}

void CStage01::Release(void)
{
}
