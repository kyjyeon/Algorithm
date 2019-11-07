#include "ItemType.h"
#include <iostream>
using namespace std;

#define maxQueue 10


/**
*	@brief	Exception class thrown by Enqueue when queue is full.
*/
class FullQueue
{
public:
	/**
	*	@brief	Display a message for full queue on screen.
	*/
	void print()
	{
		cout << "FullQueue exception thrown." << endl;
	}
};


/**
*	@brief	Exception class thrown by Dequeue when queue is empty.
*/
class EmptyQueue
{
public:
	/**
	*	@brief	Display a message for empty queue on screen.
	*/
	void print()
	{
		cout << "EmtpyQueue exception thrown." << endl;
	}
};

/**
*	@brief	Queue class.
*	@details	This class processes as First In, First Out (FIFO), 템플릿을 적용해 다양한 변수 타입을 저장할 수 있다.
*/
template <typename T>
class CircularQueueType
{
public:
	/**
	*	@brief	Allocate dynamic array whose size is maxQueue.
	*	@pre	The maxQueue is defined
	*	@post	Member of items points the allocated array.
	*/
	CircularQueueType() : m_nMaxQueue(maxQueue) { 
		m_pItems = new T[maxQueue];
		m_iFront = 0;
		m_iRear= 0;
	}

	/**
	*	@brief	Allocate dynamic array whose size is max.
	*	@pre	none.
	*	@post	Member of items points the allocated array.
	*/
	CircularQueueType(int max) : m_nMaxQueue(max) {
		m_pItems = new T[max];
		m_iFront = 0;
		m_iRear =  0;
	}

	/**
	*	@brief	Destruct the object. Free the array dynamically allocated.
	*	@pre	Release memory for queue pointer.
	*	@post	none.
	*/
		~CircularQueueType() {
		delete[] m_pItems;
	}


	/**
	*	@brief	Determines whether the queue is full.
	*	@pre	Queue has been initialized.
	*	@post	Function value = (queue is full)
	*/
	bool IsFull() {
		return ((m_iRear + 1) % m_nMaxQueue == m_iFront);
	}

	/**
	*	@brief	Determines whether the queue is empty.
	*	@pre	Queue has been initialized.
	*	@post	Function value = (queue is empty)
	*/
	bool IsEmpty() {
		return (m_iFront == m_iRear);
	}

	/**
	*	@brief	Makes the queue empty.
	*	@pre	Queue has been initialized.
	*	@post	m_iFront와 m_iRear is set same value as Constructer.
	*/
	void MakeEmpty() {
		for (int i = 0; i < m_iRear+1; ++i) {
			DeQueue(*m_pItems[i]);
		}
		m_iRear = m_nMaxQueue;
		m_iFront = m_nMaxQueue;
	}

	/**
	*	@brief	Adds newItem to the last of the queue.
	*	@pre	Queue has been initialized.
	*	@post	If (queue is full), FullQueue exception is thrown; otherwise, newItem is at the last.
	*/
	void EnQueue(T item) {
		if (IsFull() == 1)
			throw FullQueue();
		else {
			m_iRear = (m_iRear + 1) % m_nMaxQueue;
			m_pItems[m_iRear] = item;
		}
	}

	/**
	*	@brief	Removes first item from the queue.
	*	@pre	Queue has been initialized.
	*	@post	If (queue is empty), EmptyQueue exception is thrown; otherwise, first element has been removed from queue. item gets value of removed item.
	*/
	void DeQueue(T& item) {
		if (IsEmpty() == 1)
			throw EmptyQueue();
		else {
			m_iFront = (m_iFront + 1) % m_nMaxQueue;
			item = m_pItems[m_iFront];
		}
	}

	/**
	*	@brief	Print all the items in the queue on screen
	*	@pre	Queue has been initialized.
	*	@post	None.
	*/
	void Print() {
		int index = m_iFront+1;
		while (index != m_iRear+1) {
			cout << m_pItems[index] << endl;
			++index;
		}
	}

private:
	int m_iFront;	//index of one infront of the first element.
	int m_iRear;	//index of the last element.
	int m_nMaxQueue;	//max size of the queue.
	T* m_pItems;	//pointer for dynamic allocation.
};