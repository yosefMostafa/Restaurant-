#include "../Restaurant"


CancellationEvent::CancellationEvent(int eTime, int oID):Event(eTime, oID)
{

}
void CancellationEvent::Execute(Restaurant* pRest)
{
	Node<Order*>* P = pRest->GetNormal().getlisthead();
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
	}
}
