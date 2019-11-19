#pragma once
#ifndef _DOUBLYITERATOR_H
#define _DOUBLYITERATOR_H

#include "DoublySortedLinkedList.h"

template<typename T>
struct DoublyNodeType;
template<typename T>
class DoublySortedLinkedList;

/**
*	연결리스트에서 쓰이는 Iterator의 클래스.
*/
template <typename T>
class DoublyIterator
{
	friend class DoublySortedLinkedList<T>;
public:
	/**
	*	디폴트 생성자.
	*/
	DoublyIterator(const DoublySortedLinkedList<T>& list) : m_List(list), m_pCurPointer(list.m_pFirst)
	{}; ///< DoublySortedLinkedList와 친구 클래스.


	bool NotNull() {
		if (m_pCurPointer->data != NULL) {
			return 1;
		}
		else if(m_pCurPointer->data == NULL) {
			return 0;
		}
	}

	bool NextNotNull() {
		if (m_pCurPointer->next->next != NULL) {
			return 1;
		}
		else if (m_pCurPointer->next->next == NULL) {
			return 0;
		}
	}

	T First() {
		return m_List.m_pFirst->data;
	}

	T Next() {
		m_pCurPointer = m_pCurPointer->next;
		return m_pCurPointer->data;
	}

	DoublyNodeType<T> GetCurrentNode() {
		return m_pCurPointer->data;
	}

private:
	const DoublySortedLinkedList<T>& m_List;
	DoublyNodeType<T>* m_pCurPointer;
};

#endif _DOUBLYITERATOR_H