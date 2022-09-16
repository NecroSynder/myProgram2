#include <iostream>
using namespace std;

struct node {
    int value;
    node *newNode;
    bool ishead;
    };

int main(){
    int loop = 3;

    node *head = new (node);
    head->value = 1;
    head->newNode = NULL;

    node *ptr = head;

    for (int i = 1; i < loop; i++) {

        ptr->newNode = new (node);
        ptr->newNode->value = i + 1;
        ptr->newNode->newNode = NULL;
        ptr = ptr->newNode;
    }

    
    ptr->newNode = head;
    ptr = head;

    for (int i = 1; i <= 30; i++){
        cout << ptr->value << " ";
        ptr = ptr->newNode;
    }
        
    delete head;

    return 0;
}
    
