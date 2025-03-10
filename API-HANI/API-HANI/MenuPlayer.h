#pragma once
#include "Obj.h"

enum MENUID { MENU_IDLE, MENU_HAPPY, MENU_END };

class MenuPlayer :
    public CObj
{
public:
    MenuPlayer();
    MenuPlayer(TCHAR* pFrameKey, FRAME tFrame, float fX, float fY);
    virtual ~MenuPlayer();

public:
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;


public:
   
public:

    MENUID              m_eCurState;
    MENUID            m_eNextState;


};

