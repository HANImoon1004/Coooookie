#pragma once
#include "Maps.h"
class Magnet :
    public CMaps
{
public:
    Magnet();
    virtual ~Magnet();
    Magnet(MAPINFO& mapInfo, INMAP eINID);


    // CMaps을(를) 통해 상속됨
    virtual void Render(HDC hDC) override;


    // CMaps을(를) 통해 상속됨
    virtual int Update() override;

};

