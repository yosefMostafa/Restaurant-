
#ifndef __NODE_H_
#define __NODE_H_

template < typename T>
class Node
{
protected :
	T item; // A data item
	Node<T>* next; // Pointer to next node
	int pirority;

public :
	Node();
	Node( const T & r_Item);	//passing by const ref.
	Node( const T & r_Item, Node<T>* nextNodePtr);
	Node(const T& r_Item, int x);

	void setItem( const T & r_Item);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const ;
	Node<T>* getNext() const ;

	int getpirority();

}; // end Node


template < typename T>
Node<T>::Node() 
{
	pirority = 0;
	next = nullptr;
} 

template < typename T>
Node<T>::Node( const T& r_Item)
{
	item = r_Item;
	next = nullptr;
	pirority = 0;
} 

template < typename T>
Node<T>::Node( const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
	pirority=0
}
template<typename T>
inline Node<T>::Node(const T& r_Item, int x)
{
	item = r_Item;
	pirority = x;
}
template < typename T>
void Node<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
T Node<T>::getItem() const
{
	return item;
} 

template < typename T>
Node<T>* Node<T>::getNext() const
{
		return next;
}
template<typename T>
inline int Node<T>::getpirority()
{
	return pirority;
}


#endif