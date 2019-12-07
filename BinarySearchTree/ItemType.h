
#ifndef _ITEMTYPE_H
#define _ITEMTYPE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/**
*	Relation between two items.
*/
enum RelationType { LESS, GREATER, EQUAL };


/**
*	item information class.
*/
class ItemType
{
public:
	/**
	*	default constructor.
	*/
	ItemType()
	{
		m_Id = -1;
		m_sName = "";
		m_sAddress = "";
	}

	/**
	*	destructor.
	*/
	~ItemType() {}

	
	int GetId()
	{
		return m_Id;
	}

	
	string GetName()
	{
		return m_sName;
	}

	
	string GetAddress()
	{
		return m_sAddress;
	}

	
	void SetId(int inId)
	{
		m_Id = inId;
	}

	
	void SetName(string inName)
	{
		m_sName = inName;
	}

	
	void SetAddress(string inAddress)
	{
		m_sAddress = inAddress;
	}

	
	void SetRecord(int inId, string inName, string inAddress)
	{
		SetId(inId);
		SetName(inName);
		SetAddress(inAddress);
	}

	
	void DisplayIdOnScreen()
	{
		cout << "\tID   : " << m_Id << endl;
	};

	
	void DisplayNameOnScreen()
	{
		cout << "\tName : " << m_sName << endl;
	};

	
	void DisplayAddressOnScreen()
	{
		cout << "\tAddress : " << m_sAddress << endl;
	};

	
	void DisplayRecordOnScreen()
	{
		DisplayIdOnScreen();
		DisplayNameOnScreen();
		DisplayAddressOnScreen();
	};

	
	void SetIdFromKB();

	
	void SetNameFromKB();

	
	void SetAddressFromKB();

	
	void SetRecordFromKB();

	
	int ReadDataFromFile(ifstream& fin);

	
	int WriteDataToFile(ofstream& fout);


	
	ostream& operator<<(ostream& cout);
	bool operator >(const ItemType& data);
	bool operator <(const ItemType& data);
	bool operator ==(const ItemType& data);
	bool operator !=(const ItemType& data);
	void operator =(const ItemType& data);
protected:
	int m_Id;			
	string m_sName;		
	string m_sAddress;	
};

#endif	// _ITEMTYPE_H
