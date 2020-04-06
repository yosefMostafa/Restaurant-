#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int count;	//Number of nodes in the list
public:


	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll(); 
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout<<"\nList has "<<count<<" nodes";
		cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "*\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;  //Whyyyyyyyyyyyyyyyyyyyyyyyy
		}
		count = 0;
	}

	

	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T &data)
	{
		Node<T>* P = Head;
		if (Head)
		{
          	while (P->getNext())
			{
				P= P->getNext();
			}
			Node<T>* R = new Node<T>(data);
		    P->setNext(R);
			count++;
		}
		else 
		{
			InsertBeg(data);
		}
	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key)
	{
		Node<T>* P = Head;
		if (Head)
		{
			while (P)
			{
				if (P->getItem() == Key) {
					cout << "The value was found ";
					return true;
				}
				else
					P = P->getNext();
			}
		}
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value)
	{
		int count = 0;
		Node<T>* P = Head;
		if (Head)
		{
			while (P)
			{
				if (P->getItem() == value)
					count++;
	
					P = P->getNext();
			}
		}
		cout << "The value was found ";
		return count;
	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst() {
		Node<T>* P = Head;

		if (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
			count--;
		}
	}
	

	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast() {
		Node<T>* P = Head;
		Node<T>* R = P->getNext();
		if (Head)
		{
			while (R->getNext())
			{
				 P = R;
				R = P->getNext();
			} 
			delete R;
			P->setNext(nullptr);
			count--;
		}
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value)
	{
		Node<T>* P = Head;
		Node<T>* R = P->getNext();
		if (Head)
		{
			while (R)
			{
				if (R->getItem() == value)
				{
					Head = P;
					delete R;
					P->setNext(nullptr);
					count--;
					return true;
				}
	

			}
			return false;
		}
		else
			return false;

	}


};

#endif	
