#include <iostream>
#include <string>
#include "list.h"

using namespace std;

const int BYTES_IN_SECTOR = 2;  // A sector contains 2 bytes

int main() {
  List<string> arr;
  arr.get(3);
  cout << endl;
  // arr.display();
  cout << arr.find("Hello") << endl;
}