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

	// CMaps을(를) 통해 상속됨
	virtual int Update() override;
};

