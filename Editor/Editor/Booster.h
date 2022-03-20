#pragma once
#include "Maps.h"
class Booster :
    public CMaps
{
public:
    Booster();
    virtual ~Booster();
    explicit Booster(MAPINFO& mapInfo, INMAP eINID);



    virtual void Render(HDC hDC) override;


    // CMaps을(를) 통해 상속됨
    virtual int Update() override;

};

