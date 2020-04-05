#pragma once

#include "..\Defs.h"

#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)


         //
	//  Add ing More Data Members As Needed
	//
	// how I will now whether a chief is busy or not    chief_status
	//  Break time  after n orders   I may put it in chief_status                    Breaktime   
	// number of orders done                         completed orders
	int breakduration; 
	int completedOrders;  //number of completed orders 
	// chiefstatus  status;    // at break or free or at work I may not use it in case I have had 2 lists


public:
	Cook();
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setspeed(int);
	void setType(ORD_TYPE) ;

};
