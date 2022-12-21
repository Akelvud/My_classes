#include <iostream>
#include <fstream>

using namespace std;

struct node
{
  int key = 0;
  node* l_son = 0;
  node* r_son = 0;
  node* par = 0;
};


class Heap
{
public:
  Heap();
  Heap(Heap& b);
  ~Heap();
  
  void Insert(int a);
  int GetMin();
  bool Empty();
  void DeleteMin();
  void Clear();
  void Swap(Heap& b);
  Heap& operator=(Heap& a);


  friend istream& operator>>(istream& in, Heap& a);
  friend ostream& operator<<(ostream& out, Heap& a);

private:
  void ClearRc(node* q);
  void CoutRc(ostream& out ,node* q);
  void CopyRc(node* a, node* b);
  node* root;
  int size;
};

