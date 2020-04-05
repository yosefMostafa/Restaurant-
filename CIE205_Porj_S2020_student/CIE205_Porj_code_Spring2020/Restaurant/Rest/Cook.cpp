#include "Cook.h"


Cook::Cook(int id,int s,ORD_TYPE t)
{
	ID = id, speed = s; type = t;
}

Cook::Cook()
{
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


