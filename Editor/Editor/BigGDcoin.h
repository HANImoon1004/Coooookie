#pragma once
#include "Maps.h"
class BigGDcoin :
    public CMaps
{
public:
	BigGDcoin();
	explicit BigGDcoin(MAPINFO& mapInfo, INMAP eINID);
	virtual ~BigGDcoin();


	virtual void Render(HDC hDC) override;

	// CMaps��(��) ���� ��ӵ�
	virtual int Update() override;
};

