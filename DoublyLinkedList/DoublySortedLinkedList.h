#pragma once
#ifndef _DOUBLYSORTEDLINKEDLIST_H
#define _DOUBLYSORTEDLINKEDLIST_H

template <typename T>
class Iterator;

#include "ItemType.h"
#include "DoublyIterator.h"

#define min ItemType(INT_MIN)
#define max ItemType(INT_MAX)

template<typename T>
class DoublyIterator;

/**
*	연결리스트에서 쓰이는 NodeType의 구조체
*/
template <typename T>
struct DoublyNodeType
{
	T data; ///< 각 노드의 데이터.
	DoublyNodeType* prev; ///< 노드의 앞을 가리키는 포인터.
	DoublyNodeType* next; ///< 노드의 다음를 가리키는 포인터.
};

/**
*	정렬된 더블연결리스트 클래스
*/
template <typename T>
class DoublySortedLinkedList
{
	friend class DoublyIterator<T>; ///< DoublyIterator와 친구 클래스.
public:
	/**
	*	디폴트 생성자.
	*/
	DoublySortedLinkedList() {
		m_nLength = 0;
		m_pFirst = NULL;
		m_pLast = NULL;
	}

	/**
	*	소멸자.
	*/
	~DoublySortedLinkedList() {
		MakeEmpty();
	}

	/**
	*	@brief	리스트가 비었는지 아닌지 검사한다.
	*	@pre	m_nLength가 값을 가지고 있어야 한다.
	*	@post	비었는지 아닌지를 알려준다.
	*	@return	비어있으면 true, 아니면 false를 반환.
	*/
	bool IsEmpty() {
		if (m_nLength == 0)
			return 1;
		else
			return 0;
	}

	/**
	*	@brief	리스트가 가득 찼는지 아닌지 검사한다.
	*	@pre	m_nLength가 값을 가지고 있어야 한다.
	*	@post	가득 찼는지 아닌지를 알려준다.
	*	@return	가득 차있으면 true, 아니면 false를 반환.
	*/
	bool IsFull() {
		DoublyNodeType<ItemType>* location;
		try
		{
			location = new DoublyNodeType<ItemType>;
			delete location;
			return false;
		}
		catch (bad_alloc exception)
		{
			return true;
		}
	}

	/**
	*	@brief	리스트를 비운다.
	*	@pre	없음.
	*	@post	m_pFirst와 m_pLast를 제외한 모든 데이터를 지운다.
	*/
	int MakeEmpty() {
		DoublyNodeType<ItemType>pItem;
		DoublyIterator<ItemType>itor(*this);

		while (itor.NotNull()) {
			pItem = itor.m_pCurPointer;
			itor.Next();
			delete pItem;
		}
		m_pFirst = m_pLast = NULL;
		
		return 1;
	}

	/**
	*	@brief	리스트의 길이를 반환한다.
	*	@pre	없음.
	*	@post	리스트의 길이를 반환.
	*	@return	m_nLength 리스트의 길이 반환.
	*/
	int GetLength() const {
		return m_nLength;
	}

	/**
	*	@brief	새로운 아이템을 리스트에 추가한다.
	*	@pre	item을 입력받는다.
	*	@post	아이템을 리스트에 추가한다.
	*	@return	같은 아이템이 있으면 0을 반환하고, 입력에 성공하면 1을 반환.
	*/
	int Add(T item) {
		DoublyNodeType<T> *newNode;
		newNode = new DoublyNodeType<T>;
		newNode->data = item;
		if (m_nLength == 0) {
			newNode->prev = NULL;
			newNode->next = NULL;

			m_pFirst = newNode;
			m_pLast = newNode;
			++m_nLength;

			return 1;
		}
		else if (IsFull() == 1)
			return 0;
		else if (m_nLength > 0) {
			DoublyIterator<T> itor;

			if (m_pFirst->data > item) {
				newNode->prev = NULL;
				newNode->next = m_pFirst;
				m_pFirst->prev = newNode;

				++m_nLength;
				return 1;
			}
			else if (item > m_pLast->data) {
				newNode->next = NULL;
				newNode->prev = m_pLast;
				m_pLast->next = newNode;
				m_pLast = newNode;

				++m_nLength;
				return 1;
			}
			else if (item > m_pFirst->data && item < m_pLast->data) {
				DoublyIterator<T> itor;
				itor(*this);
				itor.m_pCurPointer = itor.m_pCurPointer->next;
				
				while (itor.m_pCurPointer->next != NULL) {
					if (itor.m_pCurPointer->data < item &&  itor.m_pCurPointer->next > item) {
						newNode->prev = itor.m_pCurPointer->prev;
						newNode->next = itor.m_pCurPointer;
						itor.m_pCurPointer->prev->next = newNode;
						itor.m_pCurPointer->prev = newNode;
						
						++m_nLength;
						return 1;
					}
				}
			}
		}
		return 0;
	}

	/**
	*	@brief	입력받은 아이템을 리스트에서 삭제한다.
	*	@pre	item을 입력받는다.
	*	@post	입력받은 아이템을 리스트에서 찾아 삭제한다.
	*/
	void Delete(T item) {
		if (IsEmpty() == 0) {
			return 0;
		}
		else if (m_nLength > 0) {
			DoublyIterator<T> itor;
			itor(*this);

			if (this->Get(item) == 1) {
				while (itor.m_pCurPointer->next != NULL) {
					DoublyNodeType<T> *temp;
					if (m_pFirst->data == item) {
						if (itor.m_pCurPointer == m_pFirst) {
							temp = itor.m_pCurPointer;
							m_pFirst = itor.m_pCurPointer->next;
							itor.m_pCurPointer = itor.m_pCurPointer->next;

							delete[] temp;
						}
					}
					else if (m_pLast->data == item) {
						temp = itor.m_pCurPointer;
						m_pLast->prev->next = NULL;
						m_pLast = m_pLast->prev;

						delete[] temp;
					}
					if (itor.m_pCurPointer->data == item) {
						temp = itor.m_pCurPointer;
						itor.m_pCurPointer->prev->next = itor.m_pCurPointer->next;
						itor.m_pCurPointer->next->prev = itor.m_pCurPointer->prev;
						itor.m_pCurPointer = itor.m_pCurPointer->next;

						delete[] temp;
					}
				}
			}
		}

	}

	/**
	*	@brief	입력받은 아이템으로 정보를 바꾼다.
	*	@pre	item을 입력받는다.
	*	@post	새로운 정보로 교체된다.
	*/
	void Replace(T item) {

		DoublyIterator<T> itor;
		itor(*this);
		DoublyNodeType<T> temp;
		DoublyNodeType<T> newNode;

		while (itor.m_pCurPointer->next != NULL) {
			if (itor.m_pCurPointer->data == item) {
				temp = itor.m_pCurPointer;

				newNode->data = item;
				itor.m_pCurPointer->prev->next = newNode;
				newNode->next = itor.m_pCurPointer->next;
				newNode->prev = itor.m_pCurPointer->prev;
				itor.m_pCurPointer->next->prev = newNode;

				delete[] temp;
				break;
			}
		}
		
	}

	/**
	*	@brief	입력받은 아이템의 정보와 비교하여 같은 리스트의 아이템을 가져온다.
	*	@pre	item을 입력받는다.
	*	@post	검색된 데이터를 아이템에 넣는다.
	*	@return	일치하는 데이터를 찾으면 1, 그렇지 않으면 0을 반환.
	*/
	int Get(T& item) {
		DoublyIterator<T> itor;
		itor(*this);
		if (itor.NotNull() == 1) {
			if (item == itor.GetCurrentNode()) {
				item = itor.GetCurrentNode();
				return 1;
			}
			while (itor.NextNotNull() != 0) {
				if (item == itor.Next()) {
					item = itor.m_pCurPointer->data;
					return 1;
				}
			}
		}
		return 0;
	}

private:
	DoublyNodeType<T>* m_pFirst; ///< 최소값을 가지는 리스트의 맨 처음.
	DoublyNodeType<T>* m_pLast; ///< 최댓값을 가지는 리스트의 맨 끝.
	int m_nLength; ///< 리스트의 길이
};

#endif _DOUBLYSORTEDLINKEDLIST_H