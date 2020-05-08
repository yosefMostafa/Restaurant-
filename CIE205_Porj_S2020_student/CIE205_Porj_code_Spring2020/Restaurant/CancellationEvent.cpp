#include "CancellationEvent.h"


CancellationEvent::CancellationEvent(int eTime, int oID):Event(eTime, oID)
{

}
void CancellationEvent::Execute(Restaurant* pRest)
{	
	pRest->Cancel_Order(OrderID);
}
