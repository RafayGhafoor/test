#include <iostream>
#include <string>

using namespace std;

template <class T>
class Node {
 public:
  T data;
  Node *next;

 public:
  template <typename U>
  friend ostream &operator<<(ostream &out, Node<U> &f);
  template <typename U>
  friend istream &operator>>(istream &in, Node<U> &f);
  Node() { next = nullptr; }
  Node(T d, Node *n = nullptr) : data(d), next(n) {}
};

template <typename T>
ostream &operator<<(ostream &out, Node<T> &f) {
  cout << f.data << endl;
  return out;
}

template <typename T>
istream &operator>>(istream &in, Node<T> &f) {
  cout << "[Enter data]\n";
  in >> f.data;
  next = new Node<T>;
  return in;
}
template <class T>
class List {
 private:
  Node<T> *head;
  Node<T> *tail;
  int size;
  void init(Node<T> *head = new Node<T>, Node<T> *tail = new Node<T>,
            int size = 0) {
    this->head->next = tail;
  }

 public:
  template <typename U>
  friend ostream &operator<<(ostream &out, List<U> &f);
  template <typename U>
  friend istream &operator>>(istream &in, List<U> &f);
  friend void push(string value);
  friend class FileSystem;

  List() {
    this->head = new Node<T>;
    this->tail = new Node<T>;
    this->head->next = tail;
    this->size = 0;
  }

  List(List &obj) { init(obj.head, obj.tail, obj.size); }

  void push(T d) {
    if (head->data) {
      tail->data = d;
      tail->next = new Node<T>;
      tail = tail->next;
      size++;
    }
    else {
      head->data = d;
      head->next = tail;
      return;
    }
  }

  ~List() {
    while (this->head->next != this->tail) {
      if (this->head->next != this->tail) {
        Node<T> *t = this->head->next;
        head->next = t->next;
        if (t) delete t;
      }
    }
    if (this->head) delete this->head;
    if (this->tail) delete this->tail;
  }

  bool equals(string x) {
    Node<T> *current = head;
    while (current != this->tail) {
      if (current->data == x) return true;
      current = current->next;
    }
    return false;
  }

  bool find(T x, bool debug = 0) {
    Node<T> *current = head;
    while (current != this->tail) {
      if (current->data == x) {
        if (debug) cout << x << " Found." << endl;
        return true;
      }
      current = current->next;
    }
    if (debug) cout << x << " Not Found." << endl;
    return false;
  }

  void display() {
    while (this->head) {
      cout << this->head << endl;
      if (this->head->next == this->tail) break;
      this->head = this->head->next;
    }
  }

  void get(int intake = 1, bool debug = 0) {
    if (debug) cout << "Intake set to: " << intake << endl;
    cout << "Enter data:\n";
    T data;

    for (int i = 0; i < intake; i++) {
      cin >> data;
      push(data);
    }
  }
};

template <>
void List<string>::push(string value) {
  if (head->data == "") {
    head->data = value;
    head->next = tail;
    return;
  }
  tail->data = value;
  tail->next = new Node<string>;
  tail = tail->next;
  size++;
}

template <typename U>
ostream &operator<<(ostream &out, List<U> &f) {
  while (f.head) {
    cout << f.head << endl;
    if (f.head->next == f.tail) break;
    f.head = f.head->next;
  }
  return out;
}

template <typename U>
istream &operator>>(istream &in, List<U> &f) {
  U data;
  cout << "[Enter data]\n";
  cin >> data;
  f.push(data);
  return in;
}