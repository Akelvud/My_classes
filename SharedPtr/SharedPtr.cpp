#include <iostream>
#include <array>
using namespace std;

template <typename  T>
class Deleter
{
public:

  void operator () (T* t) {
    delete t;
  }
};


template <typename  T>
class Deleter<T[]>
{
public:

  void operator () (T* t) {
    delete[] t;
  }
};

template <typename T, typename F = Deleter<T>> class SharedPtr;

template <typename T, typename F>
class SharedPtr
{
public:
  SharedPtr() = default;
  SharedPtr(T*);
  SharedPtr(SharedPtr&);

  ~SharedPtr();

  void reset();

  SharedPtr& operator=(T*);
  SharedPtr& operator=(SharedPtr&) noexcept;


  operator bool();

  T& operator *();
  T* operator ->();

private:

  F Deleter;
  T* item = nullptr;
  int* k = nullptr;
};

template <typename T, typename F>
SharedPtr<T, F>::SharedPtr(T* item) : item(item) {
  k = new int(1);
}

template <typename T, typename F>
SharedPtr<T, F>::SharedPtr(SharedPtr& ptr) : item(ptr.item), k(ptr.k) {
  (*k)++;
}


template <typename T, typename F>
SharedPtr<T, F>::~SharedPtr() {
  reset();
}

template <typename T, typename F>
void SharedPtr<T, F>::reset() {
  if (k == nullptr) return;
  if (*k == 0) return;


  (*k)--;
  
  if (*k == 0) {
    Deleter(item);
    item = nullptr;
    delete k;
  }
}

template <typename T, typename F>
SharedPtr<T, F>& SharedPtr<T, F>::operator=(T* n_item) {
  reset();
  item = n_item;
  k = new int(1);
  return *this;
}

template <typename T, typename F>
SharedPtr<T, F>& SharedPtr<T, F>::operator=(SharedPtr& ptr) noexcept {
  if (this != &ptr) {
    reset();

    item = ptr.item;
    k = ptr.k;
    (*k)++;
  }
  return *this;
}

template <typename T, typename F>
SharedPtr<T, F>::operator bool() {
  return item != nullptr;     
}


template <typename T, typename F>
T& SharedPtr<T, F>::operator *() {
  return *item;
}

template <typename T, typename F>
T* SharedPtr<T, F>::operator ->() {
  return &(this -> operator *());
}


template <typename T, typename F>
class SharedPtr<T[], F>
{
public:
  SharedPtr() = default;
  SharedPtr(T*);
  SharedPtr(SharedPtr&);
  SharedPtr(const SharedPtr&) = delete;

  ~SharedPtr();

  void reset();

  SharedPtr& operator=(T*);
  SharedPtr& operator=(SharedPtr&) noexcept;


  operator bool();

  T& operator[](int i);

private:
  F Deleter;
  T* item = nullptr;
  int* k = nullptr;
};

template <typename T, typename F>
void SharedPtr<T[], F>::reset() {
  if (k == nullptr) return;
  if (*k == 0) return;

  (*k)--;
  if (*k == 0) {
    Deleter(item);
    item = nullptr;
    delete k;
  }
}

template <typename T, typename F>
SharedPtr<T[], F>::operator bool() {
  return item != nullptr;
}

template <typename T, typename F>
SharedPtr<T[], F>::~SharedPtr() {
  reset();
}

template <typename T, typename F>
SharedPtr<T[], F>::SharedPtr(T* item) : item(item) {
  k = new int(1);
}

template <typename T, typename F>
SharedPtr<T[], F>& SharedPtr<T[], F>::operator=(SharedPtr& ptr) noexcept {
  if (this != &ptr) {
    reset();

    item = ptr.item;
    k = ptr.k;
    (*k)++;
  }
  return *this;
}


template <typename T, typename F>
T& SharedPtr<T[], F>::operator[](int i) {
  return *(item + i);
}


template<typename>
constexpr bool isArray = false;
template<typename T>
constexpr bool isArray<T[]> = true;

template <typename T, typename... Args>
std::enable_if_t<!is_array<T>::value, SharedPtr<T>>
MakeShared(Args&&... args) {
  return SharedPtr<T>(new T(forward<Args>(args)...));
}

template <typename T>
std::enable_if_t<isArray<T>, SharedPtr<T>>
MakeShared(size_t n) {
  return SharedPtr<T>(new remove_extent_t<T>[n]);
}




