#ifndef _UNSORTEDLIST_H
#define _UNSORTEDLIST_H

#include <iostream>
#include <fstream>	
#include <string>
using namespace std;

#include "ItemType.h"

#define MAXSIZE 5

/**
*	array based simple unsorted list.
*/
class ArrayList
{
public:
	/**
	*	default constructor.
	*/
	ArrayList()
	{
		m_Length = 0;
		ResetList();
	}

	/**
	*	destructor.
	*/
	~ArrayList() {}

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	int GetLength();

	/**
	*	@brief	Check capacity of list is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull();

	/**
	*	@brief	add a new data into list.
	*	@pre	list should be initialized.
	*	@post	added the new record into the list.
	*	@param	data	new data.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Add(ItemType data);

	/**
	*	@brief	Initialize list iterator.
	*	@pre	list should be initialized.
	*	@post	iterator is reset.
	*/
	void ResetList();

	/**
	*	@brief	move list iterator to the next item in list and get that item.
	*	@pre	list and list iterator should not be initialized.
	*	@post	iterator is moved to next item.
	*	@param	data	get current iterator's item. it does not need to be initialized.
	*	@return	index of current iterator's item if is not end of list, oterwise return -1.
	*/
	int GetNextItem(ItemType& data);

	/** [ÀÛ¼º]
	*	@brief List 안에 존재하는 record들과 파라미터로 받아온 record가 일치하는 위치를 찾아낸다
	*	@pre List가 선언되어있어야한다, 참조로 받아오는 객체에 record ID가 정의되어있어야한다.
	*	@post 리스트의 record들중 파라미터 record와 일치하는 아이디가 있을시 파라미터에 해당 list를 멤버변수들을 할당.
	*	@param data  data 객체의 ID와 일치하는 list에 record 멤버변수들을 data 객체에 할당
	*	@return record 일치 시 1반환, 실패시 0 반환.
	*/
	int Get(ItemType& data);

	/** [ÀÛ¼º]
	*	@brief 삭제하고자 하는 record를 keyboard로 받아와 list에서 일치하는 결과를 찾아 출력
	*	@pre list가 선언되어 item들이 삭제 가능한존재하여야 한다.
	*	@post List 안에 있는 ID들과 keyboard로 받아온 ID를 비교해서 일치하는 기록을 찾는다. 이후 기록을 ItemType 처음 선언시의 상태로 초기화한 후, 해당 record 이후 list의 record들은 위치를 -1하여 앞으로 당겨온다
	*	@param data   원하는 아이디값이 담긴 객체를 참조없이 받아와 list index별 record와 비교한다
	*	@return 일치시 후 삭제 성공시 1, 일치하는 record가 없을 시 0을 반환한다
	*/
	int Delete(ItemType data);

	/** [ÀÛ¼º]
	*	@brief 갱신하고자 하는 record를 받아와 list에서 일치하는 결과를 찾고, 바꾸고자하는 record를 입력받아 해당 list 위치에 갱신시킨다.
	*	@pre list가 선언되어 갱신 가능한 item들이 존재하여야 한다. 받아오는 파라미터에 객체에는 찾고자하는 ID 값이 정의 되어있어한다
		@post List 안에 있는 ID들과 keyboard로 받아온 ID를 비교해서 일치하는 기록을 찾은 후 갱신하고자하는 record를 다시 입력받아 기존 record에 재할당 시킨다 
		@param data   찾고자 하는 record의 ID가 담긴 객체를 data라는 ItemType 파라미터로 받아온다.
	*	@return 검색후 갱신 성공시 1, 검색 불가 시 0을 반환
	*/
	int Replace(ItemType data);

private:
	ItemType m_Array[MAXSIZE];  ///< list array.
	int m_Length;				///< number of elements in list.
	int m_CurPointer;			///< iterator pointer.
};

#endif	// _UNSORTEDLIST_H