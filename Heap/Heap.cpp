#include "Heap.h"

Heap::Heap()
{
  root = new node;
  size = 0;
}
Heap::Heap(Heap& b) {
  root = new node;
  *this = b;
}

Heap::~Heap()
{
  ClearRc(root);
  delete root;
}

void Heap::Insert(int a)
{
  
  node* q = root;
  if (size == 0) {
    q->key = a;
    size++;
  }
  else {
    size++;
    int n_size = size;
    
    int o = 0;
    int st = 1;
    int k = 0;
    while (n_size > 1) {
      o += st * (n_size % 2);   
      n_size /= 2;
      st *= 2;
      k++;
    }

    n_size = o;

    k--;
    while (k--) {
      if (n_size % 2 == 0) {
        q = q->l_son;
        
      }
      else {
        q = q->r_son;
        
      }
      n_size /= 2;
    }
    

    if (n_size == 0) {
      q->l_son = new node;
      q->l_son->par = q;
      q->l_son->key = a;
      q = q->l_son;
    }
    else {
      q->r_son = new node;
      q->r_son->par = q;
      q->r_son->key = a;
      q = q->r_son;
    }
  
    
    while (q->par != 0 && q->key < q->par->key) {
      swap(q->key, q->par->key);
      q = q->par;
    }
  }
}

int Heap::GetMin()
{
  return root->key;
}                                      
bool Heap::Empty()
{
  return (size == 0);
}

void Heap::DeleteMin()
{
  if (!Empty()) {
    int n_size = size;

    node* q = root;

    int o = 0;
    int st = 1;
    int k = 0;
    while (n_size > 1) {
      o += st * (n_size % 2);
      n_size /= 2;
      st *= 2;
      k++;
    }

    n_size = o;
    bool rol = 0;

  

    while (k--) {
      if (n_size % 2 == 0) {
        q = q->l_son;
        rol = 0;
      }
      else {
        q = q->r_son;
        rol = 1;
      }
    }
    
    
    root->key = q->key;
    

    size--;
    if (q->par != 0) {
      if (rol == 0) {
        q->par->l_son = 0;
      }
      else {
        q->par->r_son = 0;
      }
    }

    delete q;

    q = root;
    
    while (((q->l_son != 0 && q->key > q->l_son->key) || (q->r_son != 0 && q->key > q->r_son->key))) {
      if ((q->l_son != 0 && q->key > q->l_son->key)) {
        swap(q->key, q->l_son->key);
        q = q->l_son;
      }
      else {
        swap(q->key, q->r_son->key);
        q = q->r_son;
      }
    }
  }
}

void Heap::Clear()
{
  ClearRc(root);
  size = 0;
  root->l_son = 0;
  root->r_son = 0;
  root->key = 0;
}

void Heap::ClearRc(node* q)
{
  if (q->l_son != 0) {
    ClearRc(q->l_son);
  }
  if (q->r_son != 0) {
    ClearRc(q->r_son);
  }       

  if (q != root) delete q;
}

void Heap::CoutRc(ostream& out, node* q)
{
  if (q->l_son != 0) {
    CoutRc(out, q->l_son);
  }
  if (q->r_son != 0) {
    CoutRc(out, q->r_son);
  }

  out << q->key << " ";
}

void Heap::CopyRc(node* a, node* b)
{
  if (b->l_son != 0) {
    a->l_son = new node;
    a->l_son->par = a;
    CopyRc(a->l_son, b->l_son);
  }
  if (b->r_son != 0) {
    a->r_son = new node;
    a->r_son->par = a;
    CopyRc(a->r_son, b->r_son);
  }
  a->key = b->key;
}

Heap& Heap::operator=(Heap& a) {
  this->Clear();
  CopyRc(root, a.root);
  size = a.size;
  return *this;
}

void Heap::Swap(Heap& b)
{
  Heap c(b);
  b = *this;
  *this = c;
}

istream& operator>>(istream& in, Heap& a)
{
  int c, n;
  in >> n;

  for (int i = 0; i < n; i++) {
    in >> c;
    a.Insert(c);
  }
  return in;
}

ostream& operator<<(ostream& out, Heap& a)
{
  a.CoutRc(out, a.root);

  return out;
}
