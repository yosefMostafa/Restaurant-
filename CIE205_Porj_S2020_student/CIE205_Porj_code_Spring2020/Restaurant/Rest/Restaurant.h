#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include"../Generic_DS/Llist.h"
#include "..\Events\Event.h"


#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	
	/// ==>
	
	
	
	//
	// TODO: Add More Data Members As Needed
	//
	//
	// for the cooks 
	Queue<Cook*> NormalCQueue;
	Queue<Cook*> VeganCQueue;        //those three queues have all the available cooks
	Queue<Cook*> VIPCQueue;
	Queue<Cook*> BusyCooks;    // this list contains all the cook who are preparing orders or in the break duration
	//
	//

	//
	//for the orders 
	Queue<Order*> VGNWaiting;        //those three have all orders On the waiting list
	Queue<Order*> NOwaiting;              
	Queue<Order*> VIPwaiting;
	Queue<Order*> finishedqueue;
	// linked list or array list

	int BO; // repersent restaurnat rules to give a cook a break after n orders 

public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void load();
	void interactive();

	void AddtoNormal(Order* po);
	void AddtoVGN(Order* po);
	void AddVIP(Order* po);

	void AddCook(Cook* C);

	//void RemoveNormal(int Id);
	//void RemoveVGN(int Id);

	GUI* GetGUI();

	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//
	bool cancelOrder(int id);
	bool promoteOrder(int id , int extra);


/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	
	void serveorders(int timestep);
	void finished(int timestep);
	void assigncook(Order* tempo, Cook* tempc,int timestep);
	//void Addtoserving(Order* po);
	//void check(int timestep);
	//void addorder(Order* po,ORD_TYPE t);

/// ================================================================================================== 



};

#endif