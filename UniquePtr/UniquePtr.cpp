#include <iostream>
#include <array>
using namespace std;

template <typename  T>
class Deleter
{
public:

  void operator () (T* t)  {
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

template <typename T, typename F = Deleter<T>> class UniquePtr;

template <typename T, typename F>
class UniquePtr
{
public:
  UniquePtr() = default;
  UniquePtr(T*);
  UniquePtr(UniquePtr&&);
  UniquePtr(const UniquePtr&) = delete;

  ~UniquePtr();

  void reset();

  UniquePtr& operator=(T*);
  UniquePtr& operator=(UniquePtr&&) noexcept;
  UniquePtr& operator=(const UniquePtr&) = delete;

  operator bool();

  T& operator *();
  T* operator ->();
  
private:
  
  F Deleter;
  T* item = nullptr;
};

template <typename T, typename F>
UniquePtr<T,F>::UniquePtr(T* item) : item(item) {}

template <typename T, typename F>
UniquePtr<T, F>::UniquePtr(UniquePtr&& ptr) : item(ptr.item) {
  ptr.item = nullptr;
}


template <typename T, typename F>
UniquePtr<T, F>::~UniquePtr() {
  reset();
}

template <typename T, typename F>
void UniquePtr<T, F>::reset() {
  
  Deleter(item);
  item = nullptr;
}

template <typename T, typename F>
UniquePtr<T,F>& UniquePtr<T, F>::operator=(T* n_item) {
  reset();
  item = n_item;
  return *this;
}

template <typename T, typename F>
UniquePtr<T, F>& UniquePtr<T, F>::operator=(UniquePtr&& ptr) noexcept {
  if (this != &ptr) {

    reset();
    item = ptr.item;
    ptr.item = nullptr;
  }
  return *this;
}

template <typename T, typename F>
UniquePtr<T, F>::operator bool() {
  return item != nullptr;
}


template <typename T, typename F>
T& UniquePtr<T, F>::operator *() {
  return *item;
}

template <typename T, typename F>
T* UniquePtr<T, F>::operator ->() {
  return &(this -> operator *());
}


template <typename T, typename F>
class UniquePtr<T[], F>
{
public:
  UniquePtr() = default;
  UniquePtr(T*);
  UniquePtr(UniquePtr&&);
  UniquePtr(const UniquePtr&) = delete;

  ~UniquePtr();

  void reset();

  UniquePtr& operator=(T*);
  UniquePtr& operator=(UniquePtr&&) noexcept;
  UniquePtr& operator=(const UniquePtr&) = delete;

  operator bool();

  T& operator[](int i);

private:
  F Deleter;
  T* item = nullptr;
};

template <typename T, typename F>
void UniquePtr<T[], F>::reset() {

  Deleter(item);
  item = nullptr;
}

template <typename T, typename F>
UniquePtr<T[], F>::operator bool() {
  return item != nullptr;
}

template <typename T, typename F>
UniquePtr<T[], F>::~UniquePtr() {
  reset();
}

template <typename T, typename F>
UniquePtr<T[], F>::UniquePtr(T* item) : item(item) {}


template <typename T, typename F>
T& UniquePtr<T[], F>::operator[](int i) {
  return *(item + i);
}


template<typename>
constexpr bool isArray = false;
template<typename T>
constexpr bool isArray<T[]> = true;

template <typename T, typename... Args>
std::enable_if_t<!is_array<T>::value, UniquePtr<T>>
MakeUnique(Args&&... args) {
  return UniquePtr<T>(new T(forward<Args>(args)...));
}

template <typename T>
std::enable_if_t<isArray<T>, UniquePtr<T>>
MakeUnique(size_t n) {
  return UniquePtr<T>(new remove_extent_t<T>[n]);
}








