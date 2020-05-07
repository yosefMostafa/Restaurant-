#include"..\Events\promotion.h"

promotion::promotion(int eTime, int oID , int Exm) :Event(eTime, oID)
{
	EXmoney = Exm;
}
void promotion::Execute(Restaurant* pRest)
{
	pRest->promoteOrder(OrderID, EXmoney);

}
