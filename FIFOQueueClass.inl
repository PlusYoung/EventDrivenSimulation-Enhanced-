#include "FIFOQueueClass.h"

//Default Constructor. Will properly initialize a queue to
//be an empty queue, to which values can be added.
template<class T>
FIFOQueueClass<T>::FIFOQueueClass() {
    head = NULL;
    tail = NULL;
}

//Destructor. Responsible for making sure any dynamic memory
//associated with an object is freed up when the object is
//being destroyed.
template<class T>
FIFOQueueClass<T>::~FIFOQueueClass() {
    clear();
}

//Inserts the value provided (newItem) into the queue.
template<class T>
void FIFOQueueClass<T>::enqueue(
        const T &newItem
) {
    LinkedNodeClass<T> *insertNode;
    //check if the queue is empty
    if (head == NULL) {
        insertNode = new LinkedNodeClass<T>(NULL, newItem, NULL);
        head = insertNode;
        tail = insertNode;
    } else {
        insertNode = new LinkedNodeClass<T>(tail, newItem, NULL);
        insertNode->setBeforeAndAfterPointers();
        tail = insertNode;
    }
}

//Attempts to take the next item out of the queue. If the
//queue is empty, the function returns false and the state
//of the reference parameter (outItem) is undefined. If the
//queue is not empty, the function returns true and outItem
//becomes a copy of the next item in the queue, which is
//removed from the data structure.
template<class T>
bool FIFOQueueClass<T>::dequeue(
        T &outItem
) {
    //check if the queue is empty
    if (head == NULL) {
        return false;
    } else if (head->getNext() == NULL) {
        LinkedNodeClass<T> *temp;
        temp = head;
        outItem = temp->getValue();
        delete temp;
        tail = NULL;
        head = NULL;
        temp = NULL;
        return true;
    } else {
        outItem = head->getValue();
        head = head->getNext();
        delete head->getPrev();
        head->setPreviousPointerToNull();
        return true;
    }
}

//Prints out the contents of the queue. All printing is done
//on one line, using a single space to separate values, and a
//single newline character is printed at the end.
template<class T>
void FIFOQueueClass<T>::print() const {
    //represent the node for while loop
    LinkedNodeClass<T> *tempNode;
    tempNode = head;
    while (tempNode != NULL) {
        cout << tempNode->getValue() << " ";
        tempNode = tempNode->getNext();
    }
    cout << endl;
}

//Returns the number of nodes contained in the queue.
template<class T>
int FIFOQueueClass<T>::getNumElems() const {
    //initialize the count number as 0
    int count = 0;
    //represent the node for counting in loop
    LinkedNodeClass<T> *countPtr;
    countPtr = head;
    while (countPtr != NULL) {
        count++;
        countPtr = countPtr->getNext();
    }
    return count;
}

//Clears the queue to an empty state without resulting in any
//memory leaks.
template<class T>
void FIFOQueueClass<T>::clear() {
    //represent the node to be deleted
    LinkedNodeClass<T> *deleteNode;
    //represent the node for while loop
    LinkedNodeClass<T> *tempNode;
    deleteNode = head;
    tempNode = head;
    while (tempNode != NULL) {
        tempNode = tempNode->getNext();
        delete deleteNode;
        deleteNode = tempNode;
    }
    tail = NULL;
    head = NULL;
}