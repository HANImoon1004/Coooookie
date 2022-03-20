#pragma once
#include "Include.h"
#include "Maps.h"


class CollisionMgr
{
public:
	CollisionMgr();
	~CollisionMgr();

public:

	static void Collision_Mouse(list<CMaps*>& Dest, RECT rect);

private:



};

