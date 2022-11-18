/*
CCC121 Laboratory Exercise No. 1
Due: November 20, 2022 (Sunday) at 11:55PM
*/

#include <assert.h>
#include <iostream>

using namespace std;

/*
The structure to be used for representing a doubly-linked link. This struct
declaration should not be modified in any way.
*/
template <class E> struct DLink {
  E theElement;
  DLink<E> *nextPtr;
  DLink<E> *prevPtr;
};

/*
Complete this implementation variant of the doubly-linked list. Use the same
convention as described in the slides. The DLink declaration to be used here is
just a struct and should not be modified in any way. All of the operations of
the original DLink class must be done in the methods of this class. Use
assertions to ensure the correct operation of this ADT. All memory allocations
should be checked with assertions and all discarded memory must be properly
deallocated.
*/
template <class E> class DList {
  DLink<E> *head;
  DLink<E> *tail;
  DLink<E> *curr;
  int cnt; // number of DLinks between head and tail

public:
  // Return the size of the list
  int length() const { return cnt; }

  // The constructor with initial list size
  DList(int size) { this(); }

  // The default constructor
  DList() {

    // Initialize the list with allocating a new empty list
    head = curr = new DLink<E>;
    tail = new DLink<E>;

    // precaution to avoid memory distortion
    assert(head != NULL && tail != NULL);

    head->prevPtr = nullptr;
    head->nextPtr = tail;
    tail->prevPtr = head;
    tail->nextPtr = nullptr;
    cnt = 0;
    //
    // ??? - implement this method
    //
  }

  // The copy constructor
  DList(const DList &source) {
    //
    // ??? - implement this method
    //
  }

  // The class destructor
  ~DList() {
    //
    // ??? - implement this method
    //
  }

  // Empty the list
  void clear() {

    if(cnt > 0) {
      curr = head->nextPtr;
      while (curr != tail) {
          DLink<E> *temp = curr->nextPtr;
          delete curr;
          curr  = temp;
        }
        curr = head;
        head->nextPtr = tail;
        tail->prevPtr = head;
        cnt = 0;
    }
    //
    // ??? - implement this method
    //
  }

  // Set current to first element
  void moveToStart() {
    if (head->nextPtr != tail) {
      curr = head;
      // curr = head->nextPtr;
    }
    //
    // ??? - implement this method
    //
  }

  // Set current element to end of list
  void moveToEnd() {
    if (tail->prevPtr != head) {
      curr = tail->prevPtr;

      // fail because of assertion when using below this method
      // curr = tail->prevPtr;
    }
    //
    // ??? - implement this method
    //
  }

  // Advance current to the next element
  void next() {
    if (curr->nextPtr != tail) {
      curr = curr->nextPtr;
    }
    //
    // ??? - implement this method
    //
  }

 // HEAD | 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - TAIL

  // Return the current element
  E &getValue() const {
    // assert(curr != head && curr != tail);
    // return curr->theElement;
    return curr->nextPtr->theElement;
    //
    // ??? - implement this method
    //
  }

  // Insert value at current position
  void insert(const E &it) {

    DLink<E> *temp = new DLink<E>;
    assert(temp != NULL);

    temp->nextPtr = curr->nextPtr;
    temp->prevPtr = curr;
    curr->nextPtr = curr->nextPtr->prevPtr = temp;

    temp->theElement = it;

    cnt++;  
    //
    // ??? - implement this method
    //
  }

  // HEAD - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - TAIL
  // HEAD - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - TAIL

  // Append value at the end of the list
  void append(const E &it) {

    DLink<E> *newLink = new DLink<E>;
    assert(newLink != NULL);

    newLink->nextPtr = tail;
    newLink->prevPtr = tail->prevPtr;
    newLink->theElement = it;

    tail->prevPtr->nextPtr = newLink;
    tail->prevPtr = newLink;


    cnt++;

    

    
    /* tail->nextPtr = new DLink<E>;
    assert(tail->nextPtr != NULL);
    tail->nextPtr->prevPtr = tail;
    tail->theElement = it;
    tail = tail->nextPtr;
    tail->nextPtr = nullptr;
    cnt++; */

    //
    // ??? - implement this method
    //
  }

  // Remove and return the current element
  E remove() {

    if(curr->nextPtr == tail) return '\0';

    E it = curr->nextPtr->theElement;

    DLink<E> *temp = curr->nextPtr;
    curr->nextPtr->nextPtr->prevPtr = curr;
    curr->nextPtr = curr->nextPtr->nextPtr;
    delete temp;

    cnt--;
    return it;
    //
    // ??? - implement this method
    //
  }

  // Advance current to the previous element
  void prev() {

    if(cnt > 0 && (curr->prevPtr != head || curr != head)) {
      curr = curr->prevPtr;
    } 
    //
    // ??? - implement this method
    //
  }

  // Return position of the current element
  int currPos() const {

    assert(curr != NULL && cnt > 0);
    int num;
    DLink<E> *temp = head;
    for(num = 0; temp != curr; num++) {
      temp = temp->nextPtr;
    }

    return num;
    //
    // ??? - implement this method
    //
  }

  // Set current to the element at the given position
  void moveToPos(int pos) {
    if (0 <= cnt && 0 <= pos && pos <= cnt){
      curr = head;
      for (int i = 0; i < pos; i++) {
        curr  = curr->nextPtr;
      }
    }
    //
    // ??? - implement this method
    //
  }
};

/*
This is the main function for testing the implementation of the DList class.
This function can be freely modified.
*/
int main(void) {
  int i;
  DList<int> theList;

  // populate the list
  for (i = 0; i < 10; ++i) {
    theList.append(i);
  }
  while (i < 20)
  {
      theList.insert(i);

      ++i;
  }

  // display the contents of the list
  theList.moveToStart();
  for (i = 0; i < theList.length(); ++i) {
    cout << theList.getValue() << " ";

    theList.next();
  }
  cout << "\n";
  
    // display the contents of the list in reverse order
    theList.moveToEnd();
    for (i = 0; i < theList.length(); ++i)
    {
        theList.prev();

        cout << theList.getValue() << " ";
    }
    cout << "\n";

    // replace the contents of the list
    theList.clear();
    for (i = 0; i < 10; ++i)
    {
        theList.append(i + 100);
    }

    // display the contents of the list
    theList.moveToStart();
    for (i = 0; i < theList.length(); ++i)
    {
        cout << theList.getValue() << " ";

        theList.next();
    }
    cout << "\n";

    // remove two elements at the specified position
    theList.moveToPos(5);
    cout << theList.currPos() << "\n";

    theList.remove();
    theList.remove();

    // display the contents of the list
    theList.moveToStart();
    for (i = 0; i < theList.length(); ++i)
    {
        cout << theList.getValue() << " ";

        theList.next();
    }
    cout << "\n";
  
  return 0;
}
