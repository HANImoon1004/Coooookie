#include "stdafx.h"
#include "MapMgr.h"
#include "Maps.h"
#include "KeyMgr.h"
#include "CScrollMgr.h"
#include "Block.h"

CMapMgr*	CMapMgr::m_pInstance = nullptr;

CMapMgr::CMapMgr()
{
	m_tFrameKey = NULL;
}


CMapMgr::~CMapMgr()
{
	Release();
}

void CMapMgr::Save_Map()
{
}

void CMapMgr::Load_Map()
{
}

void CMapMgr::Initialize()
{
}

void CMapMgr::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= CScrollMgr::Get_Instance()->Get_ScrollY();

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-10);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(+10);

	if (CKeyMgr::Get_Instance()->Key_Down('B'))//블럭
	{
		m_eID = MAP_BLOCK;
		m_iMapKey = 1;
		m_tFrameKey = L"Block";
		m_iMCX = BLOCK_CX;
		m_iMCY = BLOCK_CY;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		switch (m_eID)
		{
		case MAP_BLOCK:
			m_pMap = new CBlock;
			break;
		}

		if (m_pMap) //값이 있으면
		{
			m_listMap[m_eID].push_back(m_pMap); //리스트에 넣구 
			m_listMap[m_eID].back()->Set_Pos(float(pt.x), float(pt.y));//넣은 애 위치
		}
		
	}
}

void CMapMgr::Render(HDC hDC)
{
	if (m_tFrameKey)
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_tFrameKey);
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);



		int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

		GdiTransparentBlt(hDC, 
			static_cast<int>(pt.x / 10) * 10, //붙어있는 위치
			static_cast<int>(pt.y / 10) * 10,
			m_iMCX,
			m_iMCY,
			hMemDC,
			0, 0,
			m_iMCX,
			m_iMCY,
			RGB(255, 0, 255));
	}

	for (int i = 0; i < MAP_END; ++i)
	{
		for (auto& iter : m_listMap[i])
		{
			iter->Render(hDC);
		}
	}
	
}

void CMapMgr::Release()
{
	for (int i = 0; i < MAP_END; ++i) 
	{
		for_each(m_listMap[i].begin(), m_listMap[i].end(), Safe_Delete<CMaps*>);
	}
}
