#pragma once
#include "Maps.h"
class Magnet :
    public CMaps
{
public:
    Magnet();
    virtual ~Magnet();
    Magnet(MAPINFO& mapInfo, INMAP eINID);


    // CMaps��(��) ���� ��ӵ�
    virtual void Render(HDC hDC) override;


    // CMaps��(��) ���� ��ӵ�
    virtual int Update() override;

};

