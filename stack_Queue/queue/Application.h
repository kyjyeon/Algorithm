#ifndef _APPLICATION_H
#define _APPLICATION_H


#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Queue.h"


/**
*	application class for item management simply.
*/
class Application
{
public:
	/**
	*	default constructor.
	*/
	Application()
	{
		m_Command = 0;
	}

	/**
	*	destructor.
	*/
	~Application() {}

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run();

	/**
	*	@brief	Display command on screen and get a input from keyboard.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	int GetCommand();

	/**
	*	@brief	Enqueue new record into the Queue.
	*	@pre	The Queue should be initialized.
	*	@post	A new record is Enqueueed into the Queue.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int enQueue();

	/**
	*	@brief	Dequeue a record of first from the Queue.
	*	@pre	The Queue should be initialized.
	*	@post	A top record is Dequeueed.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int deQueue();

	/**
	*	@brief	Check the Queue is empty state.
	*	@pre	The Queue should be initialized.
	*	@post	Display the state of Queue on screen.
	*	@return	1 if the Queue is empty, otherwise 0.
	*/
	int CheckEmpty();

	/**
	*	@brief	Check the Queue is full state.
	*	@pre	The Queue should be initialized.
	*	@post	Display the state of Queue on screen.
	*	@return	1 if the Queue is full, otherwise 0.
	*/
	int CheckFull();

	/**
	*	@brief	Test the exeception of empty Queue.
	*	@pre	The Queue should be initialized.
	*	@post	Do exception funciton when the Queue is empty.
	*/
	void TestEmptyException();

	/**
	*	@brief	Test the exeception of full Queue.
	*	@pre	The Queue should be initialized.
	*	@post	Do exception funciton when the Queue is full.
	*/
	void TestFullException();

	/**
	*	@brief	Display all records in the Queue on screen.
	*	@pre	The Queue should be initialized.
	*	@post	Display all records on screen.
	*/
	void DisplayAllItem();

private:
	CircularQueueType<ItemType> m_CQueue;	///< item queue.
	int m_Command;			///< current command number.
};

#endif	// _APPLICATION_H