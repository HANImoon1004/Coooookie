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
};

