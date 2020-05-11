#pragma once
#include "Events/Event.h"
#include "..\Restaurant\Rest\Restaurant.h"
#include "../Restaurant/Rest/Cook.h"

class HealthProblems :public Event
{
private:

public:
	HealthProblems(int eTime, int oID);

	virtual void Execute(Restaurant* pRest);
};

