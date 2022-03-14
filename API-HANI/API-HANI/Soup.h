#pragma once
#include "Obj.h"

enum BONGJI { BONGJI_IDLE, BONGJI_SNOW, BONGJI_END };

class Soup :
    public CObj
{
public:
    Soup();
    virtual ~Soup();

public:
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;

private:
    DWORD           dwOldTime;
    int                     m_iDrawID;
    int                     m_iDrawID2;
};

