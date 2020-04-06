#include "CancellationEvent.h"


CancellationEvent::CancellationEvent(int eTime, int oID):Event(eTime, oID)
{
	
}
void CancellationEvent::Execute(Restaurant* pRest)
{	
	Node<Order*>* ppRest = pRest->GetNormal().getlisthead()->getNext();
	while (pRest->GetNormal().getlisthead()->getItem())
	{
		if (pRest->GetNormal().getlisthead()->getItem()->GetID() == OrderID && pRest->GetNormal().getlisthead()->getItem()->getArrTime() == EventTime)
		{
			pRest->GetNormal().deleteNode();
		}
		else
			pRest->GetNormal().getlisthead()->getNext();
	}
}