#include "stdafx.h"
#include "MainGame.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "MapMgr.h"
CMainGame::CMainGame()
{
	m_hDC = GetDC(g_hWnd);
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map1.bmp", L"Map");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block.bmp", L"Block");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Cat.bmp", L"Cat");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SilverCoin.bmp", L"SilverCoin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/GoldCoin.bmp", L"GoldCoin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BigSilverCoin.bmp", L"BigSilverCoin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BigGoldCoin.bmp", L"BigGoldCoin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Otte.bmp", L"Otte");



}

void CMainGame::Update()
{
	CKeyMgr::Get_Instance()->Update();
	CMapMgr::Get_Instance()->Update();
}

void CMainGame::Render()
{
	HDC hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Map");

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);

	BitBlt(hBackDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CMapMgr::Get_Instance()->Render(m_hDC);

}

void CMainGame::Release()
{
}
