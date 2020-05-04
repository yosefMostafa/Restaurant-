#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, int a, int s)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	ArrTime = a; ServTime = s;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
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


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}

void Order::SetTotalMoney(int Mon)
{
	totalMoney = Mon;
}

int Order::GetTotalMoney()
{
	return totalMoney;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

Order::Order(int AT, int id, ORD_TYPE r_Type, double tMoney, int size, int dist)
{
	ArrTime = AT; ID = id; type = r_Type; totalMoney = tMoney;
	OrderSize = size; Distance = dist;
	status = WAIT;
}

