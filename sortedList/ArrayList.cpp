#include "ArrayList.h"


// Make list empty.
void ArrayList::MakeEmpty()
{
	m_Length = 0;
}


// Get a number of records in current list.
int ArrayList::GetLength()
{
	return m_Length;
}


// Check capacity of list is full.
bool ArrayList::IsFull()
{
	if (m_Length > MAXSIZE - 1)
		return true;
	else
		return false;
}


// add a new data into list.
int ArrayList::Add(ItemType inData)
{
	if (!IsFull())
	{
		//현재 담겨있는 데이터가 없을땐 비교불가하므로 가정 첫번째 list값에 데이터를 넣는다
		if (m_Length == 0) {
			m_Array[0] = inData;
			++m_Length;
		}
		//리스트에 한가지 데이터가 존재할경우 이 한가지와만 비교하면 되므로 크고 작을때를 compareById 함수를 사용해 클시 위치를 변경, 작을 시 두번째 리스트칸에 그래도 데이터를 삽입시킨다
		else if (m_Length == 1) {
			//들어오는 데이터 id값이 m_Array객체에 가장 첫번째 데이터 id값보다 작다면 가장 첫번째 리스트값에 새로운 레코드를 넣고 클시 그 뒤에 이어 넣는다
			if (m_Array[0].CompareByID(inData) == GREATER) {
				ItemType temp;
				temp = m_Array[0];
				m_Array[0] = inData;
				m_Array[1] = temp;
				++m_Length;
			}
			else if (m_Array[0].CompareByID(inData) == LESS) {
				m_Array[1] = inData;
				++m_Length;
			}
		}
		//리스트에 2개이상의 데이터가 이미 존재하거나 꽉차있지 않다면 들어가야할 데이터가 존재하는 데이터 사이에 들어갈지, 가장 처음으로 들어갈지, 마지막으로 들어갈지 ID값간 CompareByID함수를 통해 비교해 넣는다 
		else if (m_Length >= 2 && !IsFull()) {
			if (m_Array[0].CompareByID(inData) == GREATER) {
				for (int i = 0; i < GetLength(); i++) {
					m_Array[GetLength() - i] = m_Array[GetLength() - i - 1];
				}
				m_Length++;
				m_Array[0] = inData;
			}
			else if (m_Array[m_Length - 1].CompareByID(inData) == LESS) {
				m_Length++;
				m_Array[m_Length - 1] = inData;
			} 
			else {
				for (int i = 0; i < GetLength(); i++) {
					if (m_Array[i].GetId() < inData.GetId() && m_Array[i + 1].GetId() > inData.GetId()) {
						for (int j = 0; j < (GetLength() - (i + 1)); ++j) {
							m_Array[i + 2 + j] = m_Array[i + 1 + j];
						}
						++m_Length;
						m_Array[i + 1] = inData;
					}
				}
			}
		}
	}
	else
		return 0;

	return 1;
}


// Initialize list iterator.
void ArrayList::ResetList()
{
	m_CurPointer = -1;
}


// move list iterator to the next item in list and get that item.
int ArrayList::GetNextItem(ItemType& data)
{
	m_CurPointer++;	// list pointer 증가
	if (m_CurPointer == MAXSIZE)	// end of list이면 -1을 리턴
		return -1;
	data = m_Array[m_CurPointer];	// 현재 list pointer의 레코드를 복사

	return m_CurPointer;
}

int ArrayList::Get(ItemType& data) {
	for (int i = 0; i < m_Length; ++i) {
		if (m_Array[i].CompareByID(data) == EQUAL) {
			data = m_Array[i];
			return 1;
		}
	}
	return 0;
}

int ArrayList::Delete(ItemType data) {
	//임시 ItemType 객체선언
	ItemType temp;
	//현재 객체의 list가 꽉차있지 않다면 아래와 같은 for문실행
	if (GetLength() != 0) {
		for (int i = 0; i < GetLength(); ++i) {
			//리스트 안에 들어있는 각각의 레코드의 id값과 찾고자 하는 id값의 일치여부확인
			if (m_Array[i].GetId() == data.GetId()) {
				//일치하는 레코드 리스트를 지우고 그 다음 나오는 데이터들을 리스트에서 한칸씩 앞으로 당겨온다
				for (int j = i; j < GetLength(); ++j) {
					if (j == GetLength() - 1) {
						m_Array[j] = temp;
						--m_Length;
						return 1;
					}
					m_Array[j] = m_Array[j + 1];
				}
			}
		}
	}
	else {
		return 0;
	}
}

int ArrayList::Replace(ItemType data) {
	if (GetLength() != 0) {
		for (int i = 0; i < GetLength(); ++i) {
			if (m_Array[i].GetId() == data.GetId()) {
				m_Array[i] = data;
				return 1;
			}
		}
	}
	else {
		return 0;
	}
}

int ArrayList::GetBinarySearch(ItemType& data) {

	/*참조 받아온 ItemType 객체의 아이디 변수, BinarySearch에 필요한 시작값 중간값 끝값, 
	이 3가지 위치에 있는 ItemType 객체가 가지는 ID값을 나타내는 변수를 각각 선언해준다*/
	int id = data.GetId();
	int start, end, middle, startLoc, endLoc, middleLoc;
	
	startLoc = 0;
	endLoc = GetLength() - 1;
	middleLoc = endLoc / 2;

	start = m_Array[startLoc].GetId();
	end = m_Array[endLoc].GetId();
	middle = m_Array[middleLoc].GetId();

	//bool 형태로 found 변수를 선언해 search를 통해 찾을 시 true를 만들어준다
	bool found = false;

	//found bool이 true가 될때까지 BinarySearch를 실행하는 while문
	while (found) {
		//아이디가 가운데값과 바로 같다면 found가 true되고 loop를 빠져나옴
		if (id == middle) {
			data = m_Array[middle];
			found = true;
			break;
		}
		// id 변수 값이 middle보다 클때 middle 보다 작은 위치의 값들은 제외한채로 범위를 줄여감
		else if (id > middle) {
			startLoc = middleLoc + 1;
			middleLoc = (startLoc + endLoc) / 2;
			//최종적으로 시작, 중간, 끝이 겹치는 지점이 검색하여 찾음에 성공을 뜻하므로 data변수에 해당 m_array위치의 데이터를 넣어줌
			if (startLoc == middleLoc == endLoc) {
				data = m_Array[startLoc];
				found = true;
				break;
			}
			// 시작 위치가 마지막 위치보다 커졌을때는 list 범위 전체를 훍고 최종적으로 일치하는 ID값이 없단것을 뜻하으로 바로 0을 return
			else if (startLoc > endLoc)
				return 0;
		}
		// id 변수 값이 middle보다 작을때 middle 보다 큰 위치의 값들은 제외한채로 범위를 줄여감
		else if (id < middle) {
			endLoc = middle - 1;
			middleLoc = (startLoc + endLoc) / 2;
			if (startLoc == middleLoc == endLoc) {
				data = m_Array[startLoc];
				found = true;
				break;
			}
			else if (startLoc > endLoc)
				return 0;
		}
	}
	//found가 true일시 1, false 유지 시 0 반환
	if (found == true)
		return 1;
	else
		return 0;
}