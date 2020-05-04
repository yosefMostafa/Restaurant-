#include "CancellationEvent.h"


CancellationEvent::CancellationEvent(int eTime, int oID):Event(eTime, oID)
{

}
void CancellationEvent::Execute(Restaurant* pRest)
{
	//Order* op;
	//Queue<Order*> p=pRest->GetNormal();
	//Queue<Order*> p2;
	//while (p.dequeue(op))
	//{
	//	int a, b;
	//	a = op->GetID(); b = op->getArrTime();
	//	if (!(a == OrderID && b == EventTime)) {
	//		p2.enqueue(op);
	//	}
	//}
	//while (p2.dequeue(op))
	//	p.enqueue(op);
	/*Node<Order*>* P = pRest->GetNormal().getlisthead();
	while (P)
	{
		if (P->getItem()->GetID() == OrderID && P->getItem()->getArrTime() == EventTime)
		{
			Order* DummyOrder;
			pRest->GetNormal().deleteNode(P,DummyOrder);
			GUI* pGUI = pRest->GetGUI();
			pGUI->PrintMessage("Order Successfully Canceled");
		}
		else
			P = P->getNext();
	}*/
}
