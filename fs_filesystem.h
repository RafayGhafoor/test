#include <cstring>
#include <iostream>

#include "fs_block.h"
#include "fs_file.h"

using namespace std;

class FileSystem {
  List<File> *files;
  List<Block> *pool;
  char *disk;
  int numOfSectors, sizeOfSectors, numOfSectorsInPool;

  void init(List<File> *files = new List<File>,
            List<Block> *pool = new List<Block>, char *disk = new char[200],
            int numOfSectors = 0, int sizeOfSectors = 0,
            int numOfSectorsInPool = 0) {
    this->files = files;
    this->pool = pool;
    this->disk = disk;
    this->numOfSectors = numOfSectors;
    this->sizeOfSectors = sizeOfSectors;
    this->numOfSectorsInPool = numOfSectorsInPool;
  }

 public:
  friend ostream &operator<<(ostream &out, FileSystem &f);
  friend istream &operator>>(istream &in, FileSystem &f);
  FileSystem() { init(); }

  FileSystem(FileSystem &obj) {
    init(obj.files, obj.pool, obj.disk, obj.numOfSectors, obj.sizeOfSectors,
         obj.numOfSectorsInPool);
  }
  // FileSystem(List<File> *files, List<Block> *pool, char *disk, int
  // numOfSectors,
  //            int sizeOfSectors, int numOfSectorsInPool) {}

  ~FileSystem() {
    // if (files) delete files;
    // if (pool) delete pool;
    // if (disk) delete[] disk;
  }

  void push_back(File obj) {
    if (!files->head->data) {
      files->head->data = obj;
      files->head->next = files->tail;
      return;
    }

    files->tail->data = obj;
    files->tail->next = new Node<File>;
    files->tail = files->tail->next;
    files->size++;
  }

  void push_back(Block obj) {
    if (!pool->head->data) {
      pool->head->data = obj;
      pool->head->next = pool->tail;
      return;
    }

    pool->tail->data = obj;
    pool->tail->next = new Node<Block>;
    pool->tail = pool->tail->next;
    pool->size++;
  }

  void saveFile(string fname, char fcontent[], int fsize) {}

  void deleteFile(string fname) {
    if (files->equals(fname)) {
      cout << "Do something";
      return;
    }

    cout << fname << " Not Found.\n";
  }

  void readFile(string fname) {
    Node<File> *tracker = files->head;
    for (; tracker != files->tail; tracker = tracker->next) {
      if (tracker->data.name == fname) {
        cout << "Print Data for File";
        return;
      }
    }
    cout << fname << " Not Found.\n";
  }
};

ostream &operator<<(ostream &out, FileSystem &f) {
  cout << "||||||||FAT FILESYSTEM SPECIFICATIONS OUTPUT||||||\n\n";
  if (f.files) out << f.files << endl;
  if (f.pool) out << f.pool << endl;
  if (f.disk) out << f.disk << endl;
  out << "Number of Sectors: " << f.numOfSectors
      << "\nSize of Sectors: " << f.sizeOfSectors
      << "\nNumber of Sectors in Pool: " << f.numOfSectorsInPool << endl;
  cout << "||||||||FAT FILESYSTEM SPECIFICATIONS OUTPUT||||||\n";
  return out;
}

istream &operator>>(istream &in, FileSystem &f) {
  cout << "||||||||FAT FILESYSTEM SPECIFICATIONS INPUT||||||\n\n";
  int files_count, blocks_count;
  cout << "Please enter files count: \n";
  cin >> files_count;
  cout << "\nPlease enter blocks count for pool: \n";
  cin >> blocks_count;

  char dsk[200];
  cout << "\nPlease enter disk: ";
  cin >> dsk;

  f.disk = new char[strlen(dsk + 1)];
  strcpy(f.disk, dsk);

  cout << "\nPlease enter number of sectors: ";
  in >> f.numOfSectors;

  cout << "\nPlease enter size of sectors: ";
  in >> f.sizeOfSectors;

  cout << "\nPlease enter number of sectors in pool: ";
  in >> f.numOfSectorsInPool;

  for (int i = 0; i < files_count; i++) {
    File temp;
    cout << "\n[Enter information for file " << i + 1 << "]\n" << endl;
    cin >> temp;
    f.push_back(temp);
  }

  for (int i = 0; i < blocks_count; i++) {
    Block temp_block;
    cout << "\nEnter information for Block " << i + 1 << endl << endl;
    cin >> temp_block;
    f.push_back(temp_block);
  }
  cout << "||||||||FAT FILESYSTEM SPECIFICATIONS INPUT||||||\n";
  return in;
}
