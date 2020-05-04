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
	// I propose to delete FT as it can be concluded
	


	//
	// TODO: Add More Data Members As Needed
	//

	int OrderSize; // no of dishes of each order need it to calc the SV
	int waitTime; // time consumed from AT to assign the order for a chief I need it as it is important in case we want it to promote the order
	

public:
	Order(int ID, ORD_TYPE r_Type,int a,int s);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;
	void SetArrTime(int Arr);
	void SetServTime(int Serv);
	int getServTime();
	int getArrTime() const;
	void SetDistance(int d);
	int GetDistance() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	
	//
	// TODO: Add More Member Functions As Needed
	//

	Order(int AT, int id, ORD_TYPE r_Type, double tMoney, int size, int dist = 0);

};

#endif
