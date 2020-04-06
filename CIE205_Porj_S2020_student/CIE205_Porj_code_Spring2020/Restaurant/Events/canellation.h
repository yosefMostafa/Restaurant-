#pragma once

#include"..\Events\Event.h"

class cancellation :public Event {
public:
	cancellation(int eTime, int oID);
	virtual void Execute(Restaurant* pRest);
};