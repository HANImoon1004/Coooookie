#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "MapMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"


CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back"); //���� 
	
	CSoundMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Set_Scene(SC_LOGO);
	CEffectMgr::Get_Instance()->Initialize();
	
}

void CMainGame::Update()
{
	CKeyMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Update();
	CEffectMgr::Get_Instance()->Update();


}

void CMainGame::Late_Update()
{
	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	BitBlt(m_DC,			// ���������� �׸� DC
		0, // 2, 3���� : ������� ��ġ ��ǥ
		0,
		WINCX,	// 4,5���� : ���� ���� ����, ���� ����
		WINCY,
		hBackDC,			// ���� �׸������ϴ� ��Ʈ�� �̹��� DC
		0,				// 7,8���� : ��Ʈ���� ����� ���� ��ǥ
		0,
		SRCCOPY);

	CSceneMgr::Get_Instance()->Late_Update();
	CMapMgr::Get_Instance()->Late_Update(hBackDC);
}

void CMainGame::Render()
{
	//if (SC_LOGO == CSceneMgr::Get_Instance()->Get_SceneID())
	//	return;
	

	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	BitBlt(m_DC,			// ���������� �׸� DC
		0, // 2, 3���� : ������� ��ġ ��ǥ
		0,
		WINCX,	// 4,5���� : ���� ���� ����, ���� ����
		WINCY,
		hBackDC,			// ���� �׸������ϴ� ��Ʈ�� �̹��� DC
		0,				// 7,8���� : ��Ʈ���� ����� ���� ��ǥ
		0,
		SRCCOPY);

	CSceneMgr::Get_Instance()->Render(hBackDC);
	CEffectMgr::Get_Instance()->Render(hBackDC);

}

void CMainGame::Release()
{
	CSoundMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CEffectMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);

}
