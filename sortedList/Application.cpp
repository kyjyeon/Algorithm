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
		case 4:		// [작성] search item from list.
			SearchItemById();
			break;
		case 5:		// [작성] search item from list.
			RetriveRecordByMemberName();
			break;
		case 6:		// [작성] delete item from list
			DeleteItem();
			break;
		case 7:		// [작성] update item in list
			ReplaceItem();
			break;
		case 8:		// load list data from a file.
			ReadDataFromFile();
			break;
		case 9:		// save list data into a file.
			WriteDataToFile();
			break;
		case 0:
			return;
		default:
			cout << "\tllegal selection...\n";
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
	cout << "\t   4 : Search item by ID" << endl;
	cout << "\t   5 : Search item by name" << endl;
	cout << "\t   6 : Delete item" << endl;
	cout << "\t   7 : Update item" << endl;
	cout << "\t   8 : Get from file" << endl;
	cout << "\t   9 : Put to file " << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}


// Add new record into list.
int Application::AddItem()
{
	// [작성] 입력받은 레코드를 리스트에 add, 리스트가 full일 경우는 add하지 않고 0을 리턴
	if (Application::m_List.IsFull()) {
		return 0;
	}
	else {
		ItemType temp;
		temp.SetRecordFromKB();
		Application::m_List.Add(temp);
	}

	// [작성] 현재 list 출력
	return 1;
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
	// [작성] 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.

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
	if (!OpenInFile(filename))
		return 0;

	// 파일의 모든 내용을 읽어 list에 추가
	while (!m_InFile.eof())
	{
		// array에 학생들의 정보가 들어있는 structure 저장
		data.ReadDataFromFile(m_InFile);
		m_List.Add(data);
	}

	m_InFile.close();	// file close

	// 현재 list 출력
	DisplayAllItem();

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
	int length = m_List.GetLength();
	int curIndex = m_List.GetNextItem(data);
	while (curIndex < length && curIndex != -1)
	{
		data.WriteDataToFile(m_OutFile);
		curIndex = m_List.GetNextItem(data);
	}

	m_OutFile.close();	// file close

	return 1;
}

int Application::SearchItemById(){
	ItemType data;
	data.SetIdFromKB();
	if (m_List.Get(data) == 1) {
		cout << "ID found in List" << endl;
		return 1;
	}
	else {
		cout << "ID not found in List" << endl;
		return 0;
	}
	
}

int Application::DeleteItem() {
	ItemType data;
	data.SetIdFromKB();
	int result = m_List.Delete(data);
	result;
	if (result == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int Application::ReplaceItem() {
	ItemType data;
	data.SetRecordFromKB();
	int result = m_List.Delete(data);
	if (result == 1)
		return 1;
	else
		return 0;
}

int Application::SearchItemByBinarySearch() {
	ItemType temp;
	temp.SetIdFromKB();
	if (m_List.GetBinarySearch(temp) == 1) {
		cout << "Data found" << endl;
		return 1;
	}
	else {
		cout << "Data not found" << endl;
		return 0;
	}
}

int Application::SearchListByMemberName(ItemType &inData) {
	m_List.ResetList();
	ItemType temp;
	bool found = false;
	int cur = m_List.GetNextItem(temp), count = 0;
	while (cur < m_List.GetLength() && cur != -1) {
		if (temp.GetName().find(inData.GetName()) != -1) {
			temp.DisplayRecordOnScreen();
			count++;
			found = true;
		}
		cur = m_List.GetNextItem(temp);
	}
	if (found)
		return 0;
	else
		return 1;
}

int Application::RetriveRecordByMemberName() {
	ItemType temp;
	temp.SetNameFromKB();
	if (SearchListByMemberName(temp) == 1)
		return 1;
	else
		return 0;
}