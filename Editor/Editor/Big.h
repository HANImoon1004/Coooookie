#pragma once
#include "Maps.h"
class Big :
    public CMaps
{
public:
    Big();
    virtual ~Big();
    Big(MAPINFO& mapInfo, INMAP eINID);


    // CMaps��(��) ���� ��ӵ�
    virtual void Render(HDC hDC) override;


    // CMaps��(��) ���� ��ӵ�
    virtual int Update() override;

};

