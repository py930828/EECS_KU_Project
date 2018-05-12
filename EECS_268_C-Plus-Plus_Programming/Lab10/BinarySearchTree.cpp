//  Subsetted from:
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file BinarySearchTree.cpp */
#include <iostream>
#include "BinarySearchTree.h"
// PRIVATE HELPER METHODS - IMPLEMENT THESE
template<typename ItemType, typename KeyType>
BinarySearchTree<ItemType, KeyType>::BinarySearchTree() : rootPtr(nullptr)
{
}

template<typename ItemType, typename KeyType>
BinarySearchTree<ItemType, KeyType>::~BinarySearchTree()
{
	if(rootPtr!=nullptr)
	{
		destroyTree(rootPtr); // Call inherited method
	}
	cout<<"out of des???"<<endl;
}  // end destructor

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::destroyTree(BinaryNode<ItemType>* subTreePtr)
{
	if(subTreePtr!=nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		cout<<"delete: "<<subTreePtr->getItem().getword()<<endl;
		delete subTreePtr;
		subTreePtr=nullptr;
	}
	else
	{
		return;
	}
	/*
	if(subTreePtr==nullptr)
	{
		return;
	}
	if(subTreePtr->getLeftChildPtr()!=nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
	}
	if(subTreePtr->getRightChildPtr()!=nullptr)
	{
		destroyTree(subTreePtr->getRightChildPtr());
	}
	cout<<subTreePtr->getItem().getword()<<endl;
	delete subTreePtr;
	subTreePtr=nullptr;*/
}

template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType,KeyType>::insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNode)
{
	BinaryNode<ItemType>* ptr=nullptr;
	if(subTreePtr==nullptr)
	{
		return newNode;
	}
	if(newNode->getItem() > subTreePtr->getItem())
	{
		ptr=insertInorder(subTreePtr->getRightChildPtr(), newNode);
		subTreePtr->setRightChildPtr(ptr);
	}
	else
	{
		ptr=insertInorder(subTreePtr->getLeftChildPtr(), newNode);
		subTreePtr->setLeftChildPtr(ptr);
	}
	return subTreePtr;
}

template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType, KeyType>::findNode(BinaryNode<ItemType>* subTreePtr, const KeyType& target) const
{
	if(subTreePtr==nullptr)
	{
		cout<<"return nullptr\n";
		return subTreePtr;
	}
	cout<<subTreePtr->getItem().getword()<<endl;

	if(subTreePtr->getItem()==target)
	{
		cout<<"yeah! Found!!!"<<endl;
		return subTreePtr;
	}
	else if(subTreePtr->getItem()<target)
	{
		return findNode(subTreePtr->getRightChildPtr(), target);
	}
	else
	{
		return findNode(subTreePtr->getLeftChildPtr(), target);
	}
}

template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType, KeyType>::removeNode(BinaryNode<ItemType>* subTreeptr)
{
	cout<<subTreeptr->getItem().getword()<<endl;
	if(subTreeptr->isLeaf())
	{
		delete subTreeptr;
		subTreeptr=nullptr;
		return nullptr;
	}
	else if(subTreeptr->getLeftChildPtr()!=nullptr&&subTreeptr->getRightChildPtr()==nullptr)
	{
		BinaryNode<ItemType>* Node1=subTreeptr->getLeftChildPtr();
		delete subTreeptr;
		subTreeptr=nullptr;
		return Node1;
	}
	else if(subTreeptr->getLeftChildPtr()==nullptr&&subTreeptr->getRightChildPtr()!=nullptr)
	{
		BinaryNode<ItemType>* Node1=subTreeptr->getRightChildPtr();
		delete subTreeptr;
		subTreeptr=nullptr;
		return Node1;
	}
	else
	{
		DictionaryEntry de;
		de=(Leftmost(subTreeptr->getRightChildPtr())->getItem());
		removeNode(Leftmost(subTreeptr->getRightChildPtr()));
		subTreeptr->setItem(de);
		return subTreeptr;
	}
}

template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType, KeyType>::Leftmost(BinaryNode<ItemType>* subTreeptr)
{
	if(subTreeptr->getLeftChildPtr()==nullptr)
	{
		return subTreeptr;
	}
	else
	{
		return Leftmost(subTreeptr->getLeftChildPtr());
	}

}
//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////
template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType,KeyType>::getrootPtr()
{
	return rootPtr;
}

template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType,KeyType>::getPtr(const KeyType& aKey) const
{
	cout<<"go to getPtr???"<<endl;
	return findNode(rootPtr,aKey);
}
//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section - IMPLEMENT THESE
//////////////////////////////////////////////////////////////

template<typename ItemType, typename KeyType>
bool BinarySearchTree<ItemType, KeyType>::add(const ItemType& newEntry)
{
	BinaryNode<ItemType>* ptr=new BinaryNode<ItemType>(newEntry);
	rootPtr=insertInorder(rootPtr, ptr);
	return false;
}

template<typename ItemType, typename KeyType>
ItemType BinarySearchTree<ItemType, KeyType>::getEntry(const KeyType& aKey) const throw(NotFoundException)
{
	return findNode()->getItem();
}

template<typename ItemType, typename KeyType>
bool BinarySearchTree<ItemType, KeyType>::contains(const KeyType& aKey) const
{
	cout<<"in contains???";
	if(findNode(rootPtr, aKey)==nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}


//////////////////////////////////////////////////////////////
//      Public Traversals Section - IMPLEMENT THESE
//////////////////////////////////////////////////////////////

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::inorderTraverse(void visit(ItemType&)) const
{
	inorder(visit, rootPtr);
}

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::preorderTraverse(void visit(ItemType&)) const
{
	preorder(visit, rootPtr);
}

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::postorderTraverse(void visit(ItemType&)) const
{
	postorder(visit, rootPtr);
}


template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::inorder(void visit(ItemType&),BinaryNode<ItemType>* subTreeptr) const
{
	if(subTreeptr!=nullptr)
	{
		inorder(visit,subTreeptr->getLeftChildPtr());
		ItemType theItem=subTreeptr->getItem();
		visit(theItem);
		inorder(visit,subTreeptr->getRightChildPtr());
	}
}

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::postorder(void visit(ItemType&),BinaryNode<ItemType>* subTreeptr) const
{
	if(subTreeptr!=nullptr)
	{
		postorder(visit,subTreeptr->getLeftChildPtr());
		postorder(visit,subTreeptr->getRightChildPtr());
		ItemType theItem=subTreeptr->getItem();
		visit(theItem);
	}
}

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::preorder(void visit(ItemType&),BinaryNode<ItemType>* subTreeptr) const
{
	if(subTreeptr!=nullptr)
	{
		ItemType theItem=subTreeptr->getItem();
		visit(theItem);
		preorder(visit,subTreeptr->getLeftChildPtr());
		preorder(visit,subTreeptr->getRightChildPtr());
	}
}
