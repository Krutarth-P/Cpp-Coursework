/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
#include "DBentry.h"
#include "TreeNode.h"

// A useful constructor

TreeNode::TreeNode(DBentry* _entryPtr) {
    entryPtr = _entryPtr;
    left = nullptr;
    right = nullptr;
}

// the destructor

TreeNode::~TreeNode() {
    delete entryPtr;
    entryPtr = nullptr;
    left = nullptr;
    right = nullptr;
}

// sets the left child of the TreeNode.

void TreeNode::setLeft(TreeNode* newLeft) {
    left = newLeft;
}

// sets the right child of the TreeNode

void TreeNode::setRight(TreeNode* newRight) {
    right = newRight;
}

// gets the left child of the TreeNode.

TreeNode* TreeNode::getLeft() const {
    return left;
}

// gets the right child of the TreeNode

TreeNode* TreeNode::getRight() const {
    return right;
}

// returns a pointer to the DBentry the TreeNode contains. 

DBentry* TreeNode::getEntry() const {
    return entryPtr;
}

