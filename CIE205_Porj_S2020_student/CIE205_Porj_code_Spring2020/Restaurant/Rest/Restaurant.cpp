#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include"../CancellationEvent.h"
#include"..\Events\promotion.h"


Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
	
	load();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		interactive(NormalCQueue,VeganCQueue,VIPCQueue);
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		if (pGUI)
			delete pGUI;
}
Llist<Order*> Restaurant::GetNormal() const
{
	return NOwaiting;
}
GUI* Restaurant::GetGUI()
{
	return pGUI;
}

void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);

}
void::Restaurant::load() {
	ifstream file("data.txt");
	int Normalcooks, vegancooks, vipcooks;
	int Normalcooksspeed, vegancooksspeed, vipcooksspeed;
	int breaktime, normalbreaktime, veganbreaktime, vipbreaktime;
	int autopromotionlimit;
	int numofevents;

	file >> Normalcooks >> vegancooks >> vipcooks;
	file >> Normalcooksspeed >> vegancooksspeed >> vipcooksspeed; 
	file >> normalbreaktime >> veganbreaktime >> vipbreaktime;
	file >> autopromotionlimit;
	file >> numofevents;//getting the information of the cook from file

	sum = Normalcooks + vegancooks + vipcooks;
	

	for (int i = 0; i < Normalcooks; i++) {
		Cook *pc=new Cook((i + 1) * 2 + sum, Normalcooksspeed, (ORD_TYPE)(TYPE_NRM), normalbreaktime);
		NormalCQueue.enqueue(pc);//setting the id and type for the normal cooks 
	}
	for (int i = Normalcooks; i < vegancooks+ Normalcooks; i++) {
		Cook *pc=new Cook((i + 1) * 3 + sum, vegancooksspeed, (ORD_TYPE)(TYPE_VGAN), veganbreaktime);
		VeganCQueue.enqueue(pc);//setting the id and type for the vegan cooks
	}
	
	for (int i = vegancooks + Normalcooks; i < sum; i++) {
		Cook* pc = new Cook((i + 1) * 5 + sum, vipcooksspeed, (ORD_TYPE)(TYPE_VIP), vipbreaktime);
		VIPCQueue.enqueue(pc);//setting the id and type for the VIP cooks
	}

	//a break event should be created here

	Event* pEv;
	for (int i = 0; i < numofevents; i++) {
		char event,type;
		ORD_TYPE typ= TYPE_CNT;

		file >> event;

		if (event=='R') {
			int timestep, ID, size,money;

			file >> type;

			switch (type) {
			case 'N':typ = TYPE_NRM;
				break;
			case 'G':typ = TYPE_VGAN;
				break;
			case'V':typ= TYPE_VIP; //to detemine the type 
			}
		
			file >> timestep >> ID >> size >> money;

			pEv = new ArrivalEvent(timestep, ID, size,money,(ORD_TYPE)typ);
			EventsQueue.enqueue(pEv);//adding the arrival evevnt in a queue
		}
		else if (event == 'X') {
			int timestep, ID;
			file >> timestep >> ID;

			pEv = new CancellationEvent(timestep, ID);
			EventsQueue.enqueue(pEv);//adding the cancellation evevnt in a queue
		}
		else if(event =='P') {
			int timestep, ID, Exmoney;
			file >> timestep >> ID >> Exmoney;
			
			pEv = new promotion(timestep, ID,Exmoney);
			EventsQueue.enqueue(pEv);//adding the cancellation evevnt in a queue
		}

	}

}
void::Restaurant::interactive(Queue < Cook*> np, Queue < Cook*> gp, Queue < Cook*> vp){
	int CurrentTimeStep = 1;
	
	

	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);


		//The next line may add new orders to the DEMO_Queue
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step


/////////////////////////////////////////////////////////////////////////////////////////
		/// The next code section should be done through function "FillDrawingList()" once you
		/// decide the appropriate list type for Orders and Cooks

		//Let's add ALL randomly generated Cooks to GUI::DrawingList7
		Cook* pc;
		Order* pOrd;
		while (np.dequeue(pc))
			vp.enqueue(pc);
		while (gp.dequeue(pc))
			vp.enqueue(pc);
		Cook** pc2 = vp.toArray(sum);
		
		for (int j = 0; j < sum; j++) {
			pGUI->AddToDrawingList(pc2[j]);
		}

		//Let's add ALL randomly generated Ordes to GUI::DrawingList
		int size = 0;
		Order **Demo_Orders_Array = DEMO_Queue.toArray(size);

		for (int i = 0; i < size; i++)
		{
			pOrd = Demo_Orders_Array[i];
			pGUI->AddToDrawingList(pOrd);
		}
	//	///////////////////////////////////////////////////////////////////////////////////////

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//Begin of DEMO-related functions

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Events randomly... In next phases, Events should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();
		
	//Just for sake of demo, generate some cooks and add them to the drawing list
	//In next phases, Cooks info should be loaded from input file
	int C_count = 12;	
	Cook *pC = new Cook[C_count];
	int cID = 1;

	for(int i=0; i<C_count; i++)
	{
		cID+= (rand()%15+1);	
		pC[i].setID(cID);
		pC[i].setType((ORD_TYPE)(rand()%TYPE_CNT));
	}	

		
	int EvTime = 0;

	int O_id = 1;
	
	//Create Random events and fill them into EventsQueue
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		O_id += (rand()%4+1);		
		int OType = rand()%TYPE_CNT;	//Randomize order type		
		EvTime += (rand()%5+1);			//Randomize event time
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType);
		EventsQueue.enqueue(pEv);

	}	

	// --->   In next phases, no random generation is done
	// --->       EventsQueue should be filled from actual events loaded from input file

	
	
	
	
	//Now We have filled EventsQueue (randomly)
	int CurrentTimeStep = 1;
	

	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		//The next line may add new orders to the DEMO_Queue
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		

/////////////////////////////////////////////////////////////////////////////////////////
		/// The next code section should be done through function "FillDrawingList()" once you
		/// decide the appropriate list type for Orders and Cooks
		
		//Let's add ALL randomly generated Cooks to GUI::DrawingList
		for(int i=0; i<C_count; i++)
			pGUI->AddToDrawingList(&pC[i]);
		
		//Let's add ALL randomly generated Ordes to GUI::DrawingList
		int size = 0;
		Order** Demo_Orders_Array = DEMO_Queue.toArray(size);
		
		for(int i=0; i<size; i++)
		{
			pOrd = Demo_Orders_Array[i];
			pGUI->AddToDrawingList(pOrd);
		}
/////////////////////////////////////////////////////////////////////////////////////////

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}

	delete []pC;


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{

	DEMO_Queue.enqueue(pOrd);
}

/// ==> end of DEMO-related function
//////////////////////////////////////////////////////////////////////////////////////////////




