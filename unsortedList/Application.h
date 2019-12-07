#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "ArrayList.h"

#define FILENAMESIZE 1024

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
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddItem();

	/**
	*	@brief	Display all records in the list on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAllItem();

	/**
	*	@brief	Open a file by file descriptor as an input file.
	*	@pre	a file for reading is exist.
	*	@post	open the file for reading.
	*	@param	fileName	a filename to open for reading.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenInFile(char *fileName);

	/**
	*	@brief	Open a file by file descriptor as an output file.
	*	@pre	list should be initialized.
	*	@post	open the file for writing.
	*	@param	fileName	a filename to open for writing.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenOutFile(char *fileName);

	/**
	*	@brief	Open a file as a read mode, read all data on the file, and set list by the data.
	*	@pre	The file is not opened.
	*	@post	list holds all records from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile();

	/**
	*	@brief	Open a file as a write mode, and write all data into the file,
	*	@pre	The file is not opened.
	*	@post	the list is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile();

	/** 
	*	@brief 검색하고자 하는 ID를 keyboard로 받아와 list에서 일치하는 결과를 찾아 출력
	*	@pre list가 선언되어 검색가능한 item들이 존재하여야 한다.
	*	@post List 안에 있는 record들과 keyboard로 받아온 record 비교해서 일치하는 기록을 찾은 후 출력한다 
	*	@return 일치시 1, 일치하는 record가 없을 시 0을 반환한다
	*/
	int SearchData();

	/** 
	*	@brief 삭제하고자 하는 record를 keyboard로 받아와 list에서 일치하는 결과를 찾아 출력
	*	@pre list가 선언되어 item들이 삭제 가능한존재하여야 한다.
	*	@post List 안에 있는 ID들과 keyboard로 받아온 ID를 비교해서 일치하는 기록을 찾은 후 기록을 ItemType 처음 선언시의 상태로 초기화한 후, 해당 record 이후 list의 record들은 위치를 -1하여 앞으로 당겨온다
	*	@return 일치시 1, 일치하는 record가 없을 시 0을 반환한다
	*/
	int DeleteItem();

	/** 
	*	@brief 갱신하고자 하는 record를 keyboard로 받아와 list에서 일치하는 결과를 찾고, 바꾸고자하는 record를 입력받아 해당 list 위치에 갱신시킨다.
	*	@pre list가 선언되어 갱신 가능한 item들이 존재하여야 한다.
		@post List 안에 있는 ID들과 keyboard로 받아온 ID를 비교해서 일치하는 기록을 찾은 후 갱신하고자하는 record를 다시 입력받아 기존 record에 재할당 시킨다 
	*	@return 검색후 갱신 성공시 1, 검색 불가 시 0을 반환
	*/
	int UpdateItem();


private:
	ifstream m_InFile;		///< input file descriptor.
	ofstream m_OutFile;		///< output file descriptor.
	ArrayList m_List;		///< item list.
	int m_Command;			///< current command number.
};

#endif	// _APPLICATION_H
