#include <assert.h>
#include <iostream>

using namespace std;

struct Node{

  int value;
  Node *next;
  
};

int main() {

    int loop = 20;

    Node *head = new (Node);
    head->value = 1;
    head->next = NULL;

    Node *start = head;

    for (int i = 1; i < loop; i++) {
      start->next = new (Node);

      assert(start->next != NULL);
      
      start->next->value = i + 1;
      
      start->next->next = NULL;
      
      start = start->next;
      
      }

      start->next = head;
      start = head;

      for (int i = 1; i <= 200; i++){

        cout << start->value << " ";

        start = start->next;
      
        if (i % loop == 0){
          cout << endl;
        }
         
      }
      
      for (int i = 1; i < loop; i++) {

        Node *next = start->next;

        delete start;

        start = next;
        
      }
      
                  
      cout << "All data has been deleted" << endl;

      return 0;

    }  
    
