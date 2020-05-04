#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDistance;	//order distance
	ORD_TYPE OrdType;		//order type: Normal, vegan, VIP
	double OrdMoney;	//Total order money
	int size;     //size of the order
	int OrdServ; // Order Service Time
public:
	ArrivalEvent(int eTime, int s2, int oID,int s,double o, ORD_TYPE oType);
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType);
	//Add more constructors if needed

	virtual void Execute(Restaurant *pRest);	//override execute function

};

#endif
