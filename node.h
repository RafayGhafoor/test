template <class T>
class Node {
 public:
  T data;
  Node *next;

 public:
  Node() { next = nullptr; }
  Node(T d, Node *n = nullptr) : data(d), next(n) {}
};