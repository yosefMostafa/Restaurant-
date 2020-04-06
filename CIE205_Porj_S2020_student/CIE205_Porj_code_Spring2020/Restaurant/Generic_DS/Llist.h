#pragma once
#include"./Node.h"


template<typename T>
class Llist
{
	Node<T>* Head;
	Node<T>* Tail;
public:
	Llist();
	bool isEmpty() const;
	bool begInset(const T& newEntry);
	bool InsertfromTail(const T& newEntry);
	bool delLast(T& newEntry);
	bool deleteNode(Node<T>* ptr, T& delNode);
	bool delHead(T& rtnNode);
	Node<T>* getlisthead();


	~Llist();

};

template<typename T>
inline Llist<T>::Llist()
{
	Head = nullptr;
	Tail = nullptr;

}

template<typename T>
inline bool Llist<T>::isEmpty() const
{
	if (Head == nullptr)
		return true;
	else
		return false;
}

template<typename T>
inline bool Llist<T>::begInset(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);

	if (isEmpty())
	{
		Head = newNodePtr;
		Tail = newNodePtr;
	}
	else
	{
		newNodePtr->setNext(Head);
		Head = newNodePtr;

	}

	return true;

}

template<typename T>
inline bool Llist<T>::InsertfromTail(const T& newEntry)
{

	Node<T>* newNodePtr = new Node<T>(newEntry);
	if (isEmpty())
	{
		Head = newNodePtr;
		Tail = newNodePtr;
	}
	else
	{
		Tail->setNext(newNodePtr);
		Tail = newNodePtr;
	}
	return true;

}


template<typename T>
inline bool Llist<T>::delLast(T& rtnNode)
{
	if (isEmpty())
		return false;

	rtnNode = Tail->getItem();


	if (Head == Tail)   //case where there is only one node
	{
		delete Head;
	}
	else
	{
		Node<T>* newNodePtr = Head;


		while (newNodePtr->getNext() != Tail)
		{
			newNodePtr = newNodePtr->getNext();
		}

		delete Tail;
		Tail = newNodePtr;
	}

	return true;

}

template<typename T>
inline bool Llist<T>::deleteNode(Node<T>* ptr, T& delNode)
{
	if (ptr == Tail)
	{
		delLast(delNode);
		return true;
	}

	Node<T>* temp = ptr->getNext();

	if (ptr->getNext() == Tail)
	{

		delNode = ptr->getItem();
		ptr->setItem(temp->getItem());
		ptr->setNext(temp->getNext());

		delete Tail;
		Tail = ptr;
	}

	else
	{
		delNode = ptr->getItem();
		ptr->setItem(temp->getItem());
		ptr->setNext(temp->getNext());
		delete temp;
	}


	return true;
}

template<typename T>
inline bool Llist<T>::delHead(T& rtnNode)
{
	if (isEmpty())
		return false;


	rtnNode = Head->getItem();
	if (Head == Tail)         // case I have only one node
		delete Head;
	else {                    // case I have more than one node
		Node<T>* newNodePtr = Head;

		Head = newNodePtr->getNext();
		delete newNodePtr;
	}
	return true;
}



template<typename T>
inline Node<T>* Llist<T>::getlisthead()
{
	return Head;
}

template<typename T>
inline Llist<T>::~Llist()
{
}
