#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include "ItemType.h"
using namespace std;

template <typename T>
struct BinaryTreeNode
{
	T data; // node data
	BinaryTreeNode *left; // left node pointer
	BinaryTreeNode *right; // right node pointer
};


template<typename T> void MakeEmptyTree(BinaryTreeNode<T> *&root) {
	if (root != nullptr){
		MakeEmptyTree(root->left);
		MakeEmptyTree(root->right);
		delete root;
	}
}


template<typename T> int CountNodes(BinaryTreeNode<T> *root) {
	if (root == nullptr)
		return 0;
	else
		return CountNodes(root->left) + CountNodes(root->right) + 1;
}


template<typename T> void Insert(BinaryTreeNode<T> *&root, T item) {
	if (root == nullptr){ // INSERT item HERE AS LEAF
		root = new BinaryTreeNode<T>;
		root->right = nullptr;
		root->left = nullptr;
		root->data = item;
	}
	else if (item < root->data) // GO LEFT
		Insert(root->left, item);
	else if (item > root->data) // GO RIGHT
		Insert(root->right, item);
}


template<typename T> void GetPredecessor(BinaryTreeNode<T> *root, T& item) {
	if (root != nullptr) {
		if (item == root->data)
			item = root->data
		if (root->right->data != nullptr && root->left->data != nullptr) {
			if (item == root->right->data || item == root->left->data)
				item = root->data;
			else {
				GetPredecessor(root->left, item);
				GetPredecessor(root->right, item);
			}
		}
		else if (root->right->data == nullptr && root->left->data != nullptr) {
			if (item == root->left->data)
				item = root->data;
			else {
				GetPredecessor(root->left, item);
			}
		}
		else {
			if (item == root->right->data)
				item = root->data;
			else {
				GetPredecessor(root->right, item);
			}
		}
	}

	if (item > root->data || item == root->data ) {
		while (root->right != item)
			root = root->right;
		item = root->data;
	}

	else {
		while (root->left != item)
			root = root->left;
		item = root->data;
	}
}


template<typename T> void Delete(BinaryTreeNode<T> *&root, T item) {

	if (item < root->data)
		Delete(root->left, item); // Look in left subtree.
	else if (item > tree->data)
		Delete(root->right, item); // Look in right subtree.
	else
		DeleteNode(root); // Node found; call DeleteNode.

}


template<typename T> void DeleteNode(BinaryTreeNode<T> *&root) {
	T item;
	BinaryTreeNode<T>* tempPtr;
	tempPtr = root;
	if (root->left == nullptr)
	{
		root = root->right;
		delete tempPtr;
	}
	else if (root->right == nullptr)
	{
		root = root->left;
		delete tempPtr;
	}
	else
	{
		GetPredecessor(root->left, item);
		root->data = item;
		Delete(root->left, item); //Delete predecessor node.
	}
}


template<typename T> void Retrieve(BinaryTreeNode<T> *root, T& item, bool &found) {
	if (root == nullptr)
		found = false;
	else if (item < root->data) // GO LEFT
		Retrieve(root->left, item, found);
	else if (item > root->data) // GO RIGHT
		Retrieve(root->right, item, found);
	else{
		item = root->data;
		found = true;
	}
}


template<typename T> void PrintInOrderTraversal(BinaryTreeNode<T> *root, ostream &out) {
	if (root != nullptr){
		PrintInOrderTraversal(root->left, out); // Print left subtree
		out << root->data;
		PrintInOrderTraversal(root->right, out); // Print right subtree
	}
}


template<typename T> void PrintPreOrderTraversal(BinaryTreeNode<T> *root, ostream &out) {
	if (root != nullptr)
	{
		T rootData = *root;
		T currentData;
		while (root->left->data != nullptr)
			root = root->left;
		while (root->data != rootData) {
			GetPredecessor(root, currentData);
			out << root->data;
		}
		PrintPreOrderTraversal(root->left, out);// Print left subtree
		PrintPreOrderTraversal(root->right, out); // Print right subtree
	}
}


template<typename T> void PrintPostOrderTraversal(BinaryTreeNode<T> *root, ostream &out) {
	if (root != nullptr)
	{
		out << root->data;
		PrintPostOrderTraversal(root->left, out); // Print left subtree
		out << root->data;
		PrintPostOrderTraversal(root->right, out); // Print right subtree
	}
}

template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() {
		root = nullptr;
	};// constructor
	~BinarySearchTree() {
		MakeEmptyTree(root);
	} // destructor


	bool IsEmpty() const {
		return root == nullptr;
	} // check tree is empty


	bool IsFull() const {
		BinaryTreeNode* location;
		try {
			location= new BinaryTreeNode;
			delete location;
			return false;
		}
		catch (std::bad_alloc exception) {
			return true;
		}
	} // check tree is full


	void MakeEmpty() {
		MakeEmptyTree(this->root);
	}// make empty tree


	int GetLength() const {
		CountNodes(root);
	} // get number of current node


	void Add(T item) {
		if (root == nullptr)
		{ // INSERT item HERE AS LEAF
			root = new BinarySearchTree<T>;
			root->right = nullptr;
			root->left = nullptr;
			root->data = item;
		}
		else if (item < root->data) // GO LEFT
			Insert(root->left, item);
		else if (item > root->data) // GO RIGHT
			Insert(root->right, item);
	} // add item to tree


	void Delete(T item) {
		if (item < tree->data)
			Delete(tree->left, item); // Look in left subtree.
		else if (item > tree->data)
			Delete(tree->right, item); // Look in right subtree.
		else
			DeleteNode(tree); // Node found; call DeleteNode.
	} // delete item from tree


	void Retrieve(T &item, bool &found) const {
		if (root == nullptr)
			found = false;
		else if (item < root->data) // GO LEFT
			Retrieve(root->left, item, found);
		else if (item > root->data) // GO RIGHT
			Retrieve(root->right, item, found);
		else{
			item = root->data;
			found = true;
		}
	} // retrieve item in tree


	void PrintTree(ostream &out) const {
		PrintInOrderTraversal(root, out);
	}// display all item in tree, InOrder, PreOrder, PostOrder

private:
	BinaryTreeNode<T> *root;
};