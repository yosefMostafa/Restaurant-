#pragma once
#include"../Rest/Order.h"
#include "..\Defs.h"

#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
<<<<<<< HEAD
	AVAIL_TYPE statue; //The statue of the cook (in break, availble, non availble)

         //
	//  Add ing More Data Members As Needed
	//
	//  Break time  after n orders   I may put it in chief_status                    Breaktime   
	// number of orders done                         completed orders
	int breakduration; 
	int completedOrders;  //number of completed orders
	Order* assignedOrder; // those orders come from waiting lists and then  

=======
>>>>>>> parent of b506982... Merge branch 'master' of https://github.com/yosefMostafa/Restaurant-

public:
	Cook();
	Cook(int id, int spd, ORD_TYPE t, int breakDur);
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setorder(Order* p);
	void setspeed(int);
	void setStatue(AVAIL_TYPE t);
	bool Isavail(AVAIL_TYPE t);
	void setType(ORD_TYPE) ;
	///// new funtions //////
	bool isbreak(int x);

};
