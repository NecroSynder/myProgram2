#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

void slowSort(int arr[], int n) {
  random_device rd;  
  mt19937 gen(rd()); 
  uniform_int_distribution<> dis(0, n - 1);

  int i, j;

  bool sorted = false;  // initialize sorted to false
  while (!sorted) {     // replace true with !sorted
    i = dis(gen) % n;
    j = dis(gen) % n;

    if (i < j && arr[i] > arr[j]) {
      swap(arr[i], arr[j]);
    }

    sorted = true;
    for (int k = 1; k < n; k++) {
      if (arr[k] < arr[k - 1]) {
        sorted = false;
        break;
      }
    }
  }
}

int main() {
  int n = 4000;
  int arr[n];

  /* random_device rd;  
  mt19937 gen(rd()); 
  uniform_int_distribution<> dis(0, n - 1);

  for (int i = 0; i < n; i++) {
    arr[i] = dis(gen);  // generate random numbers using the Mersenne Twister engine
  }

  cout << "Unordered Array: " << endl;
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  } */

  auto start = chrono::high_resolution_clock::now();
  slowSort(arr, n);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "\n\nTime taken by Slow Sort Algorithm: " << fixed << setprecision(1)
       << duration.count() << " milliseconds" << endl;

  /* cout << "\nOrdered Array: " << endl;
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl; */

  return 0;
}
