#include "vector.h"

Vector::Vector() {
    size_ = 0;
    capacity_ = 0;
    array_ = nullptr;
}

Vector::Vector(size_t size) {
    size_ = size;
    capacity_ = size;
    array_ = new ValueType[capacity_];

    for (int i = 0; i < size_; i++) array_[i] = 0;
}

Vector::Vector(std::initializer_list<ValueType> list) {
    size_ = list.size();
    capacity_ = list.size();
    array_ = new ValueType[capacity_];

    int i = 0;
    for (auto it:list) {
        array_[i++] = it;
    }
}

Vector::Vector(Vector& other) {
    *this = other;
}

Vector &Vector::operator=(const Vector &other) {
    Clear();

    size_ = other.size_;
    capacity_ = other.capacity_;
    array_ = new ValueType[capacity_];

    for (int i = 0; i < size_; i++) array_[i] = other.array_[i];
    return *this;
}

Vector::~Vector() {
    if (array_ != nullptr) {
        delete[] array_;
    }
}

Vector::SizeType Vector::Size() const {
    return size_;
}

Vector::SizeType Vector::Capacity() const {
    return capacity_;
}

const Vector::ValueType *Vector::Data() const {
    return array_;
}

Vector::ValueType &Vector::operator[](size_t position) {
    return array_[position];
}

Vector::ValueType Vector::operator[](size_t position) const {
    Vector::ValueType o = array_[position];
    return o;
}

bool Vector::operator==(const Vector &other) const {
    if (size_ != other.size_) {
        return false;
    }

    for (int i = 0; i < size_; i++) {
        if (array_[i] != other.array_[i]) {
            return false;
        }
    }

    return true;
}

bool Vector::operator!=(const Vector &other) const {
    return !(*this == other);
}

std::strong_ordering Vector::operator<=>(const Vector &other) const {
    for (int i = 0; i < size_ && i < other.size_; i++) {
        if (array_[i] < other[i]) {
            return  std::strong_ordering::less;
        }
        if (array_[i] < other[i]) {
            return  std::strong_ordering::greater;
        }
    }
    if (size_ < other.size_) {
        return  std::strong_ordering::less;
    }
    if (size_ > other.size_) {
        return  std::strong_ordering::greater;
    }
    return std::strong_ordering::equal;
}

void Vector::Reserve(SizeType new_capacity) {
    if (capacity_ >= new_capacity) {
        return;
    }
    capacity_ = new_capacity;
    ValueType* new_array = new ValueType[capacity_];

    for (int i = 0; i < size_; i++) {
        new_array[i] = array_[i];
    }
    if (array_ != nullptr) {
        delete[] array_;
    }
    array_ = new_array;
}

void Vector::Clear() {
    size_ = 0;
}


void Vector::PushBack(const ValueType &new_element) {
    if (size_ == capacity_) {
        if (capacity_ == 0) {
            Reserve(1 );
        } else {
            Reserve(capacity_ * 2);
        }

    }
    array_[size_++] = new_element;
}

void Vector::PopBack() {
    if (size_ != 0) {
        size_--;
    }
}

void Vector::Swap(Vector &other) {
    std::swap(array_, other.array_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

Vector::Iterator Vector::Begin() {
    return Iterator(&array_[0]);
}

Vector::Iterator Vector::End() {
    return Iterator(&array_[size_]);
}

Vector::Iterator Vector::begin() {
    return Begin();
}

Vector::Iterator Vector::end() {
    return End();
}

Vector::Iterator::Iterator() {
    i = nullptr;
}

Vector::Iterator::Iterator(ValueType *pointer) {
    i = pointer;
}

Vector::ValueType &Vector::Iterator::operator*() const {
    return *i;
}

Vector::ValueType *Vector::Iterator::operator->() const {
    return i;
}

Vector::Iterator &Vector::Iterator::operator=(Iterator other) {
    i = other.i;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator++() {
    i++;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator new_it(*this);
    i++;
    return new_it;
}

Vector::Iterator& Vector::Iterator::operator--() {
    i--;
    return *this;
}

Vector::Iterator Vector::Iterator::operator--(int) {
    Iterator new_it(*this);
    i--;
    return new_it;
}

Vector::Iterator Vector::Iterator::operator+(DifferenceType shift) {
    Iterator temp = *this;
    return temp += shift;
}

Vector::DifferenceType Vector::Iterator::operator-(Iterator other) {
    return i - other.i;
}

Vector::Iterator &Vector::Iterator::operator+=(DifferenceType shift) {
    DifferenceType m = shift;
    if (m >= 0) {
        while(m--) {
            ++*this;
        }
    } else {
        while(m++) {
            --*this;
        }
    }
    return  *this;
}

Vector::Iterator &Vector::Iterator::operator-=(DifferenceType shift) {
    return *this += -shift;
}

bool Vector::Iterator::operator==(const Iterator &other) const {
    return (i - other.i) == 0;
}

bool Vector::Iterator::operator!=(const Iterator &other) const {
    return !(*this == other);
}

std::strong_ordering Vector::Iterator::operator<=>(const Iterator &other) const {
    int m = i - other.i;
    if (m < 0) {
        return  std::strong_ordering::less;
    }
    if (m > 0) {
        return  std::strong_ordering::greater;
    }
    return std::strong_ordering::equal;
}






