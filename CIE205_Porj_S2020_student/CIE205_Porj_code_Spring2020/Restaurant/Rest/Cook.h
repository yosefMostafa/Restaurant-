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

         //
	
	int breakfinishtime;
	int breakduration; 
	int completedOrders;  //number of completed orders
	Order* assignedOrder; // those orders come from waiting lists and then  


public:
	Cook();
	Cook(int id, int spd, ORD_TYPE t, int breakDur);
	virtual ~Cook();
	
	int GetID() const;
	void setID(int);

	ORD_TYPE GetType() const;
	
	int getspeed();
	void setspeed(int);
	
	void setStatue(AVAIL_TYPE t);
	bool Isavail(AVAIL_TYPE t);
	AVAIL_TYPE getavail();
	
	void setType(ORD_TYPE) ;
	
	void setorder(Order* po);
	void increasecomporders();
	int getcomporders();
	Order* getorder();
	
	bool isbreak(int x,int bo);
	bool Breakd(int x);

};
