#include "stdafx.h"
#include "Player.h"
#include "BmpMgr.h"


Player::Player()
{
}

Player::~Player()
{
	Release();
}

void Player::Initialize(void)
{
	m_pFrameKey = L"Player_Run";
	m_eCurState = PLAYER_RUN;
	m_eNextState = PLAYER_RUN;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameAnimation = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_fDiagonal = 100.f;
	m_fJumpPower = 20.f;
	m_fJumpTime = 0.f;
	m_bJump = false;

	m_iDrawIDX = 0;
	m_iDrawIDY = 0;

	m_tInfo.fX = 100;
	m_tInfo.fY = 400;

	m_tInfo.fCX = 320; 
	m_tInfo.fCY = 320;
}

int Player::Update(void)
{
	
	Jump();
	Move_Frame();
	
	Update_Rect();
	Animation_Change();
	return OBJ_NOEVENT;
}

void Player::Late_Update(void)
{

}

void Player::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left ,//���� ���� ��ġ ��ǥ
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

void Player::Release(void)
{
}

void Player::Jump(void)
{

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_eNextState = PLAYER_JUMP;
	}

	if (GetAsyncKeyState('D'))
		m_eNextState = PLAYER_DIE;
	float		fY = 0.f;

	//bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	//if (m_bJump)
	//{
	//	// �������� ���� ����
	//	m_tInfo.fY -= m_fJumpPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) * 0.5f;
	//	m_fJumpTime += 0.2f;

	//	if (bLineCol && (fY < m_tInfo.fY))
	//	{
	//		m_bJump = false;
	//		m_fJumpTime = 0.f;
	//		m_tInfo.fY = fY;
	//	}

	//}
	//else if (bLineCol)
	//{
	//	m_tInfo.fY = fY;
	//}

}

void Player::Animation_Change()
{
	if (m_eCurState != m_eNextState) {
		switch (m_eNextState) {
		case PLAYER_RUN:
			m_tFrame.iFrameStart = 0;//���� ����
			m_tFrame.iFrameEnd = 3; //���� ��
			m_tFrame.iFrameAnimation = 0;//���� ���� ��ġ
			m_tFrame.dwSpeed = 100; //���� ���� ����
			break;
		case PLAYER_SLIDE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameAnimation = 0;
			m_tFrame.dwSpeed = 100;
			break;
		case PLAYER_JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameAnimation = 1;
			m_tFrame.dwSpeed = 100; 
			break;
		case PLAYER_DIE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameAnimation = 2;
			m_tFrame.dwSpeed = 200;
			break;
		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}
