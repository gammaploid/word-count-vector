
#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <cstddef>
#include <stdexcept>

template <typename T>
class MyVector {
public:
    typedef T* iterator;


    // constructor
    MyVector() : capacity_(initial_capacity), size_(0) {
        data_ = new T[capacity_];
    }

    // destructor
    ~MyVector() {
        delete[] data_;
    }


    // constructor -- copied
    MyVector(const MyVector& other) : capacity_(other.capacity_), size_(other.size_)  {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
         }
    }



    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            data_ = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this; // its pointer
    }

    //  iterator starter
    iterator begin() const {
        return data_;
    }

     //  iterator killer
    iterator end() const {
        return data_ + size_;
    }

    // size updater
    size_t size() const {
        return size_;
    }



    void push_back(const T& item) {
         if (size_ == capacity_) {
            resize(2 * capacity_);
          }
        data_[size_++] = item;
     }


      // insert item at specific position
     iterator insert(iterator position, const T& item) {
         size_t index = position - data_;
        if (size_ == capacity_) {
            resize(2 * capacity_);
        }

        for (size_t i = size_; i > index;--i) {
            data_[i] = data_[i -1];
        }

         data_[index] = item;
         ++size_;
         return data_ + index;
    }

    // bound checking to access element
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return data_[index];
    }

    // bound checking for const access
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("index out of range.");
        }
        return data_[index];
    }

 private:
    T* data_;
    size_t capacity_;
    size_t size_;
    static const size_t initial_capacity = 10;


    // internal array RESIZE
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i =0; i< size_;++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;

     }
 };

#endif // MYVECTOR_H
