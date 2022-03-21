#pragma once
#include "Obj.h"

enum PLAYERID {
	PLAYER_IDLE, PLAYER_RUN, PLAYER_SLIDE,
	PLAYER_JUMP, PLAYER_DOUBLEJUMP,
	PLAYER_HIT, PLAYER_DIE, PLAYER_DEAD,
	PLAYER_BOOSTER, PLAYER_BIG,
	PLAYER_MAGNET, PLAYER_END
};

class Player :
	public CObj
{
public:
	Player();
	virtual ~Player();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void                          Key_Input();
	void                          Key_Check();
	void                          Update_Rect();
	void                           Move_Frame();

	bool                          Jump(void);
	void                          Jump_Stop();

	void                          Animation_Change();

	void                          Super_Cookie();

	void                          Set_Hp(int iHp) { m_iHp += iHp; }
	void                          Set_Status(PLAYERID eID) { m_eNextState = eID; }
	void                           Set_Invincible() { m_bSuper = true; }
	void                           Set_Booster();
	void                            Set_Big();
	void                            Set_Hit();

	int                             Get_Money() { return m_iMoney; }
	int                             Get_Score() { return m_iScore; }
	int                             Get_Hp() { return m_iHp; }
	PLAYERID               Get_Status() { return m_eCurState; }
	bool                            Get_isSuper() { return m_bSuper; }
	bool                            Get_Dead() { return m_bDead; }
		void    Set_Score(int iScore) { m_iScore += iScore; }
	void    Set_Money(int iMoney) { m_iMoney += iMoney; }

private:

	int                        m_iHp;
	int                        m_iScore;
	int                        m_iMoney;
	float                   m_fHeight;
	float                   m_fJumpTime;
	float                   m_fJumpPower;
	float                   m_fStartY = 0.f;
	DWORD               m_dwTime = 0.f;
	DWORD               m_dwRunning;
	DWORD               m_dwHit;
	DWORD               m_dwSuper;
	DWORD               m_dwSupertime;
	DWORD               m_dwBig;
	DWORD               m_dwBooster;
	DWORD				m_dwDie;


	bool                    m_bJump;
	bool                    m_bDoJump;
	bool                    m_bSuper; //무적상태
	bool                    m_bBooster; //부스터
	bool                    m_bBig; //거대화
	bool                    m_bHit; //피격시

	PLAYERID        m_eNextState;
	PLAYERID        m_eCurState;
};

