#include "SortedListClass.h"


//Default Constructor. Will properly initialize a list to
//be an empty list, to which values can be added.
template<class T>
SortedListClass<T>::SortedListClass() {
    head = NULL;
    tail = NULL;
}

//Copy constructor. Will make a complete (deep) copy of the list, such
//that one can be changed without affecting the other.
template<class T>
SortedListClass<T>::SortedListClass(
        const SortedListClass<T> &rhs) {
    head = NULL;
    tail = NULL;
    //build a new node that is equal to rhs–>head
    //start from head of rhs and use while loop to insert value
    LinkedNodeClass<T> *tempNode;
    tempNode = rhs.head;
    while (tempNode != NULL) {
        insertValue(tempNode->getValue());
        tempNode = tempNode->getNext();
    }

}

//Destructor. Responsible for making sure any dynamic memory
//associated with an object is freed up when the object is
//being destroyed.
template<class T>
SortedListClass<T>::~SortedListClass() {
    clear();
}

//Clears the list to an empty state without resulting in any
//memory leaks.
template<class T>
void SortedListClass<T>::clear() {
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

//Allows the user to insert a value into the list. Since this
//is a sorted list, there is no need to specify where in the list
//to insert the element. It will insert it in the appropriate
//location based on the value being inserted. If the node value
//being inserted is found to be "equal to" one or more node values
//already in the list, the newly inserted node will be placed AFTER
//the previously inserted nodes.
template<class T>
void SortedListClass<T>::insertValue(
        const T &valToInsert // The value to insert into the list
) {
    // Represents the temporary node for insertion in conditions 2 and 3,
    // as well as the temporary node for the loop in condition 4
    LinkedNodeClass<T> *tempNode;

    // Condition 1: The current sorted list is empty
    if (head == NULL && tail == NULL) {
        head = new LinkedNodeClass<T>(NULL, valToInsert, NULL);
        tail = head;
    }
        // Condition 2: valToInsert is less than the head node value
    else if (head->getValue() > valToInsert) {
        tempNode = new LinkedNodeClass<T>(NULL, valToInsert, head);
        tempNode->setBeforeAndAfterPointers();
        head = tempNode;
    }
        // Condition 3:
        // valToInsert is greater than or equal to the tail node value
    else if (tail->getValue() <= valToInsert) {
        tempNode = new LinkedNodeClass<T>(tail, valToInsert, NULL);
        tempNode->setBeforeAndAfterPointers();
        tail = tempNode;
    }
        // Condition 4: valToInsert should be inserted into the middle
    else {
        // Find the location of valToInsert
        bool findLocation = false;
        tempNode = head;
        while (!findLocation) {
            if (
                    valToInsert >= tempNode->getValue() &&
                    tempNode->getNext() != NULL &&
                    valToInsert < tempNode->getNext()->getValue()
                    ) {
                // The next node is not null,
                // meaning there is a value >= valToInsert
                // Found the location of valToInsert
                findLocation = true;
                // Represents the node to be inserted
                LinkedNodeClass<T> *inNode;
                inNode = new LinkedNodeClass<T>(tempNode, valToInsert,
                                                tempNode->getNext());
                inNode->setBeforeAndAfterPointers();
            }
            tempNode = tempNode->getNext();
        }
    }
}


//Prints the contents of the list from head to tail to the screen.
//Begins with a line reading "Forward List Contents Follow:", then
//prints one list element per line, indented two spaces, then prints
//the line "End Of List Contents" to indicate the end of the list.
template<class T>
void SortedListClass<T>::printForward() const {
    cout << "Forward List Contents Follow:" << endl;
    //represent the node for while loop
    LinkedNodeClass<T> *tempNode;
    tempNode = head;
    while (tempNode != NULL) {
        cout << "  " << tempNode->getValue() << endl;
        tempNode = tempNode->getNext();
    }
    cout << "End Of List Contents" << endl;
}

//Prints the contents of the list from tail to head to the screen.
//Begins with a line reading "Backward List Contents Follow:", then
//prints one list element per line, indented two spaces, then prints
//the line "End Of List Contents" to indicate the end of the list.
template<class T>
void SortedListClass<T>::printBackward() const {
    cout << "Backward List Contents Follow:" << endl;
    //represent the node for while loop
    LinkedNodeClass<T> *tempNode;
    tempNode = tail;
    while (tempNode != NULL) {
        cout << "  " << tempNode->getValue() << endl;
        tempNode = tempNode->getPrev();
    }
    cout << "End Of List Contents" << endl;
}

//Removes the front item from the list and returns the value that
//was contained in it via the reference parameter. If the list
//was empty, the function returns false to indicate failure, and
//the contents of the reference parameter upon return is undefined.
//If the list was not empty and the first item was successfully
//removed, true is returned, and the reference parameter will
//be set to the item that was removed.
template<class T>
bool SortedListClass<T>::removeFront(T &theVal) {
    //if the sortedlist is null
    if (head == NULL) {
        return false;
    }
        //if the sortedlist has only one node
        //it is different with the third condition
    else if (head->getNext() == NULL) {
        LinkedNodeClass<T> *temp;
        temp = head;
        theVal = temp->getValue();
        delete temp;
        tail = NULL;
        head = NULL;
        temp = NULL;
        return true;
    } else {
        theVal = head->getValue();
        head = head->getNext();
        delete head->getPrev();
        head->setPreviousPointerToNull();
        return true;
    }
}

//Removes the last item from the list and returns the value that
//was contained in it via the reference parameter. If the list
//was empty, the function returns false to indicate failure, and
//the contents of the reference parameter upon return is undefined.
//If the list was not empty and the last item was successfully
//removed, true is returned, and the reference parameter will
//be set to the item that was removed.
template<class T>
bool SortedListClass<T>::removeLast(T &theVal) {
    if (head == NULL) {
        return false;
    } else if (head->getNext() == NULL) {
        LinkedNodeClass<T> *temp;
        temp = tail;
        theVal = temp->getValue();
        delete temp;
        tail = NULL;
        head = NULL;
        temp = NULL;
        return true;
    } else {
        theVal = tail->getValue();
        tail = tail->getPrev();
        delete tail->getNext();
        tail->setNextPointerToNull();
        return true;
    }
}

//Returns the number of nodes contained in the list.
template<class T>
int SortedListClass<T>::getNumElems() const {
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

//Provides the value stored in the node at index provided in the
//0-based "index" parameter. If the index is out of range, then outVal
//remains unchanged and false is returned. Otherwise, the function
//returns true, and the reference parameter outVal will contain
//a copy of the value at that location.
template<class T>
bool SortedListClass<T>::getElemAtIndex(const int index, int &outVal) const {
    //check if the index is valid
    if (index >= 0 && index < getNumElems()) {
        int count = 0;
        LinkedNodeClass<T> *tempNode;
        tempNode = head;
        while (index != count) {
            count++;
            tempNode = tempNode->getNext();
        }
        outVal = tempNode->getValue();
        return true;
    } else {
        return false;
    }
}

