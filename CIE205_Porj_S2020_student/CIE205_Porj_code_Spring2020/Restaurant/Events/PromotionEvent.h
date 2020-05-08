#pragma once
#pragma once
#include"..\Events\Event.h"
#include"../Rest/Restaurant.h"

class promotion:public Event 
{
private:
	
	int EXmoney;

public:
	
	promotion(int eTime, int oID,int Exm);
	
	virtual void Execute(Restaurant* pRest);

};