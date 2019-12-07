#include "Application.h"


// Program driver.
void Application::Run()
{
	while (1)
	{
		m_Command = GetCommand();

		switch (m_Command)
		{
		case 1:		// read a record and add to list.
			AddItem();
			break;
		case 2:		// display all the records in list on screen.
			DisplayAllItem();
			break;
		case 3:		// make empty list.
			m_List.MakeEmpty();
			break;
		case 4:		// search item from list.
			SearchData();
			break;
		case 5:		// delete item from list
			DeleteItem();
			break;
		case 6:		// update item in list
			UpdateItem();
			break;
		case 7:		// load list data from a file.
			ReadDataFromFile();
			break;
		case 8:		// save list data into a file.
			WriteDataToFile();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}


// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add item" << endl;
	cout << "\t   2 : Print all on screen" << endl;
	cout << "\t   3 : Make empty list" << endl;
	cout << "	   4 : Search for an item" << endl;
	cout << "\t   5 : Delete an item" << endl;
	cout << "\t   6 : Update an item" << endl;
	cout << "\t   7 : Get from file" << endl;
	cout << "\t   8 : Put to file " << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}


// Add new record into list.
int Application::AddItem()
{
	ItemType temp;
	// [작성] 입력받은 레코드를 리스트에 add, 리스트가 full일 경우는 add하지 않고 0을 리턴
	if (Application::m_List.IsFull()) {
		return 0;
	}

	// [작성] 현재 list 출력
	else {
		temp.SetRecordFromKB();
		Application::m_List.Add(temp);
		temp.DisplayRecordOnScreen();
		return 1;
	}
}


// Display all records in the list on screen.
void Application::DisplayAllItem()
{
	ItemType data;
	m_List.ResetList();
	cout << "\n\tCurrent list" << endl;
	// [작성] list의 모든 데이터를 화면에 출력

	for (int i = 0; i < m_List.GetLength(); ++i) {
		m_List.GetNextItem(data);
		data.DisplayRecordOnScreen();
	}

}


// Open a file by file descriptor as an input file.
int Application::OpenInFile(char *fileName)
{
	m_InFile.open(fileName);	// file open for reading.
	if (m_InFile.is_open()) {
		return 1;
	}
	else {
		return 0;
	}
	// [작성] 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.

}


// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char *fileName)
{
	m_OutFile.open(fileName);	// file open for writing.
	if (m_OutFile.is_open()) {
		return 1;
	}
	else {
		return 0;
	}

}


// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	ItemType data;	// 읽기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (OpenInFile(filename) == 0)
		return 0;
	// 파일의 모든 내용을 읽어 list에 추가	
		while (!OpenInFile(filename)) {
			data.ReadDataFromFile(m_InFile);
			m_List.Add(data);
		}
	m_InFile.close();	// file close

	// 현재 list 출력
	data.DisplayRecordOnScreen();
	return 1;
}


// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	ItemType data;	// 쓰기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!OpenOutFile(filename))
		return 0;

	// list 포인터를 초기화
	m_List.ResetList();

	// list의 모든 데이터를 파일에 쓰기
	for (int i = 0; i < m_List.GetLength(); ++i) {
		m_List.GetNextItem(data);
		data.WriteDataToFile(m_OutFile);
	}

	m_OutFile.close();	// file close
	return 1;
}

int Application::SearchData() {
	ItemType data;
	data.SetIdFromKB();
	int result = m_List.Get(data);
	if (result == 1) {
		cout << "Found item : " << endl;
		data.DisplayRecordOnScreen();
		return 1;
	}
	else {
		return 0;
	}
}

int Application::DeleteItem() {
	ItemType data;
	data.SetIdFromKB();
	int result = m_List.Delete(data);
	if (result == 1) {
		cout << "Delete Item : " << endl;
		data.DisplayRecordOnScreen();
		return 1;
	}
	else {
		return 0;
	}
}

int Application::UpdateItem() {
	ItemType data;
	data.SetIdFromKB();
	int result = m_List.Get(data);
	if (result == 1) {
		m_List.Replace(data);
		cout << "Updated item: " << endl;
		data.DisplayRecordOnScreen();
		return 1;
	}
	else
		return 0;
}
