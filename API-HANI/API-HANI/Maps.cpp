#include "stdafx.h"
#include "Maps.h"

CMaps::CMaps()
{
}

CMaps::CMaps(MAPINFO & mapInfo, INMAP eINID)
	: m_tInfo(mapInfo), m_eINID(eINID)
{
}


CMaps::~CMaps()
{
}
