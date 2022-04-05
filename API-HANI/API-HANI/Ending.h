#pragma once
#include "Scene.h"
class Ending :
    public CScene
{
public:
    Ending();
    virtual ~Ending();

    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
};

