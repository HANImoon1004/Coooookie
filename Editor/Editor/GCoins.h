#pragma once
#include "Maps.h"
class CGCoins :
	public CMaps
{
public:
	CGCoins();
	explicit CGCoins(MAPINFO& mapInfo, INMAP eINID);
	virtual ~CGCoins();
	virtual void Render(HDC hDC) override;
};

