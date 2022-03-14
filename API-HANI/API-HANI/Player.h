#pragma once
#include "Obj.h"

enum PLAYERID { PLAYER_IDLE, PLAYER_RUN, PLAYER_SLIDE, PLAYER_JUMP, PLAYER_DIE, PLAYER_END };

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
    void   Jump(void);
    void Animation_Change();

private:
    float                   m_fJumpTime;
    float                   m_fJumpPower;
    bool                    m_bJump;
    PLAYERID        m_eNextState;
    PLAYERID        m_eCurState;

};

