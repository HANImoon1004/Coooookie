#pragma once

#include "stdafx.h"
#include "CollisionMgr.h"

#include "Maps.h"
#include "Block.h"
#include "KeyMgr.h"

CollisionMgr::CollisionMgr()
{
}

CollisionMgr::~CollisionMgr()
{
}

void CollisionMgr::Collision_Mouse(list<CMaps*>& Dest, RECT rect)
{
	RECT rc{};

	for (auto& DestIter : Dest) //리스트에 있는 거 돌려야하니까 
	{
		if (IntersectRect(&rc, &(DestIter->Get_Rect()), &rect)) //충돌 했으면
		{
			//DestIter의 객체를 사라지게 해야해 
			DestIter->Set_Dead();
		}
	}


}


