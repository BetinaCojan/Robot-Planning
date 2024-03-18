/**
 * Stack implementation via Resizable Array
 * Elements can be added or deleted only from the end of the stack
 * The list can be resized if needed
 */

#ifndef __RESIZABLEARRAY_H__
#define __RESIZABLEARRAY_H__

#include <assert.h>
#include <iostream>

template <typename T>
class ResizableArray {
private:
    int defaultCapacity;
    int expandFactor;

    int numElements;
    int maxCapacity;
    T *data;

public:
    // Constructor
    ResizableArray() {
        numElements = 0;
        maxCapacity = defaultCapacity;

        defaultCapacity = 5;
        expandFactor = 2;

        data = new T[maxCapacity];
    }

    // Another constructor
    ResizableArray(int initialCapacity) {
        numElements = 0;
        maxCapacity = initialCapacity;

        defaultCapacity = 5;
        expandFactor = 2;

        data = new T[maxCapacity];
    }

    // Another constructor
    ResizableArray(int initialCapacity, int defaultFactor) {
        numElements = 0;
        maxCapacity = initialCapacity;
        expandFactor = defaultFactor;

        defaultCapacity = 5;
        expandFactor = 2;

        data = new T[maxCapacity];
    }

    // Destructor
    ~ResizableArray() {
        delete[] data;
    }

    /**
     * Adds the specified element at the end of the array.
     *
     * @param element Element to be added at the end of the array.
     */
    void addLast(T element) {

        // check if it will exceed the maximum capacity
        if(numElements >= maxCapacity) {
            resizeArray(maxCapacity * expandFactor);
        } 

        data[numElements] = element;
        numElements++;
    }

    /**
     * Removes and returns the last element of the array.
     *
     * @return Value of the last element stored in the array.
     */
    T removeLast() {
        T lastElement;

        if (isEmpty()) {
            std::cerr << "The list is empty";
        } else {
            lastElement = data[numElements - 1];
            numElements--;

            // Reducing the capacity when the array is less than half full
            int halfCapacity = maxCapacity / 2;
            if (halfCapacity >= defaultCapacity && halfCapacity > numElements) {
                resizeArray(halfCapacity);
            }
        
        }
        return lastElement;
    }

    /**
     * Checks if the array contains any elements.
     *
     * @return True if the array contains no elements, False otherwise.
     */
    bool isEmpty() {
        return (numElements == 0);
    }

    /**
     * Returns the number of elements in the array.
     *
     * @return The number of elements stored in the array.
     */
    int size() {
        return numElements;
    }

    /**
     * Resize the array to a larger/smaller capacity
     * 
     */
    void resizeArray(int newCapacity) {
        // Create a new array with the updated capacity
        T *newData = new T[newCapacity];

        // Copy elements from the old array to the new array
        for(int i = 0; i < numElements; i++) {
            newData[i] = data[i];
        }

        // Update maxCapacity and data pointer
        maxCapacity = newCapacity;
        delete[] data;
        data = newData;

    }

    /**
     * Returns the last element of the array without removing it.
     * Peek implementation
     *
     * @return Reference to the last element stored in the array.
     */
    T& getLast() {
        if(isEmpty()) {
            std::cerr << "The list is empty";
        }
        return data[numElements - 1];
    }

    // Getters & Setters
    T *getData() {
        return data;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os,
            const ResizableArray<U>& ra);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, ResizableArray<T>& ra) {
    os << "[ ";
    for (int i = 0; i < ra.size(); i++) {
        os << (ra.getData())[i] << " ";
    }
    os << "]";

    return os;
}

#endif // __RESIZABLEARRAY_H__
