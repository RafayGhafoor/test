#include <iostream>
#include <string>
#include "list.h"

using namespace std;

class File {
  string name;
  int size;
  List<Block> *nodes;

  void init(string name = "", int size = 0,
            List<Block> *nodes = new List<Block>) {
    this->name = name;
    this->size = size;
    this->nodes = nodes;
  }

 public:
  friend ostream &operator<<(ostream &out, File &f);
  friend istream &operator>>(istream &in, File &f);
  friend class FileSystem;

  File() { init(); }

  File(File &obj) { init(name, size, nodes); }

  File(string name, int size, List<Block> *nodes) { init(name, size, nodes); }

  File(string name, int size) { init(name, size, new List<Block>); }

  inline bool operator==(string n) { return name == n; }

  operator bool() const { return name != ""; }

  ~File() {
    // if (nodes) {
    //   delete nodes;
    // }
  }

  int get_required_sectors(int defined_bytes_in_sector) const {
    return size / defined_bytes_in_sector;
  }
};

ostream &operator<<(ostream &out, File &f) {
  out << "Name: " << f.name << endl;
  out << "\nSize: " << f.size << endl;
  return out;
}

istream &operator>>(istream &in, File &f) {
  cout << "=============FILE====================\n";
  cout << "Please enter name of the file: \n";
  in >> f.name;
  cout << "\nPlease enter size of the file: \n";
  in >> f.size;
  cout << "\n[Enter Nodes]\n";
  int blocks_count;
  cout << "Please enter Blocks Count: \n";
  cin >> blocks_count;

  for (int i = 0; i < blocks_count; i++) {
    Block a;
    cout << "\nBlock Number [" << i + 1 << "]\n";
    cin >> a;
    f.nodes->push(a);
  }
  cout << "\n===========FILE======================\n";
  return in;
}
