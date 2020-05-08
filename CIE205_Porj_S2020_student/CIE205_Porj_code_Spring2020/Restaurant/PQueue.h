#pragma once
#include"./PNode.h"
#include"./Generic_DS/Queue.h"

template<class T> 
class PQueue : public Queue<T>
{
	using Queue<T>::enqueue;
public:
	PQueue();

	bool enqueue(const T& newEntry, int x)
	{
		Node<T>* newNodePtr = new Node<T>(newEntry, x);
		// Insert the new node
		if (this->isEmpty())  // The queue is empty
		{
			this->frontPtr = newNodePtr;
			this->backPtr = newNodePtr;
		}
		else   // the pirority queue is not empty
		{
			int lowestP = backPtr->getpirority();
			int highestP = frontPtr->getpirority();
			if (x <= lowestP) // check whether the lowest pirority in our queue has a pirority higher than the upcoming order
			{
				backPtr->setNext(newNodePtr);
				backPtr = newNodePtr;    /// it is the same as normal enqueuing this may not be so useful however it reduces the complexity of the code
			}
			else if (highestP < x)
			{
				newNodePtr->setNext(frontPtr);
				frontPtr = newNodePtr;
			}
			else
			{
				Node<T>* temp = frontPtr;
				while (temp->getNext()->getpirority() > x)
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

template<class T>
inline PQueue<T>::PQueue():Queue()
{
}
/*
Node<Order*>* newNodePtr = new Node<Order*>(newEntry);
	// Insert the new node
	if (isEmpty())  // The queue is empty
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

*/
