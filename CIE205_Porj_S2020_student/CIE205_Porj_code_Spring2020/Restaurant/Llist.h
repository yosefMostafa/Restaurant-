#pragma once
#include"./Generic_DS/Node.h"


template<typename T>
class Llist
{
	Node<T>* Head;
	Node<T>* Tail;
public: 
	Llist();
	bool isEmpty() const;
	bool begInset(const T& newEntry);
	bool delLast(T& newEntry);
	bool deleteNode(Node<T>* ptr);
	bool delHead(T& rtnNode);
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
inline bool Llist<T>::delLast(T& rtnNode) 
{
	if (isempty())
		return false;
	
	rtnNode = Tail->getItem();


	if (Head == Tail)   //case where there is only one node 
	{
		delete Head; 
	}
	else  
	{
		Node<T>* newNodePtr = new Node<T>(Head);


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
inline bool Llist<T>::deleteNode(Node<T>* ptr)
{
	if (ptr == Tail->getItem())
	{
		delLast();
	}
	else
	{
		Node<T>* temp = ptr->getNext();
		ptr->getItem() = temp->getItem();          
		ptr->setNext() = temp->setNext();     
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
		Node<T>* newNodePtr = new Node<T>(Head);

		Head = newNodePtr->getNext();
		delete newNodePtr;
	}
	return true;
}

template<typename T>
inline Llist<T>::~Llist()
{
}


