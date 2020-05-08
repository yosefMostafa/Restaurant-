#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 ) 
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times	

	int OrderSize; // no of dishes of each order need it to calc the SV

public:

	Order(int ID, ORD_TYPE r_Type,int a,int s);
	
	virtual ~Order();

	int GetID();
	
	ORD_TYPE GetType() const;

	void SetArrTime(int Arr);

	int GetArrTime() const;
	
	void SetServTime(int Serv);
	
	int GetServTime();

	void SetTotal_Money(double T_Money);

	double GetTotalMoney();

	void Set_Finished_Time(int f);
	
	int Get_Finished_Time()const;

	void SetDistance(int d);
	
	int GetDistance() const;

	int GetSize() const;

	double Calc_Pirority () const;

	void incTotalmoney(int x);
	
	void SetOrderType(ORD_TYPE x);
	
	void SetStatus(ORD_STATUS s);
	
	ORD_STATUS GetStatus() const;
	
	int Get_Current_Wait_Time(int x);
	
	int Get_Total_Wait_Time()const;
	
	Order(int AT, int id, ORD_TYPE r_Type, double tMoney, int size, int dist = 0);

};

#endif