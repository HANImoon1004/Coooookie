#include "stdafx.h"
#include "MenuPlayer.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

MenuPlayer::MenuPlayer()
{
}

MenuPlayer::MenuPlayer(TCHAR* pFrameKey, FRAME tFrame, float fX, float fY)
{
	m_pFrameKey = pFrameKey; 
	m_tFrame = tFrame; 
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
}

MenuPlayer::~MenuPlayer()
{
}

void MenuPlayer::Initialize(void)
{
	/*m_pFrameKey = L"Pancake";*/
	m_eCurState = MENU_IDLE;
	m_eNextState = MENU_IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameAnimation = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;
}

int MenuPlayer::Update(void)
{
	
	Move_Frame();
	Update_Rect();
	return 0;
}

void MenuPlayer::Late_Update(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);


	if (PtInRect(&m_tRect, pt))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (!(lstrcmp(L"Pancake", m_pFrameKey))) //������ũ�� ������
			{
				CSoundMgr::Get_Instance()->PlaySound(L"PanCake_Jump.wav", SOUND_EFFECT, g_fSound);
				CSceneMgr::Get_Instance()->Set_Scene(SC_STAGE01);
			}

			/*else if (!(lstrcmp(L"Edit", m_pFrameKey)))
				CSceneMgr::Get_Instance()->Set_Scene(SC_EDIT);*/

				//else if (!(lstrcmp(L"Exit", m_pFrameKey)))
				//	DestroyWindow(g_hWnd);
			if (!(lstrcmp(L"Lilac", m_pFrameKey)))
			{
				//���϶� 
			}
			return;
		}
		

		m_tFrame.iFrameAnimation = 1;
	}

	else
		m_tFrame.iFrameAnimation = 0;
}

void MenuPlayer::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left,//���� ���� ��ġ ��ǥ
		m_tRect.top,
		(int)m_tInfo.fCX, //���� ���� ���� ����
		(int)m_tInfo.fCY,
		hMemDC,
		int(m_tInfo.fCX) * m_tFrame.iFrameStart, //��Ʈ���� ���� ��ǥ�� ��� ���� ����
		int(m_tInfo.fCY) * m_tFrame.iFrameAnimation, //��Ʈ���� ���� ��ǥ�� ��� ���� ����,
		int(m_tInfo.fCX), //���� �� ��Ʈ�� ���� ����
		int(m_tInfo.fCY),
		ASHBLUE);
}

void MenuPlayer::Release(void)
{
}


