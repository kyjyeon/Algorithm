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
	if(m_Length > MAXSIZE - 1)
		return true;
	else
		return false;
}


// add a new data into list.
int ArrayList::Add(ItemType inData)
{
	if(!IsFull())
	{
		m_Array[m_Length] = inData;
		m_Length++;
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
	if(m_CurPointer == MAXSIZE)	// end of list이면 -1을 리턴
		return -1;
	data = m_Array[m_CurPointer];	// 현재 list pointer의 레코드를 복사

	return m_CurPointer;
}

int ArrayList::Get(ItemType& data) {
	for (int i = 0; i < this->m_Length; ++i) {
		if (m_Array->CompareByID(data) == EQUAL) {
			data = m_Array[i];
			return 1;
		}
	}
	return 0;
}

int ArrayList::Delete(ItemType data) {
	ItemType temp;
	if (this->GetLength() != 0) {
		for (int i = 0; i < this->GetLength(); ++i) {
			if (this->m_Array[i].GetId == data.GetId) {
				for (int j = i; j < this->GetLength(); ++j) {
					if (j == this->GetLength() - 1) {
						this->m_Array[j] = temp;
						--m_Length;
						return 1;
					}
					this->m_Array[j] = this->m_Array[j + 1];
				}
			}
		}
	}
	else {
		return 0;
	}
}
int ArrayList::Replace(ItemType data) {
	if (this->GetLength() != 0) {
		for (int i = 0; i < this->GetLength(); ++i) {
			if (this->m_Array[i].GetId == data.GetId) {
				this->m_Array[i] = data;
				return 1;
			}
		}
	}
	else {
		return 0;
	}
}