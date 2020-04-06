#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"
#include"..\Rest\Order.h"


ArrivalEvent::ArrivalEvent(int eTime, int s2, int oID, int s, double o, ORD_TYPE oType) :Event(eTime, oID)
{
	OrdType = oType; size = s; OrdMoney = o; OrdServ = s2;
}

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType) : Event(eTime, oID)
{
	OrdType = oType;//demo constructor
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2
	Order* pOrd = new Order(OrderID, (ORD_TYPE)(OrdType), EventTime, OrdServ);
	pOrd->setStatus((ORD_STATUS)(WAIT));
	pRest->AddtoDemoQueue(pOrd);
	pRest->Addtoserving(pOrd);
}
