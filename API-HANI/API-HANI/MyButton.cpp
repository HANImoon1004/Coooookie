#include "stdafx.h"
#include "MyButton.h"
#include "SceneMgr.h"
#include "BmpMgr.h"

CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	m_tInfo.fCX = 494;
	m_tInfo.fCY = 197;

	m_eGroup = RENDER_UI;
}

int CMyButton::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);


	if (PtInRect(&m_tRect, pt))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (!(lstrcmp(L"Button", m_pFrameKey)))
				CSceneMgr::Get_Instance()->Set_Scene(SC_STAGE01);

			/*else if (!(lstrcmp(L"Edit", m_pFrameKey)))
				CSceneMgr::Get_Instance()->Set_Scene(SC_EDIT);*/

			//else if (!(lstrcmp(L"Exit", m_pFrameKey)))
			//	DestroyWindow(g_hWnd);

			return;
		}

		m_iDrawID = 1;
	}

	else
		m_iDrawID = 0;

}

void CMyButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_iDrawID,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(125, 255, 189)); //연두색 제거 

}

void CMyButton::Release(void)
{
}
