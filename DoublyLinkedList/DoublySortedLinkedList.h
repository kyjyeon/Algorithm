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
*	���Ḯ��Ʈ���� ���̴� NodeType�� ����ü
*/
template <typename T>
struct DoublyNodeType
{
	T data; ///< �� ����� ������.
	DoublyNodeType* prev; ///< ����� ���� ����Ű�� ������.
	DoublyNodeType* next; ///< ����� ������ ����Ű�� ������.
};

/**
*	���ĵ� �����Ḯ��Ʈ Ŭ����
*/
template <typename T>
class DoublySortedLinkedList
{
	friend class DoublyIterator<T>; ///< DoublyIterator�� ģ�� Ŭ����.
public:
	/**
	*	����Ʈ ������.
	*/
	DoublySortedLinkedList() {
		m_nLength = 0;
		m_pFirst = NULL;
		m_pLast = NULL;
	}

	/**
	*	�Ҹ���.
	*/
	~DoublySortedLinkedList() {
		MakeEmpty();
	}

	/**
	*	@brief	����Ʈ�� ������� �ƴ��� �˻��Ѵ�.
	*	@pre	m_nLength�� ���� ������ �־�� �Ѵ�.
	*	@post	������� �ƴ����� �˷��ش�.
	*	@return	��������� true, �ƴϸ� false�� ��ȯ.
	*/
	bool IsEmpty() {
		if (m_nLength == 0)
			return 1;
		else
			return 0;
	}

	/**
	*	@brief	����Ʈ�� ���� á���� �ƴ��� �˻��Ѵ�.
	*	@pre	m_nLength�� ���� ������ �־�� �Ѵ�.
	*	@post	���� á���� �ƴ����� �˷��ش�.
	*	@return	���� �������� true, �ƴϸ� false�� ��ȯ.
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
	*	@brief	����Ʈ�� ����.
	*	@pre	����.
	*	@post	m_pFirst�� m_pLast�� ������ ��� �����͸� �����.
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
	*	@brief	����Ʈ�� ���̸� ��ȯ�Ѵ�.
	*	@pre	����.
	*	@post	����Ʈ�� ���̸� ��ȯ.
	*	@return	m_nLength ����Ʈ�� ���� ��ȯ.
	*/
	int GetLength() const {
		return m_nLength;
	}

	/**
	*	@brief	���ο� �������� ����Ʈ�� �߰��Ѵ�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	�������� ����Ʈ�� �߰��Ѵ�.
	*	@return	���� �������� ������ 0�� ��ȯ�ϰ�, �Է¿� �����ϸ� 1�� ��ȯ.
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
	*	@brief	�Է¹��� �������� ����Ʈ���� �����Ѵ�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	�Է¹��� �������� ����Ʈ���� ã�� �����Ѵ�.
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
	*	@brief	�Է¹��� ���������� ������ �ٲ۴�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	���ο� ������ ��ü�ȴ�.
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
	*	@brief	�Է¹��� �������� ������ ���Ͽ� ���� ����Ʈ�� �������� �����´�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	�˻��� �����͸� �����ۿ� �ִ´�.
	*	@return	��ġ�ϴ� �����͸� ã���� 1, �׷��� ������ 0�� ��ȯ.
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
	DoublyNodeType<T>* m_pFirst; ///< �ּҰ��� ������ ����Ʈ�� �� ó��.
	DoublyNodeType<T>* m_pLast; ///< �ִ��� ������ ����Ʈ�� �� ��.
	int m_nLength; ///< ����Ʈ�� ����
};

#endif _DOUBLYSORTEDLINKEDLIST_H