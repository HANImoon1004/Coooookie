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

	// CMaps을(를) 통해 상속됨
	virtual int Update() override;
};

