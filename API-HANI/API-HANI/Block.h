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
	virtual int	 Update() override;
	virtual void Render(HDC hDC) override;
	void Release();

public:
	virtual void Animation_Change() override;
	virtual void Move_Frame() override;


	// CMaps을(를) 통해 상속됨
	virtual int Late_Update(HDC hDC) override;

	
};

