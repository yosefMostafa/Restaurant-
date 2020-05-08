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

	int getArrTime() const;
	void SetArrTime(int Arr);

	void SetServTime(int Serv);
	int getServTime();

	void SettotalMoney(double T_Money);

	void setfinishedtime(int f);
	int getfinishedtime()const;

	void SetDistance(int d);
	int GetDistance() const;

	int getsize() const;

	double calcPirority () const;

	void incTotalmoney(int x);
	void setordertype(ORD_TYPE x);
	double gettotalMoney();
	
	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	
	int getcurrentwaittime(int x);
	int gettotalwaittime()const;
	

	Order(int AT, int id, ORD_TYPE r_Type, double tMoney, int size, int dist = 0);

};

#endif