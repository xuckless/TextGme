// DynamicArray.h
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

template <typename T>
class DynamicArray {
private:
    T* data; 
    int size;
    int capacity;

    void resize(); //this method adds more to the sie of the array which id what makees it dynamic 

public:
    DynamicArray(int initialCapacity = 2);
    ~DynamicArray();

    void add(const T& value);
    T get(int index) const;
    int getSize() const;
};

template <typename T>
DynamicArray<T>::DynamicArray(int initialCapacity) : size(0), capacity(initialCapacity) {
    data = new T[capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <typename T>
void DynamicArray<T>::add(const T& value) {
    if (size == capacity) {
        resize();
    }
    data[size++] = value;
}

template <typename T>
T DynamicArray<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

template <typename T>
void DynamicArray<T>::resize() {
    capacity *= 2;
    T* newData = new T[capacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

#endif // DYNAMICARRAY_H
