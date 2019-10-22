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
		//���� ����ִ� �����Ͱ� ������ �񱳺Ұ��ϹǷ� ���� ù��° list���� �����͸� �ִ´�
		if (m_Length == 0) {
			m_Array[0] = inData;
			++m_Length;
		}
		//����Ʈ�� �Ѱ��� �����Ͱ� �����Ұ�� �� �Ѱ����͸� ���ϸ� �ǹǷ� ũ�� �������� compareById �Լ��� ����� Ŭ�� ��ġ�� ����, ���� �� �ι�° ����Ʈĭ�� �׷��� �����͸� ���Խ�Ų��
		else if (m_Length == 1) {
			//������ ������ id���� m_Array��ü�� ���� ù��° ������ id������ �۴ٸ� ���� ù��° ����Ʈ���� ���ο� ���ڵ带 �ְ� Ŭ�� �� �ڿ� �̾� �ִ´�
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
		//����Ʈ�� 2���̻��� �����Ͱ� �̹� �����ϰų� �������� �ʴٸ� ������ �����Ͱ� �����ϴ� ������ ���̿� ����, ���� ó������ ����, ���������� ���� ID���� CompareByID�Լ��� ���� ���� �ִ´� 
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
	m_CurPointer++;	// list pointer ����
	if (m_CurPointer == MAXSIZE)	// end of list�̸� -1�� ����
		return -1;
	data = m_Array[m_CurPointer];	// ���� list pointer�� ���ڵ带 ����

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
	//�ӽ� ItemType ��ü����
	ItemType temp;
	//���� ��ü�� list�� �������� �ʴٸ� �Ʒ��� ���� for������
	if (GetLength() != 0) {
		for (int i = 0; i < GetLength(); ++i) {
			//����Ʈ �ȿ� ����ִ� ������ ���ڵ��� id���� ã���� �ϴ� id���� ��ġ����Ȯ��
			if (m_Array[i].GetId() == data.GetId()) {
				//��ġ�ϴ� ���ڵ� ����Ʈ�� ����� �� ���� ������ �����͵��� ����Ʈ���� ��ĭ�� ������ ��ܿ´�
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

	/*���� �޾ƿ� ItemType ��ü�� ���̵� ����, BinarySearch�� �ʿ��� ���۰� �߰��� ����, 
	�� 3���� ��ġ�� �ִ� ItemType ��ü�� ������ ID���� ��Ÿ���� ������ ���� �������ش�*/
	int id = data.GetId();
	int start, end, middle, startLoc, endLoc, middleLoc;
	
	startLoc = 0;
	endLoc = GetLength() - 1;
	middleLoc = endLoc / 2;

	start = m_Array[startLoc].GetId();
	end = m_Array[endLoc].GetId();
	middle = m_Array[middleLoc].GetId();

	//bool ���·� found ������ ������ search�� ���� ã�� �� true�� ������ش�
	bool found = false;

	//found bool�� true�� �ɶ����� BinarySearch�� �����ϴ� while��
	while (found) {
		//���̵� ������� �ٷ� ���ٸ� found�� true�ǰ� loop�� ��������
		if (id == middle) {
			data = m_Array[middle];
			found = true;
			break;
		}
		// id ���� ���� middle���� Ŭ�� middle ���� ���� ��ġ�� ������ ������ä�� ������ �ٿ���
		else if (id > middle) {
			startLoc = middleLoc + 1;
			middleLoc = (startLoc + endLoc) / 2;
			//���������� ����, �߰�, ���� ��ġ�� ������ �˻��Ͽ� ã���� ������ ���ϹǷ� data������ �ش� m_array��ġ�� �����͸� �־���
			if (startLoc == middleLoc == endLoc) {
				data = m_Array[startLoc];
				found = true;
				break;
			}
			// ���� ��ġ�� ������ ��ġ���� Ŀ�������� list ���� ��ü�� �a�� ���������� ��ġ�ϴ� ID���� ���ܰ��� �������� �ٷ� 0�� return
			else if (startLoc > endLoc)
				return 0;
		}
		// id ���� ���� middle���� ������ middle ���� ū ��ġ�� ������ ������ä�� ������ �ٿ���
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
	//found�� true�Ͻ� 1, false ���� �� 0 ��ȯ
	if (found == true)
		return 1;
	else
		return 0;
}