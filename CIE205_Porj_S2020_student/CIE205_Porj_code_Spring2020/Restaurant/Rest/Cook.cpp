#include "Cook.h"
#include "..\Defs.h"



Cook::Cook()
{
}

Cook::Cook(int id, int spd, ORD_TYPE t, int breakDur)
{
	ID = id;                            speed = spd;
	type = t;                           statue= Avail;
	breakduration = breakDur;           completedOrders = 0;
	assignedOrder = nullptr;            finishtime = 0;
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


void Cook::SetID(int id)
{
	ID = id;
}

void Cook::SetType(ORD_TYPE t)
{
	type = t;
}

bool Cook::Breakd(int x) 
{
	if (x == finishtime) 
	{
		SetStatue(Avail);
		return true;
	}
	return false;
}

int Cook::GetFT()
{
	return finishtime;
}

void Cook::SetFT(int x)
{
	finishtime = x;
}

bool Cook::IsBreak(int x,int bo)
{
	if (completedOrders % bo == 0)
	{
		SetStatue(Break); 
	    finishtime = x + breakduration;
		return true;
	}
	return false;
}

void Cook::SetSpeed(int s) 
{
	speed = s;
}

void Cook::SetStatue(AVAIL_TYPE t)
{
	statue = t;
}

bool Cook::IsAvail(AVAIL_TYPE t)
{
	if (t==AVAIL_TYPE::Avail)
	{
		return true;
	}
	return false;
}

AVAIL_TYPE Cook::GetAvail()
{
	return statue;
}

void Cook::SetOrder(Order* po) {
	assignedOrder = po;
}

Order* Cook::GetOrder() 
{
	return assignedOrder;
}

int Cook::GetSpeed()
{
	return speed;
}

void Cook::Increase_Completed_Orders() 
{
	completedOrders++;
}

int Cook::Get_Completed_Orders()
{
	return completedOrders;
}