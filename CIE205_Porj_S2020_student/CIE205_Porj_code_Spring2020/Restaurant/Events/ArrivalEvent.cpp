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
