#include"../Events/PromotionEvent.h"

promotion::promotion(int eTime, int oID , int Exm) :Event(eTime, oID)
{
	EXmoney = Exm;
}
void promotion::Execute(Restaurant* pRest)
{
	pRest->Promote_Order(OrderID, EXmoney);
}
