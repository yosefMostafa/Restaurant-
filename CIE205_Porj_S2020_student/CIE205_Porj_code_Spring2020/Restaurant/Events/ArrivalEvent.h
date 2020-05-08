#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"


class ArrivalEvent: public Event
{
	int OrdDistance;	//order distance
	
	ORD_TYPE OrdType;		//order type: Normal, vegan, VIP
	
	double OrdMoney;	//Total order money
	
	int size;     //size of the order
	
public:

	ArrivalEvent(int eTime, int oID, ORD_TYPE oType);
	
	ArrivalEvent(int eTime, int oID, int s, double o, ORD_TYPE oType, int distance);

	virtual void Execute(Restaurant* pRest);

};

#endif
