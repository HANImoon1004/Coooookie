#include "stdafx.h"
#include "CScrollMgr.h"


CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
{
	m_fScrollLockX = WINCX;
	m_fScrollLockY = WINCY;
	m_iX = 0;
	m_iY = 0;
	
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock(void)
{
	//if (0.f < m_fScrollX) //0308 hani 선생님 코드 주석
	//	m_fScrollX = 0.f;

	//if (0.f < m_fScrollY)
	//	m_fScrollY = 0.f;

	//if (WINCX - TILECX * TILEX > m_fScrollX)
	//	m_fScrollX = WINCX - TILECX * TILEX;

	//if (WINCY - TILECY * TILEY > m_fScrollY)
	//	m_fScrollY = WINCY - TILECY * TILEY;

	/*if (WINCX < m_fScrollLockX)
	{
		if (0 < m_fScrollX)
			m_fScrollX = 0;

		if (m_fScrollX < WINCX - m_fScrollLockX)
			m_fScrollX = WINCX - m_fScrollLockX;
	}

	if (WINCY < m_fScrollLockY)
	{
		if (0 < m_fScrollY)
			m_fScrollY = 0;

		if (m_fScrollY < WINCY - m_fScrollLockY)
			m_fScrollY = WINCY - m_fScrollLockY;
	}*/
}

POINT CScrollMgr::Cursor_Scroll_Pos(void)
{

	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= m_iX;
	pt.y -= m_iY;

	return pt;
}
