#pragma once
#include"Generic_DS/Queue.h"
#include"./Rest/Order.h"
#include"./Rest/Cook.h"
#include"./Generic_DS/Node.h"

template<class T>
class pirorityQueue : public Queue<T>
{
	

public:
	pirorityQueue() : Queue<T>() {};
	
	virtual bool enqueue(const Order*& newEntry)
	{
		Node<T> * newNodePtr = new Node<T>(newEntry);
		// Insert the new node
		 
		
		    if (Queue<T>::isEmpty())  // The queue is empty
			{
				frontPtr = newNodePtr;
				backPtr = newNodePtr;

			}
			else   // the pirority queue is not empty 
			{
				Order* lowestP = backPtr->getItem();
				Order* highestP = frontPtr->getItem();


				if (newEntry->calcPirority() <= lowestP->calcPirority()) // check whether the lowest pirority in our queue has a pirority higher than the upcoming order
				{
					backPtr->setNext(newNodePtr);
					backPtr = newNodePtr;    /// it is the same as normal enqueuing this may not be so useful however it reduces the complexity of the code
				}
				else if (highestP->calcPirority() < newEntry->calcPirority())
				{
					newNodePtr->setNext(frontPtr);
					frontPtr = newNodePtr;
				}
				else
				{
					Node<Order*>* temp = frontPtr;
					while (temp->getNext()->getItem()->calcPirority() > newEntry->calcPirority())
					{
						temp = temp->getNext();
					}
					newNodePtr->setNext(temp->getNext());
					temp->setNext(newNodePtr);

				}

			} // The queue was not empty
		count++;
		return true;

	}








};
