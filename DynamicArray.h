// DynamicArray.h
// A simple implementation of a dynamic array class template.
// Provides dynamic resizing and basic operations like adding elements and retrieving them by index.

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdexcept> // For std::out_of_range exception.

template <typename T>
class DynamicArray {
private:
    T* data;        // Pointer to the underlying array.
    int size;       // Current number of elements in the array.
    int capacity;   // Maximum number of elements the array can hold before resizing.

    // Resizes the array when its capacity is reached.
    // This method doubles the capacity and transfers existing elements to a new array.
    void resize();

public:
    // Constructor: Initializes the array with a given initial capacity (default is 2).
    DynamicArray(int initialCapacity = 2);

    // Destructor: Frees the memory allocated for the array.
    ~DynamicArray();

    // Adds a new element to the end of the array.
    void add(const T& value);

    // Retrieves the element at the specified index.
    // Throws std::out_of_range if the index is invalid.
    T get(int index) const;

    // Returns the current number of elements in the array.
    int getSize() const;
};

// Constructor: Allocates memory for the array and initializes its size and capacity.
template <typename T>
DynamicArray<T>::DynamicArray(int initialCapacity) : size(0), capacity(initialCapacity) {
    data = new T[capacity]; // Allocate memory for the initial capacity.
}

// Destructor: Frees the memory allocated for the array.
template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data; // Delete the dynamically allocated array.
}

// Adds a new element to the array.
// Resizes the array if the current size equals the capacity.
template <typename T>
void DynamicArray<T>::add(const T& value) {
    if (size == capacity) { // Check if resizing is needed.
        resize();
    }
    data[size++] = value; // Add the new element and increment the size.
}

// Retrieves the element at the specified index.
// Throws std::out_of_range if the index is invalid (out of bounds).
template <typename T>
T DynamicArray<T>::get(int index) const {
    if (index < 0 || index >= size) { // Check for out-of-bounds access.
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

// Returns the current number of elements in the array.
template <typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

// Resizes the array by doubling its capacity.
// Copies the elements from the old array to a new, larger array.
template <typename T>
void DynamicArray<T>::resize() {
    capacity *= 2; // Double the capacity.
    T* newData = new T[capacity]; // Allocate new memory for the larger array.
    for (int i = 0; i < size; i++) {
        newData[i] = data[i]; // Copy existing elements to the new array.
    }
    delete[] data; // Free the memory of the old array.
    data = newData; // Update the data pointer to the new array.
}

#endif // DYNAMICARRAY_H