#include "Application.h"

// Program driver.
void Application::Run()
{
	try
	{
		while (1)
		{
			m_Command = GetCommand();

			switch (m_Command)
			{
			case 1:		// Enqueue Element.
				enQueue();
				break;
			case 2:		// Dequeue Element.
				deQueue();
				break;
			case 3:		// Is Empty?
				CheckEmpty();
				break;
			case 4:		// Is Full?
				CheckFull();
				break;
			case 5:		// Test EmptyQueue Exception.
				TestEmptyException();
				break;
			case 6:		// Test FullQueue Exception.
				TestFullException();
				break;
			case 7:		// Print all the elements in the Queue.
				DisplayAllItem();
				break;
			case 0:
				return;
			default:
				cout << "\tIllegal selection...\n";
				break;
			}
		}
	}
	catch (FullQueue)
	{
		cout << "FullQueue exception thrown." << endl;
	}

	catch (EmptyQueue e)
	{
		e.print();
	}
}


// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t--- ID - Command -----" << endl;
	cout << "\t    1. Enqueue Element" << endl;
	cout << "\t    2. Dequeue Element" << endl;
	cout << "\t    3. Is Empty?" << endl;
	cout << "\t    4. Is Full?" << endl;
	cout << "\t    5. EmptyQueue Exception test" << endl;
	cout << "\t    6. FullQueue Exception test" << endl;
	cout << "\t    7. Print all" << endl;
	cout << "\t    0. Quit" << endl << endl;
	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}


// Enqueue new record into the Queue.
int Application::enQueue()
{
	if (!m_CQueue.IsFull())
	{
		ItemType item;
		cout << "Input Element : ";
		cin >> item;

		m_CQueue.EnQueue(item);
		DisplayAllItem();

		return 1;
	}
	else
		cout << "²Ë Ã¡½À´Ï´Ù." << endl;

	return 0;
}


// Dequeue a record of first from the Queue.
int Application::deQueue()
{
	if (!m_CQueue.IsEmpty())
	{
		ItemType item;
		m_CQueue.DeQueue(item);
		cout << "Dequeue Element : " << item << endl << endl;

		DisplayAllItem();

		return 1;
	}

	return 0;
}


// Check the Queue is empty state.
int Application::CheckEmpty()
{
	if (m_CQueue.IsEmpty())
	{
		cout << "Queue is Empty." << endl << endl;
		return 1;
	}
	else
	{
		cout << "Queue is not Empty." << endl << endl;
		return 0;
	}
}


// Check the Queue is full state.
int Application::CheckFull()
{
	if (m_CQueue.IsFull())
	{
		cout << "Queue is Full." << endl << endl;
		return 1;
	}
	else
	{
		cout << "Queue is not Full." << endl << endl;
		return 0;
	}
}


// Test the exeception of empty Queue.
void Application::TestEmptyException()
{
	ItemType item;

	while (1)
		m_CQueue.DeQueue(item);
}


// Test the exeception of full Queue.
void Application::TestFullException()
{
	ItemType item;
	srand((unsigned long)time(NULL));

	while (1)
	{
		item = rand();
		m_CQueue.EnQueue(item);
		m_CQueue.Print();
	}
}


// Display all records in the Queue on screen.
void Application::DisplayAllItem()
{
	m_CQueue.Print();
}
