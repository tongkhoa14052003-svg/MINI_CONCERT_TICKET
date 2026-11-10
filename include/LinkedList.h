
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Product.h"

struct Node {
    Product data;
    Node* next;

    Node(const Product& product);
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    int count;

public:
    LinkedList();
    ~LinkedList();

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void addFront(const Product& product);
    void addBack(const Product& product);
    bool removeById(int id);

    Product* findById(int id);
    const Product* findById(int id) const;

    void display(int limit = 20) const;
    int size() const;
    bool isEmpty() const;
    void clear();
};

#endif
