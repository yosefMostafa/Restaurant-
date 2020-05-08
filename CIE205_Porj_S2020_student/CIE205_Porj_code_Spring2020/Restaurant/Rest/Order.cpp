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

void Order::SetTotal_Money(double T_Money)
{
	totalMoney = T_Money;
}

int Order::GetServTime()
{
	return ServTime;
}

int Order::GetArrTime() const
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


void Order::SetStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::GetStatus() const
{
	return status;
}

int Order::Get_Current_Wait_Time(int x)
{
	return x - ArrTime;
}

int Order::Get_Total_Wait_Time() const
{
	return FinishTime - ArrTime - ServTime;
}

Order::Order(int AT, int id, ORD_TYPE r_Type, double tMoney, int size, int dist)
{
	ArrTime = AT; ID = id; type = r_Type; totalMoney = tMoney;
	OrderSize = size; Distance = dist;
	status = WAIT;
	FinishTime = -1;
	ServTime = -1;
}
int Order::GetSize() const {
	return OrderSize;
}
double Order::Calc_Pirority() const
{
	return 3*totalMoney - OrderSize -Distance;
}
void Order::incTotalmoney(int x)
{
	totalMoney += x;
}
void Order::SetOrderType(ORD_TYPE x)
{
	type = x;
}
double Order::GetTotalMoney()
{
	return totalMoney;
}
void Order::Set_Finished_Time(int f) {
	FinishTime = f;
}
int Order::Get_Finished_Time() const {
	return FinishTime;
}
