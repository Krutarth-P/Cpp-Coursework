//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here


bool validName(string&); //checks if the name is a reserved word
bool nameExists(string&); //checks if name already exists in database
bool nameNotFound(string&); //checks if name is not found in the database
bool invalidType(string&); //checks if the shape is valid type
bool invalidValue(int); ///checks if value is valid
bool invalidAngleValue(int); ///checks if value is valid

int main() {

    string line;
    string command;

    cout << "> "; // Prompt for input
    getline(cin, line); // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream(line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if (command == "maxShapes") {//gets the size of the shape database(max_shapes)
            lineStream >> max_shapes;
            cout << "New database: max shapes is " << max_shapes << endl;
            shapesArray = new shape*[max_shapes];
            command.clear();
        } else { // if not initial command
            if (command == keyWordsList[2] || command == keyWordsList[3] || command == keyWordsList[4] || command == keyWordsList[5] || command == keyWordsList[6]) { //checks which command is input

                if (command == keyWordsList[2]) { //if command==create
                    if ((!lineStream.eof())) {//eof is not reached

                        if (shapeCount < max_shapes) {//check if array is full
                            string name, type, next;
                            int xLoc, yLoc, xSiz, ySiz;

                            lineStream>>name; //gets name
                            if (!(lineStream.eof())) {//eof is not reached
                                if (validName(name)) {//checks if name is valid
                                    if (!nameExists(name)) {//checks if name already exists
                                        lineStream>>type; //assign type
                                        if (!invalidType(type)) {//checks for valid type
                                            lineStream>>xLoc; //assigns Xlocation
                                            if (!(lineStream.fail())) {//if not fail
                                                if (!(invalidValue(xLoc))) {//checks for valid value
                                                    lineStream>>yLoc; //assigns Yloc
                                                    if (!(lineStream.fail())) {//if not fail
                                                        if (!(invalidValue(yLoc))) {//checks for valid value

                                                            lineStream>>xSiz; //assigns Xsize
                                                            if (!(lineStream.fail())) {//if not fail
                                                                if (!invalidValue(xSiz)) {//checks for valid size
                                                                    lineStream>>ySiz; //assigns Ysize
                                                                    if (!(lineStream.fail())) {//if not fail
                                                                        if (!invalidValue(ySiz)) {//checks for valid size
                                                                            if (lineStream.eof()) {//check for too many arguments
                                                                                shapesArray[shapeCount] = new shape(name, type, xLoc, yLoc, xSiz, ySiz); //creates new object
                                                                                shapeCount++; //increments shape count 
                                                                                cout << "Created " << name << ": " << type << " " << xLoc << " " << yLoc << " " << xSiz << " " << ySiz << endl;
                                                                            } else {//if not eof
                                                                                cout << "Error: too many arguments" << endl;
                                                                            }
                                                                        } else {//if not valid ySize value
                                                                            cout << "Error: invalid value" << endl;
                                                                        }
                                                                    } else {//if fail flag
                                                                        if (!(lineStream.eof())) {//eof is not reached
                                                                            cout << "Error: invalid argument" << endl;
                                                                        } else {
                                                                            cout << "Error: too few arguments" << endl;
                                                                        }
                                                                    }
                                                                } else {//if Xsiz not valid
                                                                    cout << "Error: invalid value" << endl;
                                                                }
                                                            } else {//if fail flag
                                                                if (!(lineStream.eof())) {//eof is not reached
                                                                    cout << "Error: invalid argument" << endl;
                                                                } else {
                                                                    cout << "Error: too few arguments" << endl;
                                                                }
                                                            }
                                                        } else {//if invalid Yloc
                                                            cout << "Error: invalid value" << endl;
                                                        }
                                                    } else {//if fail flag
                                                        if (!(lineStream.eof())) {//eof is not reached
                                                            cout << "Error: invalid argument" << endl;
                                                        } else {
                                                            cout << "Error: too few arguments" << endl;
                                                        }
                                                    }
                                                } else {//if invalid xLoc
                                                    cout << "Error: invalid value" << endl;
                                                }
                                            } else {//if fail flag
                                                if (!(lineStream.eof())) {//eof is not reached
                                                    cout << "Error: invalid argument" << endl;
                                                } else {
                                                    cout << "Error: too few arguments" << endl;
                                                }
                                            }

                                        } else {//if shape type invalid
                                            cout << "Error: invalid shape type" << endl;
                                        }
                                    } else {//if shape name exists
                                        cout << "Error: shape " << name << " exists" << endl;
                                    }
                                } else {
                                    cout << "Error: invalid shape name" << endl;
                                }
                            } else {//if eof
                                if (!validName(name)) {
                                    cout << "Error: invalid shape name" << endl;
                                } else if (nameExists(name)) {
                                    cout << "Error: shape " << name << " exists" << endl;
                                } else {
                                    cout << "Error: too few arguments" << endl;
                                }
                            }

                        } else {//if array full
                            cout << "Error: shape array is full" << endl;
                        }
                    } else {//if eof
                        cout << "Error: too few arguments" << endl;

                    }
                } else if (command == keyWordsList[3]) { //if command==move
                    if (!(lineStream.eof())) {//eof is not reached
                        string name;
                        int xLoc, yLoc;
                        lineStream>>name;
                        if (!(lineStream.eof())) {//eof is not reached
                            if (validName(name)) {
                                if (!nameNotFound(name)) {
                                    lineStream>>xLoc;
                                    if (!(lineStream.fail())) {//if not fail
                                        if ((!invalidValue(xLoc))) {//checks for valid value
                                            lineStream>>yLoc;
                                            if (!(lineStream.fail())) {//if not fail
                                                if ((!invalidValue(yLoc))) {
                                                    if (lineStream.eof()) {//check for too many arguments
                                                        for (int i = 0; i < shapeCount; i++) {
                                                            if ((shapesArray[i])->getName() == name) {//if name matches

                                                                shapesArray[i]->setXlocation(xLoc); //move
                                                                shapesArray[i]->setYlocation(yLoc); //move

                                                                cout << "Moved " << name << " to " << xLoc << " " << yLoc << endl;
                                                            }
                                                        }
                                                    } else {//if not eof
                                                        cout << "Error: too many arguments" << endl;
                                                    }
                                                } else {//if invalid yLoc
                                                    cout << "Error: invalid value" << endl;
                                                }
                                            } else {//if fail flag
                                                if (!(lineStream.eof())) {//eof is not reached
                                                    cout << "Error: invalid argument" << endl;
                                                } else {
                                                    cout << "Error: too few arguments" << endl;
                                                }
                                            }
                                        } else {//if invalid xLoc
                                            cout << "Error: invalid value" << endl;
                                        }

                                    } else {//if fail
                                        if (!(lineStream.eof())) {//eof is not reached
                                            cout << "Error: invalid argument" << endl;
                                        } else {
                                            cout << "Error: too few arguments" << endl;
                                        }
                                    }
                                } else {//if name not found
                                    cout << "Error: shape " << name << " not found" << endl;
                                }
                            } else {//if invalid shape name
                                cout << "Error: invalid shape name" << endl;
                            }
                        } else {//if eof
                            if (!validName(name)) {
                                cout << "Error: invalid shape name" << endl;
                            } else if (nameNotFound(name)) {
                                cout << "Error: shape " << name << " not found" << endl;
                            } else {
                                cout << "Error: too few arguments" << endl;
                            }

                        }
                    } else {//if eof
                        {
                            cout << "Error: too few arguments" << endl;
                        }

                    }
                } else if (command == keyWordsList[4]) { //if command==rotate
                    if (!(lineStream.eof())) {//eof is not reached
                        string name, rotate = "rotate";
                        int angle;

                        lineStream>>name;
                        if (!(lineStream.eof())) {//eof is not reached
                            if (validName(name)) {
                                if (!nameNotFound(name)) {

                                    lineStream>>angle;
                                    if (!(lineStream.fail())) {//if not fail

                                        if ((!invalidAngleValue(angle))) {//check for invalid angle
                                            if ((lineStream.eof())) {//check for too many arguments
                                                for (int i = 0; i < shapeCount; i++) {
                                                    if ((shapesArray[i])->getName() == name) {

                                                        shapesArray[i]->setRotate(angle);

                                                        cout << "Rotated " << name << " by " << angle << " degrees" << endl;
                                                    }
                                                }
                                            } else {//if not eof
                                                cout << "Error: too many arguments" << endl;
                                            }
                                        } else {//if invalid angle value
                                            cout << "Error: invalid value" << endl;
                                        }

                                    } else {//if fail
                                        if (!(lineStream.eof())) {//eof is not reached
                                            cout << "Error: invalid argument" << endl;
                                        } else {
                                            cout << "Error: too few arguments" << endl;
                                        }
                                    }
                                } else {//name not found
                                    cout << "Error: shape " << name << " not found" << endl;
                                }
                            } else {//invalid name
                                cout << "Error: invalid shape name" << endl;
                            }
                        } else {//if eof
                            if (!validName(name)) {
                                cout << "Error: invalid shape name" << endl;
                            } else if (nameNotFound(name)) {
                                cout << "Error: shape " << name << " not found" << endl;
                            } else {
                                cout << "Error: too few arguments" << endl;
                            }

                        }
                    } else {//if eof
                        if (lineStream >> ws)
                            cout << "Error: too few arguments" << endl;
                    }

                } else if (command == keyWordsList[5]) { //if command==draw
                    if (!(lineStream.eof())) {//eof is not reached
                        string name;
                        lineStream>>name;
                        if ((lineStream.eof())) {//eof is reached
                            if (name == "all") {//draw all
                                cout << "Drew all shapes" << endl;
                                for (int i = 0; i < shapeCount; i++) {
                                    shapesArray[i]->draw();
                                }
                            } else if (validName(name)) {//draw shape
                                if (!nameNotFound(name)) {//if name found
                                    cout << "Drew " << name << endl;
                                    for (int i = 0; i < shapeCount; i++) {
                                        if ((shapesArray[i])->getName() == name) {
                                            shapesArray[i]->draw();
                                        }
                                    }
                                } else {//shape not found
                                    cout << "Error: shape " << name << " not found" << endl;
                                }
                            } else {//invalid name
                                cout << "Error: invalid shape name" << endl;
                            }
                        } else {//if not eof
                            if (!validName(name)) {
                                cout << "Error: invalid shape name" << endl;
                            } else if (nameNotFound(name)) {
                                cout << "Error: shape " << name << " not found" << endl;
                            } else {
                                cout << "Error: too many arguments" << endl;
                            }
                        }
                    } else {//if eof
                        if (lineStream >> ws) {
                            cout << "Error: too few arguments" << endl;
                        }
                    }
                } else if (command == keyWordsList[6]) { //if command==delete
                    if (!lineStream.eof()) {//eof is not reached
                        string name;
                        lineStream>>name;
                        if ((lineStream.eof())) {//eof is reached
                            if (name == "all") {//delete all
                                cout << "Deleted: all shapes" << endl;
                                for (int i = 0; i < shapeCount; i++) {
                                    delete shapesArray[i];
                                    shapesArray[i] = NULL; //sets null after delete
                                }
                                shapeCount = 0; //reset shape count after delete all
                            } else if (validName(name)) {//if valid name
                                if (!nameNotFound(name)) {//if name found
                                    cout << "Deleted shape " << name << endl;
                                    for (int i = 0; i < shapeCount; i++) {
                                        if ((shapesArray[i])->getName() == name) {
                                            delete shapesArray[i];
                                            shapesArray[i] = NULL; //sets null after delete

                                        }
                                    }

                                } else {//if name not found
                                    cout << "Error: shape " << name << " not found" << endl;
                                }
                            } else {//if invalid name
                                cout << "Error: invalid shape name" << endl;
                            }
                        } else {//if not eof
                            if (name == "all") {
                                cout << "Error: too many arguments" << endl;
                            } else if (!validName(name)) {
                                cout << "Error: invalid shape name" << endl;
                            } else if (nameNotFound(name)) {
                                cout << "Error: shape " << name << " not found" << endl;
                            } else {
                                cout << "Error: too many arguments" << endl;
                            }
                        }
                    } else {//if eof
                        if (lineStream >> ws)
                            cout << "Error: too few arguments" << endl;
                    }
                }
            } else {//if inlaid command
                cout << "Error: invalid command" << endl;
            }
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> "; // Prompt for input
        getline(cin, line); // Get the command line

    } // End input loop until EOF.

    return 0;
}

bool validName(string & name) {//checks for valid name
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (name == keyWordsList[i]) {

            return false;
        }
    }
    return true;
}

bool nameExists(string & name) {//checks for existing name
    for (int i = 0; i < shapeCount; i++) {
        if ((shapesArray[i])->getName() == name) {

            return true;
        }
    }
    return false;
}

bool nameNotFound(string & name) {//checks if name is not found in the database
    for (int i = 0; i < shapeCount; i++) {
        if (shapesArray[i]->getName() == name) {

            return false;
        }
    }
    return true;
}

bool invalidType(string & name) {//checks if type is valid
    for (int i = 0; i < NUM_TYPES; i++) {
        if (shapeTypesList[i] == name) {

            return false;
        }
    }
    return true;
}

bool invalidValue(int num) {//checks if value is valid
    if (num < 0) {
        return true;
    }
    return false;
}

bool invalidAngleValue(int num) {//checks if angle is valid
    if (!(num >= 0 && num <= 360)) {
        return true;
    }
    return false;
}