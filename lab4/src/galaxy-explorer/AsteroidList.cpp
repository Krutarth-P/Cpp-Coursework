#include <galaxy-explorer/AsteroidList.hpp>

//default constructor
AsteroidListItem::AsteroidListItem() {
    this->next = nullptr;
    this->data = nullptr;
}

//constructor
AsteroidListItem::AsteroidListItem(Asteroid a) {
    this->next = nullptr;
    this->data = new Asteroid(a.getID(), a.getMass(), a.getHealth(), a.getCurrentHitbox(), a.getVelocity());
}

//destructor
AsteroidListItem::~AsteroidListItem() {
    this->next = nullptr;
    delete data;
    this->data = nullptr;

}

//default constructor
AsteroidList::AsteroidList() {
    head.setNext(nullptr);
}

//copy constructor
AsteroidList::AsteroidList(const AsteroidList& src) {

    const AsteroidListItem* SRCptr = ((src.head).getNext());
    AsteroidListItem* NEWprevious = nullptr;
    AsteroidListItem* NEWptr = nullptr;
    head.setNext(nullptr);

    while (SRCptr != nullptr) {//loop till pointer reaches the end of src list
        NEWptr = new AsteroidListItem(SRCptr->getData()); //generate copy and assign to new caller list
        if (NEWprevious == nullptr) head.setNext(NEWptr);
        else NEWprevious->setNext(NEWptr);
        SRCptr = SRCptr->getNext();
        NEWprevious = NEWptr;
    }

}

//destructor
AsteroidList::~AsteroidList() {
    AsteroidListItem* ptr;

    while (head.hasNext()) {//loop till pointer reaches end of list
        ptr = head.getNext();
        head.setNext(ptr->getNext());

        delete ptr;
    }
    ptr = nullptr;
}


//Add an asteroid at the beginning of this list
void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem* ptr = new AsteroidListItem(e);
    ptr->setNext(head.getNext());
    head.setNext(ptr);
    ptr = nullptr;
}

/**
 * Return a reference to the first asteroid
 * This function may have ANY BEHAVIOUR if this list is empty
 */
Asteroid& AsteroidList::front() {
    if (head.hasNext()) return (head.getNext())->getData();

    return *(Asteroid*) nullptr;
}

const Asteroid& AsteroidList::front() const {
    if (head.hasNext()) return (head.getNext())->getData();

    return *(const Asteroid*) nullptr;
}


//returns if there are entities in this list or not
bool AsteroidList::isEmpty() const {
    if ((head.hasNext())) return false;
    else return true;
}

//returns the number of entities in this list
int AsteroidList::size() const {
    const AsteroidListItem* ptr = head.getNext();
    int size = 0;
    while (ptr != nullptr) {
        size++;
        ptr = ptr->getNext();
    }
    return size;
}

/**
 * Return an item corresponding to the position immediately before the first asteroid.
 * If this list is empty, a value equal to `beforeEnd()` must be returned.
 * If this list is in a valid state, this function must always succeed.
 */
AsteroidListItem* AsteroidList::beforeBegin() {
    return &head;//return pointer to head
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
    return &head;//return pointer to head
}

/**
 * Return an item corresponding to the first asteroid.
 * If this list is empty, a value equal to `end()` must be returned.
 * If this list is in a valid state, this function must always succeed.
 */
AsteroidListItem* AsteroidList::begin() {
    return head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
    return head.getNext();
}

/**
 * Return an item corresponding to the position of the last asteroid.
 * If this list is empty, a value equal to `beforeBegin()` must be returned.
 * If this list is in a valid state, this function must always succeed.
 */
AsteroidListItem* AsteroidList::beforeEnd() {
    AsteroidListItem* ptr = &head;
    while (ptr->hasNext()) {
        ptr = ptr->getNext();
    }
    return ptr;
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    const AsteroidListItem* ptr = &head;
    while (ptr->hasNext()) {
        ptr = ptr->getNext();
    }

    return ptr;
}

/**
 * Return an item corresponding to the position immediately after the last asteroid.
 * If this list is empty, a value equal to `begin()` must be returned.
 * If this list is in a valid state, this function must always succeed.
 */
AsteroidListItem* AsteroidList::end() {
    return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
    return nullptr;
}

/**
 * Add a single asteroid to this list, in the position immediately after `prev`.
 * returns the item that was inserted
 */
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    AsteroidListItem* ptr = new AsteroidListItem(e);
    ptr->setNext(prev->getNext());
    prev->setNext(ptr);

    return prev->getNext();
}

/**
 * Add independent copies of the entities in `others` to this list, placed immediately after `insertion_point`,
 * in the same order as `others`.
 * Returns the last item that was inserted, or `insertion_point' if `others' is empty.
 */
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    if ((others.head).getNext() == nullptr) {
        return prev;
    }

    AsteroidListItem* pptr = prev->getNext(); //next pointer of prev
    const AsteroidListItem* ptr = (others.head).getNext();
    while (ptr != nullptr) {
        prev->setNext(new AsteroidListItem(ptr->getData()));

        ptr = ptr->getNext();

        prev = prev->getNext();

    }
    prev->setNext(pptr);

    return prev;

}

/**
 * Given a position in this list, delete the following asteroid.
 * Returns the list item that followed the erased item, or end() if there wasn't one.
 * This function may have ANY BEHAVIOUR if there is no asteroid after `prev`.
 */
AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    AsteroidListItem* ptr = (prev->getNext())->getNext();

    delete prev->getNext();

    prev->setNext(ptr);

    ptr = nullptr;

    return prev->getNext();
}

/**
 * Make this list empty, free all nodes.
 */
void AsteroidList::clear() {
    AsteroidListItem* ptr;

    while (head.hasNext()) {
        ptr = head.getNext();
        head.setNext(ptr->getNext());

        //delete &(ptr->getData());
        delete ptr;
    }
    ptr = nullptr;
}

/**
* Makes this list an independent copy of `src`. This means that there is NO shared data or pointers.
*/
AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    if (this == &src) return (*this);

    clear();

    const AsteroidListItem* SRCptr = ((src.head).getNext()); //copy data from source using copy constructor
    AsteroidListItem* NEWprevious = nullptr;
    AsteroidListItem* NEWptr = nullptr;
    head.setNext(nullptr);

    while (SRCptr != nullptr) {
        NEWptr = new AsteroidListItem(SRCptr->getData());
        if (NEWprevious == nullptr) head.setNext(NEWptr);
        else NEWprevious->setNext(NEWptr);
        SRCptr = SRCptr->getNext();
        NEWprevious = NEWptr;
    }

    return (*this);
}
