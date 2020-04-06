#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type,int ArrT, int ServT)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	ArrTime = ArrT;
	ServTime = ServT;
	
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}

void Order::SetArrTime(int Arr)
{
	ArrTime = Arr;
}

void Order::SetServTime(int Serv)
{
	ServTime = Serv;
}

int Order::getServTime()
{
	return ServTime;
}

int Order::getArrTime() const
{
	return ArrTime;
}


void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

