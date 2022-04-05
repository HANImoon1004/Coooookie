#pragma once
#include "Obj.h"

enum PETID { PET_IDLE, PET_MAGNET, PET_END };
class CPet :
    public CObj
{
public:
    CPet();
    ~CPet();

public:
    // CObj을(를) 통해 상속됨
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;

public:
    void Animation_Change();

    void Set_Magnet();

private:
    PETID       m_eCurState;
    PETID       m_eNextState;
    
    DWORD     m_dwTime;
    bool           m_bMagnet;


};

