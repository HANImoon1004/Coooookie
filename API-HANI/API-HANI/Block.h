#pragma once
#include "Maps.h"

class Maps;
class CBlock :
	public CMaps
{
public:
	CBlock();
	explicit CBlock(MAPINFO& mapInfo, INMAP eINID);
	virtual ~CBlock();

public:
	virtual void Render(HDC hDC) override;
	void Release();
};

