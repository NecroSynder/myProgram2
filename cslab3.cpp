#include <assert.h>
#include <iostream>

using namespace std;

struct linkedlist {
  int value;
  linkedlist *next;
};

int main() {

  int value = 3;

  linkedlist one, two, three;
  one.value = 1;
  one.next = &two;
  two.value = 2;
  two.next = &three;
  three.value = 3;
  three.next = &one;

  linkedlist *cursor = &one;
  for (int i = 1; i <= 30; i++) {
    cout << cursor->value << " ";
    if (i % value == 0) {
      cout << endl;
    }
    cursor = cursor->next;
  }
  return 0;
}