#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

template <class T>
class List;
template <class T>
class Node {
 public:
  T data;
  Node *next;

 public:
  Node() { next = nullptr; }
  Node(T d, Node *n = nullptr) : data(d), next(n) {}
};
template <class T>
class List {
 private:
  Node<T> *head;
  Node<T> *tail;
  int size;

 public:
  List() {
    this->head = new Node<T>;
    this->tail = new Node<T>;
    this->head->next = tail;
    this->size = 0;
  }
  List(T d) {
    this->head = new Node<T>;
    this->tail = new Node<T>;
    this->head->next = tail;
    this->size = 0;

    this->tail->data = d;
    this->tail->next = new Node<T>;
    this->tail = tail->next;
    this->size++;
  }
  void InsertAtEnd(T d)  ////insert a new node before tail
  {
    tail->data = d;
    tail->next = new Node<T>;
    tail = tail->next;
    size++;
  }

  ~List() {
    while (this->head->next != this->tail) {
      if (this->head->next != this->tail) {
        Node<T> *t = this->head->next;
        head->next = t->next;
        delete t;
      }
    }
    delete this->head;
    delete this->tail;
  }
  friend class FileSystem;
};
class Block {
  // public:

 public:
  int start_sector_ID;
  int total_sectors;
  Block() {}
  Block(int start, int total) {
    this->start_sector_ID = start;
    this->total_sectors = total;
  }
  friend class FileSystem;
};
class File {
  // public:
  char *name;
  int size;
  List<Block> *list;

 public:
  File() {
    this->name = nullptr;
    this->size = 0;
    this->list = new List<Block>;
  }
  File(char *n, int s) {
    this->name = new char(strlen(n) + 1);
    strcpy(this->name, n);
    this->size = s;
    this->list = new List<Block>;
  }
  friend class FileSystem;
};
class FileSystem {
 public:
  int numOfSectorsInPool;
  List<Block> *pool;
  List<File> *files;
  int sizeOfSectors;
  char *disk;
  int numOfSectors;
  FileSystem() {
    this->disk = nullptr;
    this->pool = nullptr;
    this->files = nullptr;
  }

  FileSystem(int sec, int s) {
    this->numOfSectorsInPool = sec;
    this->sizeOfSectors = s;
    this->numOfSectors = sec;
    this->disk = new char((numOfSectors * sizeOfSectors) + 1);
    this->disk[numOfSectors * sizeOfSectors] = '\0';
    this->pool = new List<Block>;
    this->pool->InsertAtEnd(Block(0, numOfSectors));
    this->files = new List<File>;
  }

  bool SearchFileExists(char *fname) {
    Node<File> *temp = new Node<File>;
    temp = files->head;

    while (temp != files->tail) {
      if (strcmp(temp->data.name, fname) == 0) return 0;

      temp = temp->next;
    }

    return 1;
  }

  bool SaveFile(char *fname, char *fcontent, int fsize) {
    if (numOfSectorsInPool * sizeOfSectors < fsize) return 0;

    // if (!SearchFileExists(fname))
    // return 0;
    int a = 0;
    // cout << "BEFORE MAKING FILE"<<endl;
    cout << files->head << endl << files->tail << endl;
    // cout << "AFTER  MAKING FILE"<<endl;
    File *f = new File(fname, fsize);
    files->InsertAtEnd(*f);

    // cout << "CURRENT BLOCK = POOL HEAD"<<endl;
    Node<Block> *current_block = pool->head;

    while (current_block != pool->tail) {
      if (current_block->next->data.total_sectors < fsize / sizeOfSectors) {
        cout << "here";

        // if (current_block==pool->head->next) // To take first element of
        // block after dummy head
        // {
        // 	// moving nodes pointers from pool
        // 	Node <Block> *temp=current_block;
        // 	pool->head->next=current_block->next;

        // 	//Modified Insert at End
        // 		// tail->data = element;

        // 		// tail->next= new Node <T>;
        // 		// tail=tail->next;
        // 		// size++;

        // 	f->list->tail->data =
        // Block(temp->data.start_sector_ID,temp->data.total_sectors);
        // 	f->list->tail= temp;
        // 	f->list->tail->next= new Node <Block>;
        // 	f->list->tail=f->list->tail->next;
        // 	f->list->size++;
        // 	fsize=fsize-(temp->data.total_sectors*sizeOfSectors);
        // 	current_block=current_block->next;

        // 	for (int i=temp->data.start_sector_ID*sizeOfSectors;
        // i<temp->data.start_sector_ID*sizeOfSectors+temp->data.total_sectors*2;
        // i++,a++) 	disk[i]= fcontent[a];
        // }
        // else // I dont think it will go here // To take middle element of
        // block
        // {
        // 	Node <Block> *temp= current_block->next;
        // 	current_block->next=current_block->next->next;

        // 	f->list->tail->data =
        // Block(temp->data.start_sector_ID,temp->data.total_sectors);
        // 	f->list->tail= temp;
        // 	f->list->tail->next= new Node <Block>;
        // 	f->list->tail=f->list->tail->next;
        // 	f->list->size++;
        // 	fsize=fsize-(temp->data.total_sectors*sizeOfSectors);

        // }
      }
      if (current_block->next->data.total_sectors == fsize / sizeOfSectors) {
        cout << "here";

        // Same functions // Only difference is function is returning 1
        // if (current_block==pool->head->next)
        // {
        // 	Node <Block> *temp= current_block;
        // 	pool->head->next=current_block->next;

        // 	f->list->tail->data =
        // Block(temp->data.start_sector_ID,temp->data.total_sectors);
        // 	f->list->tail= temp;
        // 	f->list->tail->next= new Node <Block>;
        // 	f->list->tail=f->list->tail->next;
        // 	f->list->size++;
        // 	fsize=fsize-(temp->data.total_sectors*sizeOfSectors);
        // 	for (int i=temp->data.start_sector_ID*sizeOfSectors;
        // i<temp->data.start_sector_ID*sizeOfSectors+temp->data.total_sectors*2;
        // i++,a++) 	disk[i]= fcontent[a]; 	return 1;

        // }
        // else
        // {
        // 	Node <Block> *temp= current_block->next;
        // 	current_block->next=current_block->next->next;

        // 	f->list->tail->data =
        // Block(temp->data.start_sector_ID,temp->data.total_sectors);
        // 	f->list->tail= temp;
        // 	f->list->tail->next= new Node <Block>;
        // 	f->list->tail=f->list->tail->next;
        // 	f->list->size++;
        // 	fsize=fsize-(temp->data.total_sectors*sizeOfSectors);
        // 	return 1;

        // }

      } else {
        if (current_block == pool->head) current_block = pool->head->next;

        if (current_block == pool->head->next) {
          //  cout <<"asin"<<endl;
          //  cout << f->list->head << endl << f->list->head->next << endl <<
          //  f->list->tail<<endl;

          Node<Block> *temp = new Node<Block>;
          temp->data.start_sector_ID = current_block->data.start_sector_ID;
          temp->data.total_sectors = fsize;
          f->list->InsertAtEnd(
              Block(temp->data.start_sector_ID, temp->data.total_sectors));
          //  cout <<"asin"<<endl;
          //  cout << f->list->head << endl << f->list->head->next << endl <<
          //  f->list->tail<<endl; cout <<f->list->head->next->next<<endl;

          // Insert at end, now doing by function
          // f->list->tail->data=
          // Block(current_block->data.start_sector_ID,fsize);
          // f->list->tail=temp;
          // f->list->tail->next= new Node <Block>;
          // f->list->tail=f->list->tail->next;
          // f->list->size++;
          current_block->data.total_sectors -= fsize;
          numOfSectorsInPool -= temp->data.total_sectors;
          for (int i = temp->data.start_sector_ID * sizeOfSectors;
               i < temp->data.start_sector_ID * sizeOfSectors +
                       temp->data.total_sectors * sizeOfSectors;
               i++, a++) {
            disk[i] = fcontent[a];
          }
          return 1;
        } else {
        }
      }
    }

    return 0;
  }

  void DeleteFile(char *fname) {
    Node<File> *f = files->head->next;
    if (f != files->tail) {
      while (f->next != files->tail) {
        if (strcmp(f->next->data.name, fname) == 0) {
          Node<File> *temp =
              f->next;  // Store file to delete in a temp variable so we can
                        // access it even after changing the pointed nodes in
                        // linked list
          f->next = f->next->next;

          Node<Block> *file_blocks = temp->data.list->head->next;
          while (file_blocks !=
                 temp->data.list
                     ->tail)  // While Blocks of file do not reach end of blocks
          {
            Node<Block> *temp_use = file_blocks->next;
            // cout<<file_blocks->data.start_sector_ID <<
            // file_blocks->data.total_sectors <<endl;
            AddBlockToPool(file_blocks, file_blocks->data.start_sector_ID,
                           file_blocks->data.total_sectors);
            file_blocks = temp_use;
          }
          MergeBlocks();
          delete temp;
        }
      }
    }
  }

  void AddBlockToPool(Node<Block> *b, int start_id,
                      int sectors)  /// add blocks to pool list
  {
    Node<Block> *curr = pool->head->next;
    bool flag = 0;

    while (curr != pool->tail) {
      if (curr->next->data.start_sector_ID >= start_id) {
        // Add //Without creating more nodes, just shifting/moving from files to
        // pool by changing next/previous nodes Files mai b next/previous nodes
        // change honge Aise "moving" honi hai shyd
        b->next = curr->next;
        curr->next = b;
        numOfSectorsInPool += sectors;  // update sectors in pool
        flag = 1;

        // Merge aik agay aik peeche aur phir overall sub ka merge aik dfa upar
        // walay function mai, wrna saray merge nhi honge
        if (curr->data.start_sector_ID + curr->data.total_sectors ==
            b->data.start_sector_ID) {
          curr->data.total_sectors += b->data.total_sectors;
          curr->next = curr->next->next;
          delete b;
        }
        if (curr->data.start_sector_ID + curr->data.total_sectors ==
            curr->next->data.start_sector_ID) {
          curr->data.total_sectors += curr->next->data.total_sectors;
          Node<Block> *temp = curr->next;
          curr->next = curr->next->next;
          delete temp;
        }
      }
      if (flag) break;
      curr = curr->next;
    }
  }

  void MergeBlocks() {
    Node<Block> *p = pool->head->next;
    bool flag = 0;
    while (p->next != pool->tail) {
      if (p->data.start_sector_ID + p->data.total_sectors ==
          p->next->data.start_sector_ID) {
        p->data.total_sectors += p->next->data.total_sectors;
        Node<Block> *temp = p->next;
        p->next = p->next->next;
        delete temp;
      }
      p = p->next;
    }
  }

  void ReadFile(char *fname) {
    bool flag = 0;
    Node<File> *traverse = files->head->next;
    while (traverse != files->tail) {
      if (strcmp(traverse->data.name, fname) == 0) {
        Node<Block> *blocks_traverse =
            traverse->data.list->head->next;  // 1st block
        // cout <<"assign"<<endl;
        // cout << blocks_traverse<<endl;
        // cout << blocks_traverse->next;
        // cout <<endl <<traverse->data.list->tail;
        while (blocks_traverse != traverse->data.list->tail) {
          for (int a = blocks_traverse->data.start_sector_ID, i = 0;
               i < blocks_traverse->data.total_sectors * sizeOfSectors;
               i++, a++) {
            cout << disk[a];
            // cin.ignore();
            // cout <<"testing"<<endl;
          }
          blocks_traverse = blocks_traverse->next;
        }
        flag = 1;
      }
      if (flag)
        break;
      else {
        traverse = traverse->next;
      }
    }
    // cout <<"readfile";
  }
};
int main() {
  int a, b;
  cout << "Enter number of total sectors= ";
  cin >> a;
  cout << "Enter size for one sector= ";
  cin >> b;
  FileSystem fsystem(a, b);
  // cout << fsystem.numOfSectorsInPool << endl << fsystem.numOfSectors << endl
  // << fsystem.sizeOfSectors <<endl <<
  // fsystem.pool->head->next->data.start_sector_ID <<
  // fsystem.pool->head->next->data.total_sectors<<endl;
  bool check = fsystem.SaveFile("f1", "qq", 1);
  if (check) fsystem.ReadFile("f1");
  cout << endl;
  bool check2 = fsystem.SaveFile("f2", "ww", 1);
  if (check2) fsystem.ReadFile("f2");
  cout << endl
       << fsystem.numOfSectorsInPool << " " << fsystem.numOfSectors << endl;
  fsystem.DeleteFile("f2");
  cout << endl
       << fsystem.numOfSectorsInPool << " " << fsystem.numOfSectors << endl;
  fsystem.ReadFile("f2");
  fsystem.ReadFile("f1");

  // cout <<"out";
  // 		if (check==true)
  // 			cout<<"File saved"<<endl;
  // 		else
  // 			cout<<"Error saving file"<<endl;
}