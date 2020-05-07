#include "Cook.h"
#include "..\Defs.h"



Cook::Cook()
{
}

Cook::Cook(int id, int spd, ORD_TYPE t, int breakDur)
{
	ID = id; 
	speed = spd;
	type = t; 
	statue= Avail;
	breakduration = breakDur; 
	completedOrders = 0;
	assignedOrder = nullptr;
	breakfinishtime = 0;
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
bool Cook::isbreak(int x,int bo)
{
	if (x != breakfinishtime) {
		if (completedOrders % bo == 0) {
			setStatue(Break); breakfinishtime = x + breakduration;
			return true;
		}
		else
			return false;
	}
	else {
		setStatue(Avail);
	}
	return false;
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

AVAIL_TYPE Cook::getavail()
{
	return statue;
}

void Cook::setorder(Order* po) {
	assignedOrder = po;
}

Order* Cook::getorder() {
	return assignedOrder;
}
int Cook::getspeed() {
	return speed;
}
void Cook::increasecomporders() {
	completedOrders++;
}
int Cook::getcomporders() {
	return completedOrders;
}