#include <iostream>

using namespace std;

struct Node {

  int value;
  Node *next;
  
};

void push(Node *&head, int value) {

    Node* new_node = new Node;

    new_node->value = value;

    new_node->next = head;

    head = new_node;
}

void insertAfter(Node *&PrevHead, int value) {

    if (PrevHead == NULL){

        cout << "The given node cannot be NULL" << endl;
        return;
    }

    Node* new_node = new Node;

    new_node->value = value;

    new_node->next = PrevHead->next;

    PrevHead->next = new_node;
}


void append(Node *&head, int value ) {

    Node* new_node = new Node;

    Node *last = head;

    new_node->value = value;

    new_node->next = NULL;

    if (head == NULL)
    {
        head = new Node;
        return;
    }

    while (last->next != NULL)
    {
        last = last->next;
    }

    last->next = new_node;
    return;
}



void printList(Node *&node, int value)
{

    while ( node != NULL)
    {
        cout << " " << node->next;
        node = node->next;
    }

}





/* int main() {
