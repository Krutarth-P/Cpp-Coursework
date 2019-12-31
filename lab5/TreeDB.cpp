/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
#include "DBentry.h"
#include "TreeNode.h"
#include "TreeDB.h"

// the default constructor, creates an empty database.

TreeDB::TreeDB() {
    root = nullptr;
    probesCount = 0;
}

// the destructor, deletes all the entries in the database.

TreeDB::~TreeDB() {
    clear();
}

//private function to insert a string and return pointer to the added TreeNode

TreeNode* TreeDB::insertNode(TreeNode* ptr, DBentry* newEntry) {
    if (root == nullptr) {
        root = new TreeNode(newEntry);
        return root;
    }
    if ((ptr->getEntry()->getName().compare(newEntry->getName())) > 0) {
        if (ptr->getLeft() == nullptr) {
            ptr->setLeft(new TreeNode(newEntry));
            return ptr;
        } else insertNode(ptr->getLeft(), newEntry);
    }
    if ((ptr->getEntry()->getName().compare(newEntry->getName())) < 0) {
        if (ptr->getRight() == nullptr) {
            ptr->setRight(new TreeNode(newEntry));
            return ptr;
        } else insertNode(ptr->getRight(), newEntry);
    }
}


// inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.

bool TreeDB::insert(DBentry* newEntry) {
    if (find(newEntry->getName()) != nullptr)return false; //name already in database
    else {//if name not in database
        insertNode(root, newEntry);
        return true;
    }

}


//private function to search for a string and return pointer to TreeNode

TreeNode* TreeDB::search(TreeNode* ptr, string name) {
    probesCount++;
    if (ptr == nullptr) return nullptr;
    else if ((ptr->getEntry()->getName().compare(name)) == 0) {

        return ptr; //if name is found

    } else if ((ptr->getEntry()->getName().compare(name)) < 0) {

        return search(ptr->getRight(), name);

    } else {

        return search(ptr->getLeft(), name);

    }
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount

DBentry* TreeDB::find(string name) {
    if ((search(root, name)) != nullptr) {
        probesCount = 0;
        return (search(root, name))->getEntry(); //if name found

    } else return nullptr; //if name not found
}


//function to get the node before name

TreeNode* TreeDB::nodeBefore(TreeNode* ptr, string name, TreeNode*& pptr) {
    if (ptr == nullptr) return nullptr; //if empty tree
    else if ((ptr->getEntry()->getName().compare(name)) == 0) {
        return pptr; //if name is found
    } else if ((ptr->getEntry()->getName().compare(name)) < 0) {
        pptr = ptr;
        return nodeBefore(ptr->getRight(), name, pptr);
    } else {
        pptr = ptr;
        return nodeBefore(ptr->getLeft(), name, pptr);
    }

}

//helper function to find the pointer to the max node in the left tree

TreeNode* TreeDB::maxLeft(TreeNode* ptr) {
    if (ptr->getRight() == nullptr)return ptr;
    else return maxLeft(ptr->getRight());
}


// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.

bool TreeDB::remove(string name) {
    TreeNode* toDelete = search(root, name);
    TreeNode* prev = nullptr;
    nodeBefore(root, name, prev);


    //if(prev==nullptr && toDelete==root)prev&=root;//root is to be deleted

    if (toDelete == nullptr)return false;
    else {
        if (toDelete->getLeft() == nullptr && toDelete->getRight() == nullptr) {//no left or right children(leaf node)
            if (toDelete == root) {//if root to be deleted
                delete toDelete;
                toDelete = nullptr;

                root = nullptr;
                return true;
            }
            if (prev->getRight() == toDelete) {
                prev->setRight(nullptr);
                delete toDelete;
                toDelete = nullptr;
                prev = nullptr;

                return true;
            } else {
                prev->setLeft(nullptr);
                delete toDelete;
                toDelete = nullptr;
                prev = nullptr;

                return true;
            }
        } else if (toDelete->getLeft() == nullptr) {//left empty
            if (toDelete == root) {//if root to be deleted
                root = toDelete->getRight();
                delete toDelete;
                toDelete = nullptr;
                prev = nullptr;

                return true;
            } else {
                if (prev->getRight() == toDelete) {
                    prev->setRight(toDelete->getRight());
                    delete toDelete;
                    toDelete = nullptr;
                    prev = nullptr;

                    return true;
                } else {
                    prev->setLeft(toDelete->getRight());
                    delete toDelete;
                    toDelete = nullptr;
                    prev = nullptr;

                    return true;
                }
            }
        } else if (toDelete->getRight() == nullptr) {//right empty

            if (toDelete == root) {//if root to be deleted
                root = toDelete->getLeft();
                delete toDelete;
                toDelete = nullptr;
                prev = nullptr;

                return true;
            } else {
                if (prev->getRight() == toDelete) {
                    prev->setRight(toDelete->getLeft());
                    delete toDelete;
                    toDelete = nullptr;
                    prev = nullptr;

                    return true;
                } else {
                    prev->setLeft(toDelete->getLeft());
                    delete toDelete;
                    toDelete = nullptr;
                    prev = nullptr;

                    return true;
                }
            }
        } else if (toDelete->getLeft() != nullptr && toDelete->getRight() != nullptr) {//two sub-trees

            TreeNode* prevMax = nullptr; //previous ptr to the max node on the left tree
            TreeNode* max = nullptr; //ptr to the max node on the on the left tree
            max = maxLeft(toDelete->getLeft());
            nodeBefore(root, max->getEntry()->getName(), prevMax);

            if (toDelete == root) {//if root to be deleted

                if (toDelete->getLeft() == max) {//if max direct children of root
                    root = max;
                    max->setRight(toDelete->getRight());

                    delete toDelete;
                    toDelete = nullptr;

                    return true;
                } else {
                    max->setLeft(root->getLeft());
                    max->setRight(root->getRight());
                    root = max;
                    delete toDelete;
                    toDelete = nullptr;

                    prevMax->setRight(nullptr);

                    return true;
                }
            } else {
                if (toDelete->getLeft() == max) {//if max direct children of toDelete
                    max->setRight(toDelete->getRight());

                    if (prev->getLeft() == toDelete)prev->setLeft(max);
                    else if (prev->getRight() == toDelete) prev->setRight(max);

                    delete toDelete;
                    toDelete = nullptr;

                    return true;
                } else {
                    max->setLeft(toDelete->getLeft());
                    max->setRight(toDelete->getRight());

                    if (prev->getLeft() == toDelete)prev->setLeft(max);
                    else if (prev->getRight() == toDelete) prev->setRight(max);

                    delete toDelete;
                    toDelete = nullptr;

                    prevMax->setRight(nullptr);

                    return true;
                }
            }

        }

    }
}

//helper function for deleting nodes

void TreeDB::delete_tree(TreeNode* ptr) {
    if (ptr == nullptr)return;

    delete_tree(ptr->getLeft());


    delete_tree(ptr->getRight());

    delete ptr;
}



//helper function to count active entries

void TreeDB::count(TreeNode* ptr, int& num)const {
    if (ptr != nullptr) {
        if (ptr->getEntry()->getActive() == true)num++;
        count(ptr->getLeft(), num);
        count(ptr->getRight(), num);
    }
}


// deletes all the entries in the database.

void TreeDB::clear() {
    if (root == nullptr)return;
    else {
        delete_tree(root);
    }
    root = nullptr;
}

// prints the number of probes stored in probesCount

void TreeDB::printProbes() const {
    cout << probesCount << endl;
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).

void TreeDB::countActive() const {
    int activeNUM = 0;
    count(root, activeNUM);
    cout << activeNUM << endl;
}
//helper function to print the whole tree

void print(TreeNode* ptr) {
    if (ptr != nullptr) {
        print(ptr->getLeft());
        cout << *(ptr->getEntry()) << endl;
        print(ptr->getRight());
    }
}

// Prints the entire tree, in ascending order of key/name (in-order traversal LNR)

ostream& operator<<(ostream& out, const TreeDB& rhs) {
    print(rhs.root);
    return (out);

}