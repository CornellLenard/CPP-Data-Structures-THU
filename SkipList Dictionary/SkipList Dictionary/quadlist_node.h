/*********************************************************************************

  * FileName:       quadlist_node.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class QuadListNode
  * Project:        The Data Structures - SkipList Dictionary
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include "entry.h"


template<typename K, typename V> class QuadListNode
{
public:
	// Stores the entry
	Entry<K, V> entry_;
	// Points to the predecessor node
	QuadListNode<K, V>* pred_;
	// Points to the successor node
	QuadListNode<K, V>* succ_;
	// Points to the above node
	QuadListNode<K, V>* above_;
	// Points to the below node
	QuadListNode<K, V>* below_;

	QuadListNode(K k, V v = static_cast<V>(0), QuadListNode<K, V>* p = nullptr, QuadListNode<K, V>* s = nullptr, QuadListNode<K, V>* a = nullptr, QuadListNode<K, V>* b = nullptr);
	
	/*
	* Inserts a new node, its pred is the current node, its below is the node b
	* @ Parameter:
	*       k:         The key
	*       v:         The value
	*       b:         The node b
	* @ Return:
	*                  Points to the inserted node
	*/
	QuadListNode<K, V>* InsertAsSuccAbove(const K& k, const V& v, QuadListNode<K, V>* b = nullptr);
};


template<typename K, typename V> QuadListNode<K, V>::QuadListNode(K k, V v, QuadListNode<K, V>* p, QuadListNode<K, V>* s, QuadListNode<K, V>* a, QuadListNode<K, V>* b):
	entry_(k, v), pred_(p), succ_(s), above_(a), below_(b)
{
}


template<typename K, typename V> QuadListNode<K, V>* QuadListNode<K, V>::InsertAsSuccAbove(const K& k, const V& v, QuadListNode<K, V>* b)
{
	QuadListNode<K, V>* x = new QuadListNode<K, V>(k, v, this, succ_, nullptr, b);
	succ_->pred_ = x;
	succ_ = x;

	if (b != nullptr)
		b->above_ = x;

	return x;
}


