#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include"..\CancellationEvent.h"
#include"..\Events\promotion.h"
#include<string>


Restaurant::Restaurant()
{
	pGUI = NULL;

	load();
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getGUIMode();


	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		interactive();
		break;
	case MODE_STEP:
		stepbystep();
		break;
	case MODE_SLNT:
		silent();
		break;
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

GUI* Restaurant::GetGUI()
{
	return pGUI;
}

void Restaurant::FillDrawingList()
{
	int ncount, vegancount,vipcount,orvipcount, orncount, orvegcount; ncount = NormalCQueue.getcount(); vegancount = VeganCQueue.getcount();
	orncount = NOwaiting.getcount(); orvegcount = VGNWaiting.getcount();//getting the count of the queues to draw
	vipcount = VIPCQueue.getcount();
	orvipcount = VIPwaiting.getcount();
	Cook** pcn = NormalCQueue.toArray(ncount);
	Cook** pcv = VeganCQueue.toArray(vegancount);
	Cook** pcvip = VIPCQueue.toArray(vipcount);
	//waiting
	if (orvipcount != 0) {
		Order** orvip = VIPwaiting.toArray(orvegcount);
		for (int j = 0; j < orvegcount; j++)
			pGUI->AddToDrawingList(orvip[j]);
	}
	if (orvegcount != 0) {
		Order** orveg = VGNWaiting.toArray(orvegcount);
		for (int j = 0; j < orvegcount; j++)
			pGUI->AddToDrawingList(orveg[j]);
	}
	if (orncount != 0) {
		Order** orn = NOwaiting.toArray(orncount);
		for (int j = 0; j < orncount; j++)
			pGUI->AddToDrawingList(orn[j]);
	}
	//Cooks
	for (int j = 0; j < ncount; j++)
		pGUI->AddToDrawingList(pcn[j]);
	for (int j = 0; j < vegancount; j++)
		pGUI->AddToDrawingList(pcv[j]);
	for (int j = 0; j < vipcount; j++)
		pGUI->AddToDrawingList(pcvip[j]);
	//serving
	int busycount = BusyCooks.getcount();
	Cook * *busyc = BusyCooks.toArray(busycount);
	Order * p;
	for (int j = 0; j < busycount; j++) {
		p = busyc[j]->getorder();
		if (p)
			pGUI->AddToDrawingList(p);
	}
	//finished
	int finishedcount = finishedqueue.getcount();
	if (finishedcount != 0) {
		Order** finishedord = finishedqueue.toArray(orncount);
		for (int j = 0; j < finishedcount; j++)
			pGUI->AddToDrawingList(finishedord[j]);
	}

}
bool Restaurant::cancelOrder(int id)
{
	Order* temp; bool x=false;
	for (int i = 0; i < NOwaiting.getcount(); i++)
	{
		NOwaiting.dequeue(temp);
		if(temp->GetID()!=id)
		  NOwaiting.enqueue(temp);

		else
		{
			x = true;
			delete temp;
		}
	}
	return x;
}
bool Restaurant::promoteOrder(int id, int extra)
{
	Order* temp; bool x = false;
	for (int i = 0; i < NOwaiting.getcount(); i++)
	{
		NOwaiting.dequeue(temp);
		if (temp->GetID() != id)
			NOwaiting.enqueue(temp);

		else
		{
			x = true;
			temp->incTotalmoney(extra);
			temp->setordertype(TYPE_VIP);
			VIPwaiting.pushToPQ(temp);
		}
	}
	return x;
}
void::Restaurant::load() {
	ifstream file("data.txt");
	int Normalcooks, vegancooks, vipcooks;
	int Normalcooksspeed, vegancooksspeed, vipcooksspeed;
	int  normalbreaktime, veganbreaktime, vipbreaktime;
	int numofevents;

	file >> Normalcooks >> vegancooks >> vipcooks;
	file >> Normalcooksspeed >> vegancooksspeed >> vipcooksspeed;
	file >>BO >> normalbreaktime >> veganbreaktime >> vipbreaktime;
	file >> AutoPT;
	file >> numofevents;//getting the information of the cook from file

	int sum = Normalcooks + vegancooks + vipcooks;
	TOTALautoP = 0; // We Added this to count the total number of auto promoted orders (can be changed)

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
			int timestep, ID, size,money,speed=0;

			file >> type;

			switch (type) {
			case 'N':typ = TYPE_NRM;
				speed = Normalcooksspeed;
				break;
			case 'G':typ = TYPE_VGAN;
				speed = vegancooksspeed;
				break;
			case'V':typ= TYPE_VIP;
				speed = vipcooksspeed;//to detemine the type
			}

			file >> timestep >> ID >> size >> money;

			pEv = new ArrivalEvent(timestep, ID, size,money,(ORD_TYPE)typ,0);
			//	ArrivalEvent(int eTime, int oID, int s, double o, ORD_TYPE oType, int distance);

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
void::Restaurant::interactive(){
	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while (!isprogramfnished())
	{
		Run(CurrentTimeStep);
		pGUI->waitForClick();
		pGUI->ClearStatusBar(2);
	}
	OutPut();
}
void Restaurant::stepbystep() {
	int CurrentTimeStep = 1;
	while (!isprogramfnished()) {
		Run(CurrentTimeStep);
		Sleep(1000);
		pGUI->ClearStatusBar(2);
	}
	OutPut();
}

void Restaurant::silent() {
	int CurrentTimeStep = 1;

	while (!isprogramfnished())//should be updated
		Run(CurrentTimeStep);
	OutPut();

	//the func for calling the output file should be called here
}
void Restaurant::OutPut()
{
	fstream Output;
	int  Normal = 0, Vip = 0, Vegan = 0, N_Cook = 0, V_Cook = 0, VI_Cook = 0;
	double WaitTime = 0.0;
	double  totalserv = 0.00;
	//int AP = 0;
	Output.open("Output.txt", ios::out);
	Order* Order;
	string type;
	Output << "FT" << "    " << "ID" << "    " << "AT" << "    " << "WT" << "    " << "ST" << endl;
	while (finishedqueue.dequeue(Order))
	{
		Output << Order->getfinishedtime() << "    " << Order->GetID() << "     " << Order->getArrTime() << "     " << Order->gettotalwaittime() << "     "
			<< Order->getServTime() << endl;
		ORD_TYPE typ = Order->GetType();
		switch (typ)
		{
		case TYPE_NRM:
			Normal++;
			break;
		case TYPE_VGAN:
			Vegan++;
			break;
		case TYPE_VIP:
			Vip++;
			break;
		}
		totalserv += Order->getServTime();
		WaitTime += Order->gettotalwaittime();
	}
	NormalCQueue.toArray(N_Cook);
	VeganCQueue.toArray(V_Cook);
	VIPCQueue.toArray(VI_Cook);
	Output << "Orders: " << Vip + Normal + Vegan << "  [Norm: " << Normal << ", Veg: " << Vegan << ", VIP: " << Vip << " ]" << endl;
	Output << "Cooks:" << VI_Cook + V_Cook + N_Cook << "  [Norm: " << N_Cook << ", Veg: " << V_Cook << ", VIP: " << VI_Cook << " ]" << endl;
	Output << "Avg Wait= " << WaitTime / (Normal + Vegan + Vip) << ", Avg Serv= " << totalserv / (Normal + Vegan + Vip) << endl;
	Output << "Auto-Promoted: " << TOTALautoP;
	Output.close();

}
void Restaurant::print(int time)
{
	string cooks = "    Normal cook avail: " + to_string(NormalCQueue.getcount()) + "    Vegan cook avail: " + to_string(VeganCQueue.getcount()) + "    VIP cook avail: " + to_string(VIPCQueue.getcount());
	string orders ="    Normal waiting: " + to_string(NOwaiting.getcount()) + "    " + "Vegan waiting: " + to_string(VGNWaiting.getcount()) + "    " + "VIP waiting: " + to_string(VIPwaiting.getcount());
	string served = "    served: " + to_string(finishedqueue.getcount());

	pGUI->PrintMessage("Ts:" + to_string(time) +orders +cooks+served);
}
void Restaurant::Run(int &time) {
	//char timestep[10];
	//itoa(time, timestep, 10);
	print(time);

	ExecuteEvents(time);	//execute all events at current time step
	finished(time);//checking if there is any order is done in this time step
	TOTALautoP += Autop(time);
	serveorders(time);//assigning orders to cooks
	FillDrawingList();

	/// The next code section should be done through function "FillDrawingList()" once you
	/// decide the appropriate list type for Orders and Cooks
	pGUI->UpdateInterface();
	time++;	//advance timestep
	pGUI->ResetDrawingList();
}
void Restaurant::AddtoNormal(Order* po)
{
	NOwaiting.enqueue(po);
}

void Restaurant::AddtoVGN(Order* po)
{
	VGNWaiting.enqueue(po);
}
void Restaurant::AddVIP(Order* po)
{
	VIPwaiting.pushToPQ(po);

}
int Restaurant::Autop(int timestep)
{
	bool y = true; Order* po;
	int x = 0;
	while (NOwaiting.peekFront(po) && y)
	{
		if (po->getcurrentwaittime(timestep) == AutoPT)
		{
			NOwaiting.dequeue(po);
			po->setordertype(TYPE_VIP);
			VIPwaiting.pushToPQ(po);
			y = true;
			x++;
		}
		else
			y = false;

	}
	return x;
}

void Restaurant::finished(int timestep) {
	Cook* temp;
	Queue<Cook*> tempqc;
	Queue<Order*>dummy;
	while (BusyCooks.dequeue(temp)) {
		if (temp->getavail() != Break) {
			if (timestep == temp->getorder()->getfinishedtime())
			{
				Order* p;
				p = temp->getorder();
				p->setStatus(DONE);
				temp->increasecomporders();
				temp->setorder(nullptr);
				dummy.enqueue(p);
				if (!temp->isbreak(timestep, BO)) {
					AddCook(temp);
				}
				else
					tempqc.enqueue(temp);
			}
			else
				tempqc.enqueue(temp);
		}
		else {
			if (temp->Breakd(timestep)) {
				AddCook(temp);
			}else
				tempqc.enqueue(temp);
		}
	}
	while (tempqc.dequeue(temp))
		BusyCooks.enqueue(temp);


	int dcount; bool flag = true;  Order* temporder;
	Order** Arr = dummy.toArray(dcount);
	while (flag)
	{
		flag = false;
		for (int i = 0; i < dcount-1; i++)
		{
			if (Arr[i]->getServTime() > Arr[i + 1]->getServTime())  // arrange where less serving time exists first
			{
				flag = true; // the while loop will have another iteration
				temporder = Arr[i+1];    // here I have to make a swap between the two orderes
				Arr[i + 1] = Arr[i];
				Arr[i] = temporder;

			}
		}
	}

	for (int i = 0; i < dcount; i++)
		finishedqueue.enqueue(Arr[i]);
	delete Arr;

}
void Restaurant::assigncook(Order* tempo, Cook* tempc,int timestep,int count)
{
	float cspeed, dishes, servtime, finished;
			cspeed = tempc->getspeed();
			dishes = tempo->getsize();
			servtime = ceil(dishes / cspeed);//calculating serving time
			finished = servtime + timestep;//calculating finishing time for this order
			tempo->SetServTime(servtime);
			tempo->setfinishedtime(finished);
			tempo->setStatus(SRV);
			tempc->setorder(tempo);
			tempc->setStatue(Not_Avail);
			pGUI->PrintMessage2(typetostring(tempc) +to_string(tempc->GetID()) + "("+typetostring(tempo)+to_string(tempo->GetID())+")",count);
			BusyCooks.enqueue(tempc);
}
string Restaurant::typetostring(Order* tempo)
{
	switch (tempo->GetType()) {
	case TYPE_NRM:
		return "N";
	case TYPE_VGAN:
		return "Veg";
	case TYPE_VIP:
		return "V";
	}
}
string Restaurant::typetostring(Cook* tempc)
{
	switch (tempc->GetType()) {
	case TYPE_NRM:
		return "N";
	case TYPE_VGAN:
		return "Veg";
	case TYPE_VIP:
		return "V";
	}
}
bool Restaurant::isprogramfnished()
{
	return EventsQueue.isEmpty()&&NOwaiting.isEmpty()&&VIPwaiting.isEmpty()&&VGNWaiting.isEmpty()&&BusyCooks.isEmpty();
}
void Restaurant::AddCook(Cook* C) {
	ORD_TYPE type;
	type = C->GetType();
	C->setStatue(Avail);
	switch (type) {
	case TYPE_NRM:NormalCQueue.enqueue(C);
		break;
	case TYPE_VGAN:VeganCQueue.enqueue(C);
		break;
	case TYPE_VIP:VIPCQueue.enqueue(C);
		break;
	}
}
void Restaurant::serveorders(int timestep)
{
	Order* tempo;
	Cook* tempc;
	int count = -1;
	bool flag = true;
	while (VIPwaiting.peekFront(tempo)&&flag)
	{
		count++;
		if (VIPCQueue.dequeue(tempc)) {
			VIPwaiting.dequeue(tempo);
			assigncook(tempo, tempc, timestep,count);
		}
		else if (NormalCQueue.dequeue(tempc))
		{
			VIPwaiting.dequeue(tempo);
			assigncook(tempo, tempc, timestep,count);
		}
		else if (VeganCQueue.dequeue(tempc))
		{
			VIPwaiting.dequeue(tempo);
			assigncook(tempo, tempc, timestep,count);
		}
		else {
			flag = false; count--;
		}
	}
	flag = true;
	while (VGNWaiting.peekFront(tempo)&&flag)
	{
		if (VeganCQueue.dequeue(tempc))
		{
		VGNWaiting.dequeue(tempo);
		count++;
		assigncook(tempo, tempc, timestep,count);
		}
		else
		flag = false;
	}
	flag = true;
	while (NOwaiting.peekFront(tempo) && flag)
	{
		if (NormalCQueue.dequeue(tempc)) {
			NOwaiting.dequeue(tempo);
			count++;
			assigncook(tempo, tempc, timestep,count);
		}
		else if (VIPCQueue.dequeue(tempc))
		{
			NOwaiting.dequeue(tempo); count++;
			assigncook(tempo, tempc, timestep,count);
		}
		else
			flag = false;
	}

}
