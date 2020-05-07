#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"
#include"..\Rest\Order.h"




ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType) : Event(eTime, oID)
{
	OrdType = oType;//demo constructor
}

ArrivalEvent::ArrivalEvent(int eTime, int oID, int s, double o, ORD_TYPE oType, int dist) : Event(eTime, oID)
{
	OrdType = oType; size = s; OrdMoney = o; OrdDistance = dist;
	
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1



	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2
	/*Order* pOrd = new Order(OrderID, (ORD_TYPE)(OrdType), EventTime, OrdServ);
	pRest->addorder(pOrd, (ORD_TYPE)(OrdType));
	pOrd->setStatus((ORD_STATUS)(SRV));
	pRest->AddtoDemoQueue(pOrd);
	pRest->Addtoserving(pOrd);*/

	/////////////  THE NEW EXECUTION FOR ARRIVAL EVENT  ////////

	// FIRST STEP  --->> ALOCATE THE ORDER  //  DONE
	// SECOND STEP  --->> ACCORDING TO THE ORDER TYPE I WILL ADD IT TO THE CORESPONDING WAITING LIST 
	// REGARDING THE SERVING LIST IT WILL BE PERFORMED IN ASSIGN TO A COOK IN THE RESTAURANT.CPP

	Order* pOrd= new Order(EventTime, OrderID, OrdType, OrdMoney,size, OrdDistance);

	switch (OrdType)	
	{
	case TYPE_NRM:
		pRest->AddtoNormal(pOrd);
		break;
	case TYPE_VGAN:
		pRest->AddtoVGN(pOrd);
		break;
	case TYPE_VIP:
		pRest->AddVIP(pOrd);
		break;
	

	};

}
