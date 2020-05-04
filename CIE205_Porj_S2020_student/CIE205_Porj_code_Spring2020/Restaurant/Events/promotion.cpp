#include"..\Events\promotion.h"

promotion::promotion(int eTime, int oID , int Exm) :Event(eTime, oID)
{
	EXmoney = Exm;
}
void promotion::Execute(Restaurant* pRest)
{
	Order* op;
	Queue<Order*> p = pRest->GetNormal();

	Queue<Order*> Temp;
	while (p.dequeue(op))
	{
		int ID,Money;
		ID = op->GetID();
		Money = op->GetTotalMoney();
		if (ID == OrderID)
		{
			Temp.enqueue(op);

		}
		
	}
	while (Temp.dequeue(op))
	{
		p.enqueue(op);
	}
}
