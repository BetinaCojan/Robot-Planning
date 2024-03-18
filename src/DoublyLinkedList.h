/**
 * Deque implementation via Doubly Linked List
 * Elements can be added and deleted 
 * from the beginning and from the end of the queue
 */

#ifndef __DOUBLYLINKEDLIST_H__
#define __DOUBLYLINKEDLIST_H__

#include <assert.h>
#include <iostream>

template <typename T>
struct Node {
    T data;
    Node<T> *next;
    Node<T> *prev;

    Node(T data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int numElements;

public:
    /**
     * Returns the pos'th node in the list.
     */
    Node<T> *goToPos(int pos) {
        int count = 0;
        Node<T> *temp = head;

        while (count != pos) {
            temp = temp->next;
            count++;
        }
        return temp;
    }

    // Constructor
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        numElements = 0;
    }

    // Another constructor
    DoublyLinkedList(Node<T> *head) {
        this->head = head;
        while (head != nullptr) {
            numElements++;
            head = head->next;
        }
    }

    // Destructor
    ~DoublyLinkedList() {
        Node<T> *temp = head;
        while(temp != nullptr) {
            Node<T> *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        head = nullptr;
        tail = nullptr;
        
        numElements = 0;
    }

    /**
     * Adds a new node at the end of the list.
     *
     * @param data Data to be added at the end of the list.
     */
    void addLast(T data) {
        Node<T> *newNode = new Node<T>(data);

        if (isEmpty()) {

            head = newNode;

        } else {

            tail->next = newNode;
            newNode->prev = tail;

        }

        tail = newNode;
        numElements++;
        
    }

    /**
     * Adds a new node at the beginning of the list.
     *
     * @param data Data to be added at the beginning of the list.
     */
    void addFirst(T data) {
        Node<T> *newNode = new Node<T>(data);

        if (isEmpty()) {

            tail = newNode;

        } else {

            head->prev = newNode;
            newNode->next = head;

        } 

        head = newNode;
        numElements++;
    }

    /**
     * Removes the last node of the list.
     *
     * @return Value stored in the last node of the list.
     */
    T removeLast() {
        Node<T>* temp;
        T dataRemoved;

        // check if the list is empty
        if (isEmpty()) {
            
            std::cerr << "The list is empty";

        } else if (tail != nullptr) {
            dataRemoved = tail->data;

            if (tail->prev != nullptr) {

                temp = tail->prev;
                temp->next = nullptr;
                tail->prev = nullptr;
                delete tail;
                tail = temp;

            } else {

                delete tail;

            }

            numElements--;

        } 

        temp = nullptr;
        return dataRemoved;

    }

    /**
     * Removes the first node of the list.
     *
     * @return Value stored in the first node of the list.
     */
    T removeFirst() {
        Node<T> *temp;
        T removedData;

        // check if the list is empty
        if(isEmpty()) {
            std::cerr << "The list is empty";

        } else if (head != nullptr) {

            removedData = head->data;

            if (head->next != nullptr) {

                temp = head->next;
                head->next = nullptr;
                temp->prev = nullptr;
                delete head;
                head = temp;

            } else {

                delete head;

            }

            numElements--;

        } 

        //temp = nullptr;
        return removedData;
    }

    /**
     * Check if the list contains any elements.
     *
     * @return True if the list contains no elements, False otherwise.
     */
    bool isEmpty() {
        return (head == nullptr);
    }

    /**
     * Get the number of nodes in the list.
     *
     * @return The number of nodes stored in the list.
     */
    int size() {
        return numElements;
    }

    // Getters & Setters
    Node<T> *getHead() {
        return head;
    }

    Node<T> *getTail() {
        return tail;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os,
            DoublyLinkedList<U>& list);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T>& list) {
    Node<T> *it = list.getHead();

    if (list.size() > 0) {
        os << "[ ";
        while (it->next != nullptr) {
            os << it->data << " <-> ";
            it = it->next;
        }

        os << it->data;
        os << " ]";
    } else {
        os << "[]";
    }

    return os;
}

#endif // __DOUBLYLINKEDLIST_H__