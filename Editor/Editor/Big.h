#pragma once
#include "Maps.h"
class Big :
    public CMaps
{
public:
    Big();
    virtual ~Big();
    Big(MAPINFO& mapInfo, INMAP eINID);


    // CMaps을(를) 통해 상속됨
    virtual void Render(HDC hDC) override;


    // CMaps을(를) 통해 상속됨
    virtual int Update() override;

};

