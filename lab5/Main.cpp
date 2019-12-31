/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Krutarth Patel
 *
 * Created on November 22, 2019, 8:23 PM
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "DBentry.h"
#include "TreeNode.h"
#include "TreeDB.h"

using namespace std;

void insert(stringstream &, TreeDB&);
void find(stringstream &, TreeDB&);
void remove(stringstream &, TreeDB&);
void printall(TreeDB&);
void printprobes(stringstream &, TreeDB&);
void removeall(TreeDB&);
void countactive(TreeDB&);
void updatestatus(stringstream&, TreeDB&);

int main(int argc, char** argv) {
    TreeDB root;
    string line;
    string command;

    cout << "> ";
    getline(cin, line);

    while (!cin.eof()) {

        stringstream lineStream(line);

        lineStream >> command;

        if (command == "insert") {
            insert(lineStream, root);
        } else if (command == "find") {
            find(lineStream, root);
        } else if (command == "remove") {
            remove(lineStream, root);
        } else if (command == "printall") {
            printall(root);
        } else if (command == "printprobes") {
            printprobes(lineStream, root);
        } else if (command == "removeall") {
            removeall(root);
        } else if (command == "countactive") {
            countactive(root);
        } else if (command == "updatestatus") {
            updatestatus(lineStream, root);
        }

        cout << "> ";
        getline(cin, line);

    }
    root.clear();
    return 0;
}

/*This  command  creates  a  new  entry  with name(a string) as
 the key and IPaddress(a non-negative integer) 
 and status(active or inactive)*/
void insert(stringstream & line, TreeDB& tree) {
    string name, IPaddress, status;
    bool active;
    int num = 0;

    line >> name;
    line >> IPaddress;
    line >> status;

    stringstream convert(IPaddress);
    convert>>num;

    if (status == "active")active = true;
    else active = false;

    DBentry* add = new DBentry(name, num, active);

    if ((tree.insert(add)))cout << "Success" << endl;
    else {
        cout << "Error: entry already exists" << endl;
        delete add;
    }
    add = nullptr;

}

/*This command finds the entry with the key name in the database, 
 and prints its contents to cout as name : IPaddress : status*/
void find(stringstream & line, TreeDB& tree) {

    string name;

    line>>name;

    if ((tree.find(name)) == nullptr)cout << "Error: entry does not exist" << endl;
    else {
        cout << *(tree.find(name)) << endl;
    }
}

//this command deletes the entry with the key name from the database

void remove(stringstream & line, TreeDB& tree) {
    string name;

    line>> name;

    if (tree.remove(name))cout << "Success" << endl;
    else cout << "Error: entry does not exist" << endl;

}

/*This command prints all the entries in the database, sorted 
 in ascending order of keys, one entry per line.*/
void printall(TreeDB& tree) {
    cout << tree;
}


//the number of probes (DBentries examined during the tree search) is printed

void printprobes(stringstream & line, TreeDB& tree) {
    string name;

    line>>name;

    if (tree.find(name) == nullptr) cout << "Error: entry does not exist" << endl;
    else tree.printProbes();
}

//This  command  deletes  all  the  entries  in  the  database,  returning  it  to  the empty state

void removeall(TreeDB& tree) {
    tree.clear();
    cout << "Success" << endl;
}


//This command counts the number of entries in the database that are active and prints this count

void countactive(TreeDB& tree) {
    tree.countActive();
}

//This  command  updates  the  status  of  the  entry  with the  given  name

void updatestatus(stringstream & line, TreeDB& tree) {
    string name, status;
    line>>name;
    line>>status;

    bool active;


    if (status == "active")active = true;
    else active = false;

    if ((tree.find(name)) == nullptr)cout << "Error: entry does not exist" << endl;
    else {
        cout << "Success" << endl;
        (tree.find(name))->setActive(active);
    }

}

