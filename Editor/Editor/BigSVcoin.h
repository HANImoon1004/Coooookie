#pragma once
#include "Maps.h"
class BigSVcoin :
    public CMaps
{
public:
	BigSVcoin();
	explicit BigSVcoin(MAPINFO& mapInfo, INMAP eINID);
	virtual ~BigSVcoin();

public:
	virtual void Render(HDC hDC) override;

	// CMaps��(��) ���� ��ӵ�
	virtual int Update() override;
};

