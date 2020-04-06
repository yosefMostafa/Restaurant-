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
	Llist<Cook*> BusyCooks;    // this list contains all the cook who are preparing orders or in the break duration
	//
	//

	//
	//for the orders 
	Queue<Order*> VOWaiting;        //those three have all orders On the waiting list
	Llist<Order*> NOwaiting;              
	Llist<Order*> VOwaiting;
	Llist<Order*> finishedOrders; 
	// linked list or array list

	int sum;

public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void load();
	void interactive(Queue < Cook*> np, Queue < Cook*> gp, Queue < Cook*> vp);
	Llist<Order*> GetNormal() const;


	GUI* GetGUI();

	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//


/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

/// ================================================================================================== 



};

#endif