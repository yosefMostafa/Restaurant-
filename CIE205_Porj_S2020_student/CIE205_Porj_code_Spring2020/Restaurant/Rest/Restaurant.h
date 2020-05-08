#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include"../Generic_DS/Llist.h"
#include "..\Events\Event.h"
#include"../PQueue.h"


#include "Order.h"

// it is the maestro of the project
class Restaurant
{
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file


	// for the cooks
	Queue<Cook*> NormalCQueue;
	Queue<Cook*> VeganCQueue;        //those three queues have all the available cooks
	Queue<Cook*> VIPCQueue;
	PQueue<Cook*> BusyCooks;    // this list contains all the cook who are preparing orders or in the break duration
	//

	//
	//for the orders
	Queue<Order*> VGNWaiting;        //those three have all orders On the waiting list
	Queue<Order*> NOwaiting;
	PQueue<Order*> VIPwaiting;
	Queue<Order*> finishedqueue;

	int BO, AutoPT;// repersent restaurnat rules to give a cook a break after n orders
	int TOTALautoP;
public:

	Restaurant();
	~Restaurant();

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep

	void RunSimulation();
	void load();

	void interactive();
	void Run(int& time);
	void stepbystep();
	void silent();
	void OutPut();

	void AddtoNormal(Order* po);
	void AddtoVGN(Order* po);
	void AddVIP(Order* po);

	void AddCook(Cook* C);


	GUI* GetGUI();

	void FillDrawingList();
	void print(int time);
	string typetostring(Order* tempo);
	string typetostring(Cook* tempc);

	bool cancelOrder(int id);
	bool promoteOrder(int id , int extra);
	int Autop(int timestep);


/// ===================       =================


	void serveorders(int timestep); //   adding cooks to serving list
	void finished(int timestep);  // to check if a cook has finished coking
	void assigncook(Order* tempo, Cook* tempc,int timestep,int count);   // helper function used inside servorders used to assaign cook to an aorder

	void freememory();
/// ==================================================================================================

	bool isprogramfnished();

};

#endif
