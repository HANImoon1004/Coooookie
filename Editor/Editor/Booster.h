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


    // CMaps��(��) ���� ��ӵ�
    virtual int Update() override;

};

