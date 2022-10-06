#include <assert.h>
#include <iostream>

using namespace std;

int main(void) {

  int *intarr[10];
  int i;

  for (i = 0; i < 10; ++i) {
    intarr[i] = new int;
    assert(intarr[i] != NULL);

    *intarr[i] = i + 1;
  }

  for (i = 0; i < 10; ++i) {
    cout << intarr[i] << ": " << *intarr[i] << endl;
  }

  for (i = 0; i < 10; ++i) {
    delete intarr[i];
  }

  return 0;
}