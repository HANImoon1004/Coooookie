#include "stdafx.h"
#include "Player.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"

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
	m_fJumpPower = 18.f;
	m_fJumpTime = 0.f;
	m_fHeight = 0.f;
	m_fStartY = 0.f;
	m_fSpeed = 80.f;
	m_bJump = false;
	m_bDoJump = false;

	m_iDrawIDX = 0;
	m_iDrawIDY = 0;

	m_tInfo.fCX = PLAYER_CX;
	m_tInfo.fCY = PLAYER_CY;

	m_tInfo.fX = 200; //시작 위치 가로
	m_tInfo.fY = WINCY - 113 - m_tInfo.fCY*0.5;

}

int Player::Update(void)
{
	if (!Jump())
		Key_Check();

	Key_Input();
	//Jump();
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
		m_tRect.left,//복사 받을 위치 좌표
		m_tRect.top,
		(int)m_tInfo.fCX, //복사 받을 가로 길이
		(int)m_tInfo.fCY,
		hMemDC,
		int(m_tInfo.fCX) * m_tFrame.iFrameStart, //비트맵의 시작 좌표값 출력 시작 지점
		int(m_tInfo.fCY) * m_tFrame.iFrameAnimation, //비트맵의 시작 좌표값 출력 시작 지점,
		int(m_tInfo.fCX), //복사 할 비트맵 가로 길이
		int(m_tInfo.fCY),
		ASHBLUE);
}

void Player::Release(void)
{
}

void Player::Key_Input()
{
	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_eNextState = PLAYER_JUMP;
		m_bJump = true;
	}*/

	//if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	//{
	//	m_eNextState = PLAYER_SLIDE;
	//}
}

void Player::Key_Check()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(KEY_DOWN))
	{
		m_eNextState = PLAYER_SLIDE;
	}

	if (CKeyMgr::Get_Instance()->Key_Up(KEY_DOWN))
	{
		m_eNextState = PLAYER_RUN;
	}
}

void Player::Update_Rect()
{
	//190 190 


	switch (m_eNextState)
	{
	case PLAYER_IDLE: PLAYER_RUN: PLAYER_JUMP: PLAYER_DIE:
	m_tRect.left = m_tInfo.fX - (190 >> 1);
	m_tRect.right = m_tInfo.fX + (190 >> 1);
	m_tRect.top = m_tInfo.fY - (190 >> 1);
	m_tRect.bottom = m_tInfo.fY + (190 >> 1);
	break;

	case PLAYER_SLIDE:
		m_tRect.left = m_tInfo.fX - (200 >> 1);
		m_tRect.right = m_tInfo.fX + (200 >> 1);
		m_tRect.top = m_tInfo.fY - (190 >> 2);
		m_tRect.bottom = m_tInfo.fY + (190 >> 2);
		break;

	default:
		m_tRect.left = m_tInfo.fX - (190 >> 1);
		m_tRect.right = m_tInfo.fX + (190 >> 1);
		m_tRect.top = m_tInfo.fY - (190 >> 1);
		m_tRect.bottom = m_tInfo.fY + (190 >> 1);
		break;
	}
}

bool Player::Jump(void)
{
	if (GetAsyncKeyState('D'))
		m_eNextState = PLAYER_DIE;


	if (m_fJumpTime + 150 < GetTickCount()) //hani 이거 의미... 
	{
		if ((m_bJump && (!m_bDoJump))) // 점프가 참이고 더블점프 아닐 때
		{
			if (CKeyMgr::Get_Instance()->Key_Down(KEY_SPACE)) //hani스페이스바 이전에 호출x 지금호출o ??
			{
				m_fStartY = m_tInfo.fY; 
				m_bDoJump = true; 
				m_fJumpTime = 0.f; //jumpTime 0으로 초기화
				m_eNextState = PLAYER_DOUBLEJUMP; 
			}
		}
	}
	if (!m_bJump) // 점프 false일 때  -> 일단점프 hani 이렇게 나눠놓은 이유가 뭘까요? 
	{							// 이러면 점프 두 번 눌러야 일단 점프 한 번 하는게 아닌가... 
		if (CKeyMgr::Get_Instance()->Key_Down(KEY_SPACE))
		{
 			m_fStartY = m_tInfo.fY;
			m_bJump = true;
			m_dwTime = GetTickCount();
			m_eNextState = PLAYER_JUMP; 
		}
	}	


	if (m_bDoJump) // 더블점프
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) * 0.5f;
		m_fJumpTime += 0.2f; //좀만 천천히 떨어지게 못하나? hani...
	}

	
//	bool bBlockCol = CollisionMgr::Collision_Block(pBlock.,m_tRect)

		//for()
	else if (m_bJump) // 일단점프
	{

		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) * 0.5f;
		m_fJumpTime += 0.2f;

	}

	else
		m_tInfo.fY = WINCY - 113 - m_tInfo.fCY * 0.5;

	

	if (m_bJump)
		return true;

	else return false;

}

void Player::Jump_Stop()
{
	m_fJumpTime = 0.f; //QUE 왜 이것만 밖에 나와있을까욤
	
	if (m_bJump)
	{
		if ((WINCY - 113 - m_tInfo.fCY * 0.5) < m_tInfo.fY)
			m_tInfo.fY = WINCY - 113 - m_tInfo.fCY * 0.5;
		m_bJump = false;
		m_bDoJump = false;
		m_dwTime = GetTickCount();
		
		m_eNextState = PLAYER_RUN;
	}

}

void Player::Animation_Change()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState) {
		case PLAYER_RUN:
			m_tFrame.iFrameStart = 0;//가로 시작
			m_tFrame.iFrameEnd = 3; //가로 끝
			m_tFrame.iFrameAnimation = 0;//세로 시작 위치
			m_tFrame.dwSpeed = 100; //낮을 수록 빠름
			break;
		case PLAYER_JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameAnimation = 1;
			m_tFrame.dwSpeed = 200;
			break;
		case PLAYER_DOUBLEJUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameAnimation = 2;
			m_tFrame.dwSpeed = 100;
			break;
		case PLAYER_DIE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameAnimation = 2;
			m_tFrame.dwSpeed = 200;
			break;
		case PLAYER_SLIDE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameAnimation = 3;
			m_tFrame.dwSpeed = 100;
			break;

		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}
