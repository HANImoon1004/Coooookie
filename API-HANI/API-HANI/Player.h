#pragma once
#include "Obj.h"

enum PLAYERID { PLAYER_IDLE, PLAYER_RUN, PLAYER_SLIDE, PLAYER_JUMP, PLAYER_DOUBLEJUMP, PLAYER_DIE, PLAYER_END };

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
    void Key_Input();
    void Key_Check();
    void Update_Rect();
    bool   Jump(void);
    void Jump_Stop();
    void Animation_Change();

private:


    float                   m_fHeight;
    float                   m_fJumpTime;
    float                   m_fJumpPower;
    float                   m_fStartY = 0.f;
    DWORD               m_dwTime = 0.f;
    bool                    m_bJump;
    bool                    m_bDoJump;
    PLAYERID        m_eNextState;
    PLAYERID        m_eCurState;

};

