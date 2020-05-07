#pragma once
#include "./Generic_DS/Node.h"

template <typename T>
class pirQueue
{
protected:
	int count;
	int pir;
	Node<T>* backPtr;
	Node<T>* frontPtr;

public:
	pirQueue();
	int getcount();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, int x);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	T* toArray(int& count);	//returns array of T (array if items)
	~pirQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
pirQueue<T>::pirQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;
	pir=0
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool pirQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}

template <typename T>
int pirQueue<T>::getcount() {
	return count;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool pirQueue<T>::enqueue(const T& newEntry, int x)
{
	pir = x;
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	count++;
	backPtr = newNodePtr; // New node is at back
	return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool pirQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;
	count--;

	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template <typename T>
bool pirQueue<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
pirQueue<T>::~pirQueue()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: toArray
returns an array of "T"
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/

template <typename T>
T* pirQueue<T>::toArray(int& count)
{
	count = 0;

	if (!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = frontPtr;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}


