#include "Cook.h"
#include "..\Defs.h"



Cook::Cook(int id, int s, ORD_TYPE t,int b)
{
	ID = id, speed = s; type = t; statue = Avail; breakduration = b; completedOrders = 0;
}

Cook::Cook(int id,int s,ORD_TYPE t,AVAIL_TYPE at,int b)
{
	ID = id, speed = s; type = t; statue = at; breakduration = b; completedOrders = 0;
}



Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}
void Cook::setspeed(int s) {
	speed = s;
}
void Cook::setStatue(AVAIL_TYPE t)
{
	statue = t;
}
bool Cook::Isavail(AVAIL_TYPE t)
{
	if (t==AVAIL_TYPE::Avail)
	{
		return true;
	}
	return false;
}

