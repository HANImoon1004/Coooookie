#pragma once
#include "Maps.h"
class CCoin :
	public CMaps
{
public:
	CCoin();
	explicit CCoin(MAPINFO& mapInfo, INMAP eINID);
	virtual ~CCoin();

public:
	virtual void Render(HDC hDC) override;

	// CMaps을(를) 통해 상속됨
	virtual int Update() override;
};

