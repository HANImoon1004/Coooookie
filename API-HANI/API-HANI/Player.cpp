#include "stdafx.h"
#include "Player.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#pragma comment(lib, "msimg32.lib")
#include "SoundMgr.h"
#include "SceneMgr.h"
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
	m_fJumpPower = 13.f;
	m_fJumpTime = 0.f;
	m_fHeight = 0.f;
	m_fStartY = 0.f;
	m_fSpeed = 80.f;
	m_bJump = false;
	m_bDoJump = false;
	m_bSuper = false;
	m_bBig = false;
	m_bHit = false;
	m_bBooster = false;
	
	m_dwRunning = GetTickCount();

	m_iMoney = 0;
	m_iScore = 0;
	m_iHp = 500;

	m_iDrawIDX = 0;
	m_iDrawIDY = 0;

	m_tInfo.fCX = PLAYER_CX;
	m_tInfo.fCY = PLAYER_CY;

	m_tInfo.fX = 200; //시작 위치 가로
	m_tInfo.fY = WINCY - 113 - m_tInfo.fCY * 0.5;
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/거인끝.wav", SOUND_PLAYER, CObj::g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/PanCake_Jump.wav", SOUND_EFFECT, g_fSound);
}

int Player::Update(void)
{
	if (!Jump())
		Key_Check();

	if (m_iHp <= 50 && m_eCurState != PLAYER_DEAD)
	{
		
			m_eNextState = PLAYER_DIE;
			m_bJump = false;
			m_bSuper = true;
		m_dwDie = GetTickCount();
		
		dynamic_cast<CStage01*>(CSceneMgr::Get_Instance()->Get_CScene())->Set_Scroll(0);
		if (m_dwDie + 2000 < GetTickCount())
		{
			m_eNextState = PLAYER_DEAD;
			
		}
		
	}
	/*if (m_bSuper)
		m_iHp = 1000;*/

	if (m_bBooster)
	{
		m_eNextState = PLAYER_BOOSTER;
		if (m_dwBooster + 3000 < GetTickCount()) //2cho who
		{
			m_bSuper = false;
			m_dwSupertime = GetTickCount();
			dynamic_cast<CStage01*>(CSceneMgr::Get_Instance()->Get_CScene())->Set_Scroll(DEFAULT_SPEED);
			m_eNextState = PLAYER_RUN;
	
			m_bBooster = false;
		}
	}
	if (m_bBig)
	{
		m_eNextState = PLAYER_BIG;
		if (m_dwBig + 3000 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"거인끝.wav", SOUND_PLAYER, CObj::g_fSound);
			m_bSuper = false;
			m_dwSupertime = GetTickCount();
			m_eNextState = PLAYER_RUN;

			m_bBig = false;
		}
	}
	Key_Input();
	//Jump();
	Move_Frame();

	Player::Update_Rect();
	Animation_Change();
	return OBJ_NOEVENT;
}

void Player::Late_Update(void)
{
	for (int i = 0; i < MAPID::MAP_END; i++)
	{
		list<CMaps*> temp = OBJMGR->Get_Map((MAPID)i);

		if ((MAPID)i == MAPID::MAP_BLOCK)
		{
			if (CollisionMgr::Collision_Block(temp, this))
			{
				switch ((MAPID)i)
				{
				case MAP_BLOCK:
					Jump_Stop();
					break;
				}
			}
		}
		else
		{
			if (CollisionMgr::Collision_Rect(temp, this))
			{
				switch ((MAPID)i)
				{
				case MAP_OBSTACLE:
					break;
				case MAP_COIN:
				
					break;
				case MAP_JELLY:
					CSoundMgr::Get_Instance()->PlaySound(L"Jelly.wav", SOUND_JELLY, CObj::g_fSound);
					break;
				case MAP_ITEM:
				{

					CSoundMgr::Get_Instance()->PlaySound(L"KingCoin.wav", SOUND_COIN, CObj::g_fSound);
					float fX = temp.front()->Get_MapInfo()->tPoint.fX;
					float fY = temp.front()->Get_MapInfo()->tPoint.fY;
				}
				break;
				case MAP_END:
				default:
					break;
				}
			}
		}
	}

	if (m_dwRunning + 1000 < GetTickCount()) //10초마다 피 깎기
	{
		m_iHp -= 10;
		m_dwRunning = GetTickCount(); //안해주면 계속 피깎여
	}

	if (m_bHit)
	{
		dynamic_cast<CStage01*>(CSceneMgr::Get_Instance()->Get_CScene())->Set_Scroll(SLOW_SPEED);
		if (m_dwHit + 200 < GetTickCount())
		{
			if (m_eCurState == PLAYER_HIT && m_dwHit + 200 < GetTickCount()) //시간 지나면
			{
				dynamic_cast<CStage01*>(CSceneMgr::Get_Instance()->Get_CScene())->Set_Scroll(DEFAULT_SPEED);
				m_bHit = false;
				m_eNextState = PLAYER_RUN;
			}
			if (m_dwHit + 1000 < GetTickCount())
				m_bSuper = false; 

		}
	}
}

void Player::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);



	if (m_bBig)
	{
		GdiTransparentBlt(hDC,
			int(m_tInfo.fX - m_tInfo.fCX),//복사 받을 위치 좌표
			int(m_tInfo.fY - m_tInfo.fCY*1.5),
			(int)m_tInfo.fCX * 2, //복사 받을 가로 길이
			(int)m_tInfo.fCY * 2,
			hMemDC,
			int(m_tInfo.fCX) * m_tFrame.iFrameStart, //비트맵의 시작 좌표값 출력 시작 지점
			int(m_tInfo.fCY) * m_tFrame.iFrameAnimation, //비트맵의 시작 좌표값 출력 시작 지점,
			int(m_tInfo.fCX), //복사 할 비트맵 가로 길이
			int(m_tInfo.fCY),
			ASHBLUE);
	}
	else
	{
		//static HDC AlphaDC;
		//static HBITMAP bm1, hbmMem, hbmMemOld;
		//static BLENDFUNCTION bf;
		//ZeroMemory(&bf, sizeof(bf));
		//
		//AlphaDC = CreateCompatibleDC(hDC);
		//hbmMem = CreateCompatibleBitmap(hDC, 900, 600);

		//GdiTransparentBlt(AlphaDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
		//	hDC,0,0,
		//	int(m_tInfo.fCX), int(m_tInfo.fCY), ASHBLUE);
		
		GdiTransparentBlt(hDC,
			int(m_tInfo.fX - m_tInfo.fCX*0.5),//복사 받을 위치 좌표
			int(m_tInfo.fY - m_tInfo.fCY * 0.5),
			m_tInfo.fCX, //복사 받을 가로 길이
			m_tInfo.fCY,
			hMemDC,
			int(m_tInfo.fCX) * m_tFrame.iFrameStart, //비트맵의 시작 좌표값 출력 시작 지점
			int(m_tInfo.fCY) * m_tFrame.iFrameAnimation, //비트맵의 시작 좌표값 출력 시작 지점,
			m_tInfo.fCX, //복사 할 비트맵 가로 길이
			m_tInfo.fCY,
			ASHBLUE);

		//bf.AlphaFormat = AC_SRC_OVER;
		//bf.SourceConstantAlpha = 100;

		//GdiAlphaBlend(hDC,
		//	m_tRect.left, m_tRect.top, //시작 위치!
		//	(int)m_tInfo.fCX, (int)m_tInfo.fCY, AlphaDC, 
		//	int(m_tInfo.fCX) * m_tFrame.iFrameStart, int(m_tInfo.fCY) * m_tFrame.iFrameAnimation,
		//	(int)m_tInfo.fCX, (int)m_tInfo.fCY, bf);
		//
		//GdiTransparentBlt(hDC,
		//	m_tRect.left,//복사 받을 위치 좌표
		//	m_tRect.top,
		//	(int)m_tInfo.fCX, //복사 받을 가로 길이
		//	(int)m_tInfo.fCY,
		//	hMemDC,
		//	int(m_tInfo.fCX) * m_tFrame.iFrameStart, //비트맵의 시작 좌표값 출력 시작 지점
		//	int(m_tInfo.fCY) * m_tFrame.iFrameAnimation, //비트맵의 시작 좌표값 출력 시작 지점,
		//	int(m_tInfo.fCX), //복사 할 비트맵 가로 길이
		//	int(m_tInfo.fCY),
		//	ASHBLUE);

	}
		

	//AlphaBlend(hDC, m_tRect.left, m_tRect.top, m_tInfo.fCX, m_tInfo.fCY,
	//	AlphaDC,
	//	int(m_tInfo.fCX) * m_tFrame.iFrameStart, 
	//	int(m_tInfo.fCY) * m_tFrame.iFrameAnimation,
	//	m_tInfo.fCX, m_tInfo.fCY, bf);


	//BitBlt(hDC, 0, 0, 900, 600, AlphaDC, 0, 0, SRCCOPY);
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
	if (!m_bDead)
	{
		if (m_eCurState != PLAYER_BOOSTER)
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			{
				m_eNextState = PLAYER_SLIDE;
			}

		if (CKeyMgr::Get_Instance()->Key_Up(VK_DOWN))
		{
			m_eNextState = PLAYER_RUN;
		}

		if (m_eNextState == PLAYER_HIT)
		{

			DWORD dTime = GetTickCount();
			if (dTime + 10 < GetTickCount()) //히트 시간이 좀 지났다면
			{
				m_eNextState = PLAYER_RUN;
			}
		}
	}

}

void Player::Update_Rect()
{
	//190 190 


	switch (m_eNextState)
	{
	case PLAYER_IDLE: PLAYER_RUN: PLAYER_JUMP: PLAYER_DIE:
	m_tRect.left = m_tInfo.fX - (100 >> 1);
	m_tRect.right = m_tInfo.fX + (100 >> 1);
	m_tRect.top = m_tInfo.fY - (100 >> 1);
	m_tRect.bottom = m_tInfo.fY + (100 >> 1);
	break;

	case PLAYER_SLIDE:
		m_tRect.left = m_tInfo.fX - (200 >> 1);
		m_tRect.right = m_tInfo.fX + (200 >> 1);
		m_tRect.top = m_tInfo.fY - (150 >> 3);
		m_tRect.bottom = m_tInfo.fY + (190 >> 1);
		break;

	case PLAYER_BIG:
		m_tRect.left = m_tInfo.fX - (100);
		m_tRect.right = m_tInfo.fX + (100);
		m_tRect.top = m_tInfo.fY - (100);
		m_tRect.bottom = m_tInfo.fY + (100);
		break;
	default:
		m_tRect.left = m_tInfo.fX - (150 >> 1);
		m_tRect.right = m_tInfo.fX + (150 >> 1);
		m_tRect.top = m_tInfo.fY - (150 >> 1);
		m_tRect.bottom = m_tInfo.fY + (150 >> 1);
		break;
	}
}

void Player::Move_Frame()
{

	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			if (m_eCurState == PLAYER_HIT)
				m_eNextState = PLAYER_RUN;

			m_tFrame.iFrameStart = 0;
		}

	}

}

bool Player::Jump(void)
{
	if (GetAsyncKeyState('D'))
		m_eNextState = PLAYER_DIE;

	if (!m_bBooster) //부스터일 때 점프 X
	{
		if (m_fJumpTime + 150 < GetTickCount()) //hani 이거 의미... 150 안에 또 누르면?
		{
			if ((m_bJump && (!m_bDoJump))) // 점프가 참이고 더블점프 아닐 때
			{
				if (CKeyMgr::Get_Instance()->Key_Down(KEY_SPACE)) //hani스페이스바 이전에 호출x 지금호출o ??
				{
					CSoundMgr::Get_Instance()->PlaySound(L"PanCake_Jump.wav", SOUND_EFFECT, g_fSound);

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
				CSoundMgr::Get_Instance()->PlaySound(L"PanCake_Jump.wav", SOUND_EFFECT, g_fSound);

				m_fStartY = m_tInfo.fY;
				m_bJump = true;
				m_dwTime = GetTickCount();
				m_eNextState = PLAYER_JUMP;
			}
		}
	}
	
	m_fJumpTime += 0.2f;

	if (m_bDoJump) // 더블점프
	{

		m_fHeight = 2 * (m_fJumpTime * m_fJumpTime * -9.8 * 0.5) + (m_fJumpTime * m_fSpeed);
		m_tInfo.fY = -m_fHeight + m_fStartY;
		//m_tInfo.fY -= m_fJumpPower * m_fJumpTime - (4.8f * m_fJumpTime * m_fJumpTime) * 0.5f;
		//m_fJumpTime += 0.2f; //좀만 천천히 떨어지게 못하나? hani... wndfurrkthreh wnfdu
	}


	//	bool bBlockCol = CollisionMgr::Collision_Block(pBlock.,m_tRect)

			//for()
	else if (m_bJump) // 일단점프
	{
		
		//m_fHeight = 2 * (m_fJumpTime * m_fJumpTime * -9.8 * 0.5) + (m_fJumpTime * m_fSpeed);
		//m_tInfo.fY = -m_fHeight + m_fStartY;
		//m_tInfo.fY -= m_fJumpPower * m_fJumpTime - (4.8f * m_fJumpTime * m_fJumpTime) * 0.5f;
		//m_fJumpTime += 0.2f; //점프 나중에 하고 0316

		m_tInfo.fY -= m_fJumpPower;
		m_fJumpPower -= 1.f;
	}

	else
	{
		//m_tInfo.fY += m_fJumpTime * 9.8;
	}
	/*else
		m_tInfo.fY = WINCY - 113 - m_tInfo.fCY * 0.5;
*/


	if (m_bJump)
		return true;

	else return false;

}

void Player::Jump_Stop()
{
	m_fJumpTime = 0.f; //QUE 왜 이것만 밖에 나와있을까욤

	if (m_bJump)
	{
		/*if ((WINCY - 113 - m_tInfo.fCY * 0.5) < m_tInfo.fY)
			m_tInfo.fY = WINCY - 113 - m_tInfo.fCY * 0.5;*/
		m_bJump = false;
		m_bDoJump = false;
		m_dwTime = GetTickCount();
		m_fJumpPower = 13.f;

		m_eNextState = PLAYER_RUN;
	}

}

void Player::Animation_Change()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState) {
		case PLAYER_RUN:PLAYER_BIG:
			m_pFrameKey = L"Player_Run";
			m_tFrame.iFrameStart = 0;//가로 시작
			m_tFrame.iFrameEnd = 3; //가로 끝
			m_tFrame.iFrameAnimation = 0;//세로 시작 위치
			m_tFrame.dwSpeed = 100; //낮을 수록 빠름
			break;
		case PLAYER_JUMP:
			m_pFrameKey = L"Player_Run";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameAnimation = 1;
			m_tFrame.dwSpeed = 200;
			break;
		case PLAYER_DOUBLEJUMP:
			m_pFrameKey = L"Player_Run";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameAnimation = 2;
			m_tFrame.dwSpeed = 100;
			break;
		case PLAYER_HIT:
			m_pFrameKey = L"Player_Run";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameAnimation = 3;
			m_tFrame.dwSpeed = 300;
			break;
		case PLAYER_DIE:
			m_pFrameKey = L"Player_Run";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameAnimation = 3;
			m_tFrame.dwSpeed = 200;
			break;
		case PLAYER_DEAD:
			m_pFrameKey = L"Player_Run";
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameAnimation = 3;
			m_tFrame.dwSpeed = 200;
			break;
		case PLAYER_SLIDE:
			m_pFrameKey = L"Player_Run";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameAnimation = 4;
			m_tFrame.dwSpeed = 100;
			break;

		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}

void Player::Super_Cookie()
{
	m_bSuper = true; //무적 트루, 몸 반짝 
	//충돌 처리 안됨




}

void Player::Set_Booster()
{
	m_bBooster = true;
	m_bSuper = true;
	m_dwBooster = GetTickCount();
	m_eNextState = PLAYER_RUN;
	dynamic_cast<CStage01*>(CSceneMgr::Get_Instance()->Get_CScene())->Set_Scroll(BOOST_SPEED);
}

void Player::Set_Big()
{
	m_bBig = true;
	m_bSuper = true;
	m_dwBig = GetTickCount();
}

void Player::Set_Hit()
{
	m_dwHit = GetTickCount();
	m_dwSuper = GetTickCount();
	//스피드 설정
}
