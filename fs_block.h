#include <iostream>
using namespace std;

class Block {
  int start_sector_ID, total_sectors;

  void init(int start_sector_ID = 0, int total_sectors = 0) {
    this->start_sector_ID = start_sector_ID;
    this->total_sectors = total_sectors;
  }

 public:
  friend ostream &operator<<(ostream &out, Block &f);
  friend istream &operator>>(istream &in, Block &f);
  friend class FileSystem;

  Block() { init(); }

  Block(Block &obj) { 
      init(obj.start_sector_ID, obj.total_sectors); 
    }

  Block(int start_sector_ID, int total_sectors) {
    init(start_sector_ID, total_sectors);
  }

  int get_block_size(int defined_bytes_in_sector = 2) const {
    return total_sectors * defined_bytes_in_sector;
  }

  operator bool() const { return total_sectors != 0; }
};

istream &operator>>(istream &in, Block &f) {
  cout << "=============BLOCK====================\n";
  cout << "Please enter start sector ID: \n";
  in >> f.start_sector_ID;
  cout << "Please enter total sectors: \n";
  in >> f.total_sectors;
  cout << "\n=============BLOCK====================\n";
  return in;
}

ostream &operator<<(ostream &out, Block &f) {
  cout << "=============BLOCK====================\n";
  out << "Start Sector ID: " << f.start_sector_ID;
  out << "\nTotal Sectors Count: " << f.total_sectors << endl;
  cout << "=============BLOCK====================\n";
  return out;
}
