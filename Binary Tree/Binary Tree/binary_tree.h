/*********************************************************************************

  * FileName:       binary_tree.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class BinaryTree
  * Project:        The Data Structures - Binary Tree
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include "bin_node.h"


template<typename T> class BinaryTree
{
protected:
	// The size of the binary tree
	int size_;
	// Points to the root node of the binary tree
	BinNode<T>* root_;

	/*
	* Updates the height of the node x
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The new height of the node x
	*/
	int UpdateHeight(BinNode<T>* x);

	/*
	* Updates the height of the node x and its ancestors
	* @ Parameter:
	*       x:         The node x
	*/
	void UpdateHeightAbove(BinNode<T>* x);

	/*
	* Removes the node x and its successors
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The number of removed nodes
	*/
	int RemoveAt(BinNode<T>* x);

	/*
	* Gets the pointer from the node bn's mother node that points to the node bn
	* @ Parameter:
	*       bn:        The node bn
	* @ Return:
	*                  The pointer from the node bn's mother node that points to the node bn
	*/
	BinNode<T>*& FromParentTo(const BinNode<T>& bn);

public:
	BinaryTree();
	~BinaryTree();

	/*
	* Gets the size of the binary tree
	* @ Return:
	*                  The size of the binary tree
	*/
	int GetSize() const;

	/*
	* Whether the binary tree is empty
	* @ Return:
	*                  Whether the binary tree is empty
	*/
	bool IsEmpty() const;

	/*
	* Gets the root node
	* @ Return:
	*                  Points to the root node
	*/
	BinNode<T>* GetRoot() const;

	/*
	* Inserts the node as root node
	* @ Parameter:
	*       e:         The value of the node
	* @ Return:
	*                  Points to the inserted node
	*/
	BinNode<T>* InsertAsRoot(const T& e);

	/*
	* Inserts the node as the left child of the node x
	* @ Parameter:
	*       x:         The node x
	*       e:         The value of the node
	* @ Return:
	*                  Points to the inserted node
	*/
	BinNode<T>* InsertAsLC(BinNode<T>* x, const T& e);

	/*
	* Inserts the node as the right child of the node x
	* @ Parameter:
	*       x:         The node x
	*       e:         The value of the node
	* @ Return:
	*                  Points to the inserted node
	*/
	BinNode<T>* InsertAsRC(BinNode<T>* x, const T& e);

	/*
	* Attaches the binary tree bt as the left child tree of the node x
	* @ Parameter:
	*       x:         The node x
	*       bt:        The binary tree
	* @ Return:
	*                  Points to the node x
	*/
	BinNode<T>* AttachAsLC(BinNode<T>* x, BinaryTree<T>*& bt);

	/*
	* Attaches the binary tree bt as the right child tree of the node x
	* @ Parameter:
	*       x:         The node x
	*       bt:        The binary tree
	* @ Return:
	*                  Points to the node x
	*/
	BinNode<T>* AttachAsRC(BinNode<T>* x, BinaryTree<T>*& bt);

	/*
	* Removes the binary tree whose root node is node x
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The size of the removed binary tree
	*/
	int Remove(BinNode<T>* x);

	/*
	* Removes the binary tree whose root node is node x, and transforms it as a independent binary tree
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The new binary tree
	*/
	BinaryTree<T>* Secede(BinNode<T>* x);

	/*
	* Level order traversal algorithm
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void TraverseLevel(VST& visit);

	/*
	* Preorder traversal algorithm
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void TraversePre(VST& visit);

	/*
	* Inorder traversal algorithm
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void TraverseIn(VST& visit);

	/*
	* Postorder traversal algorithm
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void TraversePost(VST& visit);
};


template<typename T> int BinaryTree<T>::UpdateHeight(BinNode<T>* x)
{
	int max = (BinNode<T>::GetStature(x->lc_) > BinNode<T>::GetStature(x->rc_) ? BinNode<T>::GetStature(x->lc_) : BinNode<T>::GetStature(x->rc_));
	return x->height_ = 1 + max;
}


template<typename T> void BinaryTree<T>::UpdateHeightAbove(BinNode<T>* x)
{
	while (x != nullptr)
	{
		UpdateHeight(x);
		x = x->parent_;
	}
}


template<typename T> int BinaryTree<T>::RemoveAt(BinNode<T>* x)
{
	if (x == nullptr)
		return 0;

	int count = 1 + RemoveAt(x->lc_) + RemoveAt(x->rc_);
	//release(x->data);
	//release(x);
	delete x;
	x = nullptr;
	return count;
}


template<typename T> BinNode<T>*& BinaryTree<T>::FromParentTo(const BinNode<T>& bn)
{
	return (BinNode<T>::IsRoot(bn) == true) ? root_ : ((BinNode<T>::IsLChild(bn) == true) ? (bn.parent_)->lc_ : (bn.parent_)->rc_);
}


template<typename T> BinaryTree<T>::BinaryTree(): size_(0), root_(nullptr)
{
}


template<typename T> BinaryTree<T>::~BinaryTree()
{
	if (GetSize() > 0)
		Remove(root_);
}


template<typename T> int BinaryTree<T>::GetSize() const
{
	return size_;
}


template<typename T> bool BinaryTree<T>::IsEmpty() const
{
	return !static_cast<bool>(GetSize());
}


template<typename T> BinNode<T>* BinaryTree<T>::GetRoot() const
{
	return root_;
}


template<typename T> BinNode<T>* BinaryTree<T>::InsertAsRoot(const T& e)
{
	size_ = 1;
	return root_ = new BinNode<T>(e);
}


template<typename T> BinNode<T>* BinaryTree<T>::InsertAsLC(BinNode<T>* x, const T& e)
{
	size_++;
	x->InsertAsLC(e);
	UpdateHeightAbove(x);
	return x->lc_;
}


template<typename T> BinNode<T>* BinaryTree<T>::InsertAsRC(BinNode<T>* x, const T& e)
{
	size_++;
	x->InsertAsRC(e);
	UpdateHeightAbove(x);
	return x->rc_;
}


template<typename T> BinNode<T>* BinaryTree<T>::AttachAsLC(BinNode<T>* x, BinaryTree<T>*& bt)
{
	x->lc_ = bt->GetRoot();

	if (x->lc_ != nullptr)
		x->lc_->parent_ = x;

	size_ += bt->GetSize();
	UpdateHeightAbove(x);

	bt->root_ = nullptr;
	bt->size_ = 0;
	//release(bt);
	bt = nullptr;
	return x;
}


template<typename T> BinNode<T>* BinaryTree<T>::AttachAsRC(BinNode<T>* x, BinaryTree<T>*& bt)
{
	x->rc_ = bt->GetRoot();

	if (x->rc_ != nullptr)
		x->rc_->parent_ = x;

	size_ += bt->GetSize();
	UpdateHeightAbove(x);

	bt->root_ = nullptr;
	bt->size_ = 0;
	//release(bt);
	bt = nullptr;
	return x;
}


template<typename T> int BinaryTree<T>::Remove(BinNode<T>* x)
{
	FromParentTo(*x) = nullptr;
	UpdateHeightAbove(x->parent_);
	int count = RemoveAt(x);
	size_ -= count;
	return count;
}


template<typename T> BinaryTree<T>* BinaryTree<T>::Secede(BinNode<T>* x)
{
	FromParentTo(*x) = nullptr;
	UpdateHeightAbove(x->parent_);

	BinaryTree<T>* bt = new BinaryTree<T>();
	bt->root_ = x;
	x->parent_ = nullptr;
	bt->size_ = x->GetSize();
	size_ -= bt->GetSize();

	return bt;
}


template<typename T> template<typename VST> void BinaryTree<T>::TraverseLevel(VST& visit)
{
	if (GetRoot() != nullptr)
		root_->TraverseLevel(visit);
}


template<typename T> template<typename VST> void BinaryTree<T>::TraversePre(VST& visit)
{
	if (GetRoot() != nullptr)
		root_->TraversePre(visit);
}


template<typename T> template<typename VST> void BinaryTree<T>::TraverseIn(VST& visit)
{
	if (GetRoot() != nullptr)
		root_->TraverseIn(visit);
}


template<typename T> template<typename VST> void BinaryTree<T>::TraversePost(VST& visit)
{
	if (GetRoot() != nullptr)
		root_->TraversePost(visit);
}


