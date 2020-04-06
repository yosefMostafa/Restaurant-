#pragma once
#include "../Restaurant/Events/Event.h"
class CancellationEvent :public Event
{

 public:
	CancellationEvent(int eTime, int oID);
	virtual void Execute(Restaurant* pRest);
};

