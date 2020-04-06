#pragma once
#include "Event.h"


//class for the cancellation event
class cancellation : public Event
{
	
public:

	cancellation(int etime, int ordID);
 
	//Add more constructors if needed

	virtual void Execute(Restaurant* pRest);	//override execute function


};



