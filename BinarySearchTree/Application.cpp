#include "Application.h"

Application::Application()
{
	
}

void Application::run()
{
	int m_Command;
	while (1)
	{
		m_Command = GetCommand();

		switch (m_Command)
		{
		case 1:
			AddItem();
			break;
		case 2:
			DeleteItem();
			break;
		case 3:
			DisplayItem();
			break;
		case 4:
			SearchItem();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal sellection...\n";
			break;
		}
	}
}

int Application::GetCommand() {

	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add item" << endl;
	cout << "\t   2 : Delete item" << endl;
	cout << "\t   3 : Display item" << endl;
	cout << "\t   4 : Search item" << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}