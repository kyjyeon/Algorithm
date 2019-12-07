#pragma once
#include "BinarySearchTree.h"
class Application
{
public:
	Application();
	void run();
	int GetCommand();
	int AddItem();
	int DeleteItem();
	void DisplayItem();
	int SearchItem();
	~Application();
private:
	BinarySearchTree<ItemType> tree;
};