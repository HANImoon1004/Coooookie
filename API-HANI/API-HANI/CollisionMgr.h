#pragma once
#include "Include.h"
#include "Maps.h"
#include "Obj.h"

class CollisionMgr
{
public:
	CollisionMgr();
	~CollisionMgr();

public:
	static void Collision_RectEX(list<CMaps*> Dest, list<CObj*> Sour);

	static bool Collision_Rect(list<CMaps*> Dest, list<CObj*> Sour);

	static bool Collision_Block(list<CMaps*> Dest, list<CObj*> Sour);

	static bool Collision_Map(list<CMaps*> Dest, list<CObj*> Sour);

	static bool Collision_Item(list<CMaps*>& Dest, list<CObj*>&  Sour);

	static void Collision_Otte(list<CMaps*>& Dest, list<CObj*>& Sour);

private:
	static bool Check_Sphere(const CObj* pDstObject, const CObj* rSrcObject);
	static bool Check_Rect(CMaps* pDest, CObj* pSour, float* pfX, float* pfY);


};

