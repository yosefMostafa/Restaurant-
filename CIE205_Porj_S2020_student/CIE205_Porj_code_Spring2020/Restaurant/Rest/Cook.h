#pragma once
#include"../Rest/Order.h"
#include "..\Defs.h"

#pragma once

class Cook
{
	int ID;
	
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	
	int speed;		//dishes it can prepare in one clock tick (in one timestep)

	AVAIL_TYPE statue; //The statue of the cook (in break, availble, non availble)
	
	int finishtime;
	
	int breakduration; 
	
	int completedOrders;  //number of completed orders
	
	Order* assignedOrder; // those orders come from waiting lists and then  

public:
	
	Cook();
	
	Cook(int id, int spd, ORD_TYPE t, int breakDur);
	virtual ~Cook();
	

	int GetID() const;
	void SetID(int);

	
	ORD_TYPE GetType() const;
	

	int GetSpeed();
	void SetSpeed(int);
	
	void SetStatue(AVAIL_TYPE t);
	bool IsAvail(AVAIL_TYPE t);
	AVAIL_TYPE GetAvail();
	
	void SetType(ORD_TYPE) ;
	
	void SetOrder(Order* po);
	Order* GetOrder();

	void Increase_Completed_Orders();
	
	int Get_Completed_Orders();
	
	bool IsBreak(int x,int bo);
	bool Breakd(int x);


	int GetFT();
	void SetFT(int x);

};
