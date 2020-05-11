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
	GUI *pGUI; //Pointer to GUI
	
	Queue<Event*> Events_Queue;	//Queue of all events that will be loaded from file


	Queue<Cook*> Normal_Cook_Queue; //Queue that contains the available normal cooks
	Queue<Cook*> Vegan_Cook_Queue;    //Queue that contains the available vegan cooks
	Queue<Cook*> VIP_Cook_Queue;      //Queue that contains the available VIP cooks
	PQueue<Cook*> BusyCooks;    // Queue that contains  contains all the cook who are preparing orders or in the break duration
	

	Queue<Order*> Vegan_Waiting;        //those three have all orders On the waiting list
	Queue<Order*> Normal_Waiting;      //Queue that contains the Noraml orders on the waiting list
	PQueue<Order*> VIP_Waiting;        //Queue that contains the vip ordesr on the waiting list
	Queue<Order*> Finished_Orders;     //Queue that contains the finished orders

	int BO , AutoPT; // Represent restaurnat rules to give a cook a break after n orders, repersents promoted orders
	
	int T_AutoP; //Represent total promoted orders
public:
	Restaurant();
	~Restaurant();

	void ExecuteEvents(int TimeStep);	////Function to executes all events at current timestep
	
	void RunSimulation(); //Function to  run the simulation

	void load(); //Function to load from a file


	void Interactive();
	void Run(int& time);
	void Step_By_Step(); 
	void Silent(); //function to implement mode silent

	void OutPut(); //Function to print the output


	void AddtoNormal(Order* po); //Function to add order to normal queue
	void AddtoVGN(Order* po); //Function to add order to vigan queue
	void AddVIP(Order* po); //Function to add order to VIP queue


	void AddCook(Cook* C); //Function to add Cooks

	GUI* GetGUI(); //Function to get GUI pointer
	void Fill_Drawing_List(); //Function to fill the drawing list
	

	void Print(int time); // Function to print on the statues bar 
	
	string Type_To_String(Order* tempo); // Function to transfer type of Orders to string
	string Type_To_String(Cook* tempc); // Function to transfer type of Cooks to string

	bool Cancel_Order(int id);  // Function to cancel order
	bool Promote_Order(int id , int extra); // Function to promote order
	int Auto_Promotion(int timestep); //Function to auto promote


	void ServOrders(int timestep); //   adding cooks to serving list
	void IsFinished(int timestep);  // to check if a cook has finished cooking
	void Assign_Cook(Order* tempo, Cook* tempc,int timestep,int count);   // helper function used inside servorders used to assaign cook to an aorder


	void Free_Memory(); //Function to delete all objects of orders and cooks
	bool Is_Program_Finished(); 
};

#endif
