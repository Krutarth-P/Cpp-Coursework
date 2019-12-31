/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */

#include <iostream>
#include <galaxy-explorer/AsteroidsObserver.hpp>

/**
 * Called whenever a new asteroid appears on the field
 */
void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    asteroid_list.insertAfter(asteroid_list.beforeEnd(), asteroid);
}

/**
 * Called when an asteroid has moved.
 * Use the ID of the asteroid to determine what asteroid to replace
 */
void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
   AsteroidListItem* ptr = (asteroid_list.begin());
    
    if (ptr != nullptr && (ptr->getData()).getID() == asteroid.getID()) {
        //AsteroidListItem* tptr = ptr;

        asteroid_list.beforeBegin()->setNext(new AsteroidListItem(asteroid));
        
        asteroid_list.begin()->setNext(ptr->getNext());
        
        delete ptr;
        ptr = nullptr;
    return;

    }

    while ((ptr->getNext()->getData()).getID() != asteroid.getID()) {
        ptr = ptr->getNext();
    }
   
    
    asteroid_list.eraseAfter(ptr);
    
    asteroid_list.insertAfter(ptr, asteroid);
    
}

/**
 * Called when an asteroid leaves the field without being destroyed
 */
void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
   AsteroidListItem* ptr = (asteroid_list.begin());

    if (ptr != nullptr && (ptr->getData()).getID() == asteroid.getID()){ //if ID == the first asteroid
              
        asteroid_list.beforeBegin()->setNext(ptr->getNext());

        delete ptr;
        ptr = nullptr;
    
    return;
    }

    while ((ptr->getNext()->getData()).getID() != asteroid.getID()) {
        ptr = ptr->getNext();
    }

    asteroid_list.eraseAfter(ptr);

}

/**
 * Called when an asteroid is destroyed by a phaser shot
 */
void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    AsteroidListItem* ptr = (asteroid_list.begin());

    if (ptr != nullptr && (ptr->getData()).getID() == asteroid.getID()) {//if ID == the first asteroid
             
        asteroid_list.beforeBegin()->setNext(ptr->getNext());

        delete ptr;
        ptr = nullptr;
    
    return;
    
    }

    while ((ptr->getNext()->getData()).getID() != asteroid.getID()) {
        ptr = ptr->getNext();
    }

    asteroid_list.eraseAfter(ptr);
}
