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
	//  Add ing More Data Members As Needed
	//
	//  Break time  after n orders   I may put it in chief_status                    Breaktime   
	// number of orders done                         completed orders
	int breakduration; 
	int completedOrders;  //number of completed orders
	Order* assignedOrder; // those orders come from waiting lists and then  


public:
	Cook();
	Cook(int id, int spd, ORD_TYPE t, int breakDur);
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setspeed(int);
	void setStatue(AVAIL_TYPE t);
	bool Isavail(AVAIL_TYPE t);
	void setType(ORD_TYPE) ;
	void setorder(Order* po);
	int getspeed();
	void increasecomporders();
	int getcomporders();
	Order* getorder();
	///// new funtions //////
	bool isbreak(int x);

};
