#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include"..\CancellationEvent.h"
#include"../Events/PromotionEvent.h"
#include<string>

using namespace std;

Restaurant::Restaurant()
{
	pGUI = new GUI;
	load();
}

void Restaurant::RunSimulation()
{
	//pGUI = new GUI;
	PROG_MODE mode = pGUI->getGUIMode();
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive();
		break;
	case MODE_STEP:
		Step_By_Step();
		break;
	case MODE_SLNT:
		Silent();
		break;
	};

}

//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep

void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( Events_Queue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current timestep
			return;

		pE->Execute(this);
		Events_Queue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}

Restaurant::~Restaurant()
{
	Free_Memory();
	if (pGUI)
		delete pGUI;
}

GUI* Restaurant::GetGUI()
{
	return pGUI;
}

void Restaurant::Fill_Drawing_List()
{	
	//Cooks
	PQueue<Cook*> arrangecook;
	Cook* temp;
	int Normal_Count = Normal_Cook_Queue.getcount();

	int Vegan_Count = Vegan_Cook_Queue.getcount();

	int VIP_Count = VIP_Cook_Queue.getcount();

	for (int i = 0; i < Normal_Count; i++) {
		Normal_Cook_Queue.dequeue(temp);
		arrangecook.enqueue(temp, temp->GetFT()*-1);
		Normal_Cook_Queue.enqueue(temp);
	}
	for (int i = 0; i < VIP_Count; i++) {
		VIP_Cook_Queue.dequeue(temp);
		arrangecook.enqueue(temp, temp->GetFT()*-1);
		VIP_Cook_Queue.enqueue(temp);
	}
	for (int i = 0; i < Vegan_Count; i++) {
		Vegan_Cook_Queue.dequeue(temp);
		arrangecook.enqueue(temp, temp->GetFT()*-1);
		Vegan_Cook_Queue.enqueue(temp);
	}
	//drawing Cooks
	while (arrangecook.dequeue(temp))
		pGUI->AddToDrawingList(temp);
	
	
	//waiting 

	Normal_Count = Normal_Waiting.getcount();
	
	Vegan_Count = Vegan_Waiting.getcount();
		
	VIP_Count = VIP_Waiting.getcount();
	
	PQueue<Order*> arrangewaiord;
	Order* temp1;
	
	for (int i = 0; i < Normal_Count; i++) {
		Normal_Waiting.dequeue(temp1);
		arrangewaiord.enqueue(temp1, temp1->GetArrTime() * -1);
		Normal_Waiting.enqueue(temp1);
	}
	for (int i = 0; i < Vegan_Count; i++) {
		Vegan_Waiting.dequeue(temp1);
		arrangewaiord.enqueue(temp1, temp1->GetArrTime() * -1);
		Vegan_Waiting.enqueue(temp1);
	}
	Queue<Order*> vipwai;
	for (int i = 0; i < VIP_Count; i++) {
		VIP_Waiting.dequeue(temp1);
		arrangewaiord.enqueue(temp1, temp1->GetArrTime() * -1);
		vipwai.enqueue(temp1);
	}
	while (vipwai.dequeue(temp1))
		VIP_Waiting.enqueue(temp1, temp1->Calc_Pirority());
	//printing waiting 
	while (arrangewaiord.dequeue(temp1))
		pGUI->AddToDrawingList(temp1);
	
	/*if (Order_VIP_Count != 0) 
	{
		Order** orvip = VIP_Waiting.toArray(Order_Vegan_Count);
		for (int j = 0; j < Order_Vegan_Count; j++)
			pGUI->AddToDrawingList(orvip[j]);
	}
	if (Order_Vegan_Count !=  
	{
		Order** orveg = Vegan_Waiting.toArray(Order_Vegan_Count);
		for (int j = 0; j < Order_Vegan_Count; j++)
			pGUI->AddToDrawingList(orveg[j]);
	}
	if (Order_Normal_Count != 0)
	{
		Order** orn = Normal_Waiting.toArray(Order_Normal_Count);
		for (int j = 0; j < Order_Normal_Count; j++)
			pGUI->AddToDrawingList(orn[j]);
	}
	*/
	//serving
	int busycount = BusyCooks.getcount();
	
	Cook * *busyc = BusyCooks.toArray(busycount);
	
	Order * p;
	for (int j = 0; j < busycount; j++) 
	{
		p = busyc[j]->GetOrder();
		if (p)
			pGUI->AddToDrawingList(p);
	}
	//finished
	
	int finishedcount = Finished_Orders.getcount();
	
	if (finishedcount != 0) 
	{
		Order** finishedord = Finished_Orders.toArray(finishedcount);
		for (int j = 0; j < finishedcount; j++)
			pGUI->AddToDrawingList(finishedord[j]);
	}

}

bool Restaurant::Cancel_Order(int id)
{
	Order* temp; bool x=false;
	for (int i = 0; i < Normal_Waiting.getcount(); i++)
	{
		Normal_Waiting.dequeue(temp);
		if(temp->GetID()!=id)
		  Normal_Waiting.enqueue(temp);

		else
		{
			x = true;
			delete temp;
		}
	}
	return x;
}

bool Restaurant::Promote_Order(int id, int extra)
{
	Order* temp; bool x = false;
	for (int i = 0; i < Normal_Waiting.getcount(); i++)
	{
		Normal_Waiting.dequeue(temp);
		if (temp->GetID() != id)
			Normal_Waiting.enqueue(temp);
		else
		{
			x = true;
			temp->incTotalmoney(extra);
			temp->SetOrderType(TYPE_VIP);
			VIP_Waiting.enqueue(temp, temp->Calc_Pirority());
		}
	}
	return x;
}

void::Restaurant::load() 
{
	ifstream Input;
	
	pGUI->ClearStatusBar(2);
	
	pGUI->PrintMessage("Write input filename : ");
	
	string filename = pGUI->GetString();
	
	Input.open(filename.c_str());
	
	while (Input.fail())
	{
		pGUI->ClearStatusBar(2);

		pGUI->PrintMessage("Wrong filename, Please Enter the correct input filename : ");
		
		string filename = pGUI->GetString();

		Input.open(filename.c_str());
	}

	int Normal_Cooks, Vegan_Cooks, VIP_Cookcs;
	
	int Normal_Cook_Speed, Vegan_Cook_Speed, VIP_Cook_Speed;
	
	int  Normal_Break_Time, Vegan_Break_Time, VIP_Break_Time;
	
	int Number_Events;

	Input >> Normal_Cooks >> Vegan_Cooks >> VIP_Cookcs;
	
	Input >> Normal_Cook_Speed >> Vegan_Cook_Speed >> VIP_Cook_Speed;
	
	Input >>BO >> Normal_Break_Time >> Vegan_Break_Time >> VIP_Break_Time;
	
	Input >> AutoPT;
	
	Input >> Number_Events;//getting the information of the cook from file

	int sum = Normal_Cooks + Vegan_Cooks + VIP_Cookcs;
	
	T_AutoP = 0; // We Added this to count the total number of auto promoted orders (can be changed)

	for (int i = 0; i < Normal_Cooks; i++) 
	{
		Cook *pc=new Cook((i + 1) * 2 + sum, Normal_Cook_Speed, (ORD_TYPE)(TYPE_NRM), Normal_Break_Time);
		
		Normal_Cook_Queue.enqueue(pc);//setting the id and type for the normal cooks
	}
	for (int i = Normal_Cooks; i < Vegan_Cooks+ Normal_Cooks; i++)
	{
		Cook *pc=new Cook((i + 1) * 3 + sum, Vegan_Cook_Speed, (ORD_TYPE)(TYPE_VGAN), Vegan_Break_Time);
	
		Vegan_Cook_Queue.enqueue(pc);//setting the id and type for the vegan cooks
	}

	for (int i = Vegan_Cooks + Normal_Cooks; i < sum; i++) 
	{
		Cook* pc = new Cook((i + 1) * 5 + sum, VIP_Cook_Speed, (ORD_TYPE)(TYPE_VIP), VIP_Break_Time);
		
		VIP_Cook_Queue.enqueue(pc);//setting the id and type for the VIP cooks
	}
	
	Event* pEv;
	
	for (int i = 0; i < Number_Events; i++)
	{
		char event, type;
		ORD_TYPE typ = TYPE_CNT;
		Input >> event;
		if (event == 'R')
		{
			int timestep, ID, size, money, speed = 0;
			Input >> type;
			switch (type) {
			case 'N':typ = TYPE_NRM;
				speed = Normal_Cook_Speed;
				break;
			case 'G':typ = TYPE_VGAN;
				speed = Vegan_Cook_Speed;
				break;
			case'V':typ = TYPE_VIP;
				speed = VIP_Cook_Speed;//to detemine the type
			}
			Input >> timestep >> ID >> size >> money;
			pEv = new ArrivalEvent(timestep, ID, size, money, (ORD_TYPE)typ, 0);
			Events_Queue.enqueue(pEv);//adding the arrival evevnt in a queue
		}
		else if (event == 'X')
		{
			int timestep, ID;
			Input >> timestep >> ID;
			pEv = new CancellationEvent(timestep, ID);
			Events_Queue.enqueue(pEv);//adding the cancellation evevnt in a queue
		}
		else if (event == 'P') {
			int timestep, ID, Exmoney;
			Input >> timestep >> ID >> Exmoney;
			pEv = new promotion(timestep, ID, Exmoney);
			Events_Queue.enqueue(pEv);//adding the cancellation evevnt in a queue
		}
	}
}

void::Restaurant::Interactive()
{
	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while (!Is_Program_Finished())
	{
		Run(CurrentTimeStep);
		pGUI->waitForClick();
		pGUI->ClearStatusBar(2);
	}
	OutPut();
}

void Restaurant::Step_By_Step() 
{
	int CurrentTimeStep = 1;
	while (!Is_Program_Finished()) 
	{
		Run(CurrentTimeStep);
		Sleep(1000);
		pGUI->ClearStatusBar(2);
	}
	OutPut();
}

void Restaurant::Silent() 
{
	int CurrentTimeStep = 1;
	while (!Is_Program_Finished())
	{
		Run(CurrentTimeStep);
	}
	OutPut();
}

void Restaurant::OutPut()
{
	int  N_Order = 0, VIP_Order = 0, V_Order = 0, N_Cook = 0, V_Cook = 0, VIP_Cook = 0;
	double WaitTime = 0.0,Total_Serv = 0.00;
	Order* Order;
	string type;
	pGUI->ClearStatusBar(2);
	pGUI->PrintMessage("Write output filename : ");
	string filename = pGUI->GetString();
	fstream Output(filename.c_str(), ios::out);
	Output << "FT" << "    " << "ID" << "    " << "AT" << "    " << "WT" << "    " << "ST" << endl;
	while (Finished_Orders.dequeue(Order))
	{
		Output << Order->Get_Finished_Time() << "    " << Order->GetID() << "     " << Order->GetArrTime() << "     " << Order->Get_Total_Wait_Time() << "     "
			<< Order->GetServTime() << endl;
		ORD_TYPE typ = Order->GetType();
		switch (typ)
		{
		case TYPE_NRM:
			N_Order++;
			break;
		case TYPE_VGAN:
			V_Order++;
			break;
		case TYPE_VIP:
			VIP_Order++;
			break;
		}
		Total_Serv += Order->GetServTime();
		WaitTime += Order->Get_Total_Wait_Time();
	}
	Normal_Cook_Queue.toArray(N_Cook);
	Vegan_Cook_Queue.toArray(V_Cook);
	VIP_Cook_Queue.toArray(VIP_Cook);
	Output << "Orders: " << VIP_Order + N_Order + V_Order << "  [Norm: " << N_Order << ", Veg: " << V_Order << ", VIP: " << VIP_Order << " ]" << endl;
	Output << "Cooks:" << VIP_Cook + V_Cook + N_Cook << "  [Norm: " << N_Cook << ", Veg: " << V_Cook << ", VIP: " << VIP_Cook << " ]" << endl;
	Output << "Avg Wait= " << WaitTime / (N_Order + V_Order + VIP_Order) << ", Avg Serv= " << Total_Serv / (N_Order + V_Order + VIP_Order) << endl;
	Output << "Auto-Promoted: " << T_AutoP;
	Output.close();
}
void Restaurant::Print(int time)
{
	string cooks = "    Normal cook avail: " + to_string(Normal_Cook_Queue.getcount()) + "    Vegan cook avail: " + to_string(Vegan_Cook_Queue.getcount()) + "    VIP cook avail: " + to_string(VIP_Cook_Queue.getcount());
	
	string orders ="    Normal waiting: " + to_string(Normal_Waiting.getcount()) + "    " + "Vegan waiting: " + to_string(Vegan_Waiting.getcount()) + "    " + "VIP waiting: " + to_string(VIP_Waiting.getcount());
	
	string served = "    served: " + to_string(Finished_Orders.getcount());

	pGUI->PrintMessage("Ts:" + to_string(time) +orders +cooks+served);
}
void Restaurant::Run(int &time) 
{
	Print(time);

	ExecuteEvents(time);	//Execute all events at current time step
	
	IsFinished(time);  //Checking if there is any order is done in this time step
	
	T_AutoP += Auto_Promotion(time);
	
	//ServOrders(time); //Assigning orders to cooks
	
	Fill_Drawing_List();

	pGUI->UpdateInterface();
	
	time++;
	
	pGUI->ResetDrawingList();
}

void Restaurant::AddtoNormal(Order* po)
{
	Normal_Waiting.enqueue(po);
}

void Restaurant::AddtoVGN(Order* po)
{
	Vegan_Waiting.enqueue(po);
}

void Restaurant::AddVIP(Order* po)
{
	VIP_Waiting.enqueue(po, po->Calc_Pirority());
}

int Restaurant::Auto_Promotion(int timestep)
{
	bool y = true; Order* po;
	int x = 0;
	while (Normal_Waiting.peekFront(po) && y)
	{
		if (po->Get_Current_Wait_Time(timestep) == AutoPT)
		{
			Normal_Waiting.dequeue(po);
			po->SetOrderType(TYPE_VIP);
			VIP_Waiting.enqueue(po,po->Calc_Pirority());
			y = true;
			x++;
		}
		else
		{
			y = false;
		}
	}
	return x;
}

void Restaurant::IsFinished(int timestep) 
{
	Cook* temp;
	PQueue<Order*>dummy;
	bool x = true;
	while (BusyCooks.peekFront(temp) && x)
	{
		if (temp->GetFT() == timestep)
		{
			BusyCooks.dequeue(temp);
			if (temp->GetAvail() == Break)
			{
				temp->SetStatue(Avail);
				AddCook(temp);

			}
			else
			{
				Order* p;
				p = temp->GetOrder();
				p->SetStatus(DONE);
				temp->Increase_Completed_Orders();
				temp->SetOrder(nullptr);
				Finished_Orders.enqueue(p);
				if (!temp->IsBreak(timestep, BO))
				{
					AddCook(temp);
				}
				else
					BusyCooks.enqueue(temp, temp->GetFT() * -1);
			}
		}
		else
		{
			x = false;
		}
	}
}
	
void Restaurant::Assign_Cook(Order* tempo, Cook* tempc,int timestep,int count)
{
	float cspeed, dishes, servtime, finished;
			
	cspeed = tempc->GetSpeed();
			
	dishes = tempo->GetSize();
	
	servtime = ceil(dishes / cspeed); //Calculating serving time
	
	finished = servtime + timestep;  //Calculating finishing time for this order
	
	tempc->SetFT(finished);
	
	tempo->SetServTime(servtime);
	
	tempo->Set_Finished_Time(finished);
	
	tempo->SetStatus(SRV);
	
	tempc->SetOrder(tempo);
	
	tempc->SetStatue(Not_Avail);
	
	pGUI->PrintMessage2(Type_To_String(tempc) +to_string(tempc->GetID()) + "("+Type_To_String(tempo)+to_string(tempo->GetID())+")",count);
	
	BusyCooks.enqueue(tempc,finished*-1);
}

void Restaurant::Free_Memory()
{
	// Deleting all alocated orders
	Order* tempo;
	while (Finished_Orders.dequeue(tempo))
		delete tempo;
	
	// Deleteing all the cooks
	Cook * tempc;
	while (Normal_Cook_Queue.dequeue(tempc))
		delete tempc;
	while (Vegan_Cook_Queue.dequeue(tempc))
		delete tempc;
	while (VIP_Cook_Queue.dequeue(tempc))
		delete tempc;

}

string Restaurant::Type_To_String(Order* tempo)
{
	switch (tempo->GetType())
	{
	case TYPE_NRM:
		return "N";
	case TYPE_VGAN:
		return "Veg";
	case TYPE_VIP:
		return "V";
	}
}

string Restaurant::Type_To_String(Cook* tempc)
{
	switch (tempc->GetType()) 
	{
	case TYPE_NRM:
		return "N";
	case TYPE_VGAN:
		return "Veg";
	case TYPE_VIP:
		return "V";
	}
}

bool Restaurant::Is_Program_Finished()
{
	return Events_Queue.isEmpty()&&Normal_Waiting.isEmpty()&&VIP_Waiting.isEmpty()&&Vegan_Waiting.isEmpty()&&BusyCooks.isEmpty();
}

void Restaurant::AddCook(Cook* C) 
{
	ORD_TYPE type;
	type = C->GetType();
	C->SetStatue(Avail);
	switch (type) {
	case TYPE_NRM:Normal_Cook_Queue.enqueue(C);
		break;
	case TYPE_VGAN:Vegan_Cook_Queue.enqueue(C);
		break;
	case TYPE_VIP:VIP_Cook_Queue.enqueue(C);
		break;
	}
}

void Restaurant::ServOrders(int timestep)
{
	Order* tempo;
	Cook* tempc;
	int count = -1;
	bool flag = true;
	while (VIP_Waiting.peekFront(tempo)&&flag)
	{
		count++;
		if (VIP_Cook_Queue.dequeue(tempc))
		{
			VIP_Waiting.dequeue(tempo);
			Assign_Cook(tempo, tempc, timestep,count);
		}
		else if (Normal_Cook_Queue.dequeue(tempc))
		{
			VIP_Waiting.dequeue(tempo);
			Assign_Cook(tempo, tempc, timestep,count);
		}
		else if (Vegan_Cook_Queue.dequeue(tempc))
		{
			VIP_Waiting.dequeue(tempo);
			Assign_Cook(tempo, tempc, timestep,count);
		}
		else 
		{
			flag = false; count--;
		}
	}
	flag = true;
	while (Vegan_Waiting.peekFront(tempo) && flag)
	{
		if (Vegan_Cook_Queue.dequeue(tempc))
		{
			Vegan_Waiting.dequeue(tempo);
			count++;
			Assign_Cook(tempo, tempc, timestep, count);
		}
		else 
		{
			flag = false;
		}
	}
	flag = true;
	while (Normal_Waiting.peekFront(tempo) && flag)
	{
		if (Normal_Cook_Queue.dequeue(tempc))
		{
			Normal_Waiting.dequeue(tempo);
			count++;
			Assign_Cook(tempo, tempc, timestep,count);
		}
		else if (VIP_Cook_Queue.dequeue(tempc))
		{
			Normal_Waiting.dequeue(tempo); count++;
			Assign_Cook(tempo, tempc, timestep,count);
		}
		else
		{
			flag = false;
		}
	}

}
