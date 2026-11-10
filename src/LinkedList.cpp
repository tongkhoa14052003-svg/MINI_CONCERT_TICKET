
#include "LinkedList.h"

#include <iostream>

Node::Node(const Product& product)
    : data(product), next(nullptr) {
}

LinkedList::LinkedList()
    : head(nullptr), tail(nullptr), count(0) {
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::addFront(const Product& product) {
    Node* newNode = new Node(product);

    newNode->next = head;
    head = newNode;

    if (tail == nullptr) {
        tail = newNode;
    }

    ++count;
}

void LinkedList::addBack(const Product& product) {
    Node* newNode = new Node(product);

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    ++count;
}

bool LinkedList::removeById(int id) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data.id == id) {
            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }

            if (current == tail) {
                tail = previous;
            }

            delete current;
            --count;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

Product* LinkedList::findById(int id) {
    Node* current = head;

    while (current != nullptr) {
        if (current->data.id == id) {
            return &current->data;
        }

        current = current->next;
    }

    return nullptr;
}

const Product* LinkedList::findById(int id) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->data.id == id) {
            return &current->data;
        }

        current = current->next;
    }

    return nullptr;
}

void LinkedList::display(int limit) const {
    std::cout << "\nDANH SACH VE CA NHAC\n";

    std::cout << std::left
              << "ID       TEN VE"
              << "                                 GIA"
              << "              TON"
              << "   RATING\n";

    Node* current = head;
    int displayed = 0;

    while (current != nullptr && displayed < limit) {
        displayProduct(current->data);

        current = current->next;
        ++displayed;
    }

    std::cout << "Tong so ve trong danh sach: "
              << count << '\n';
}

int LinkedList::size() const {
    return count;
}

bool LinkedList::isEmpty() const {
    return head == nullptr;
}

void LinkedList::clear() {
    Node* current = head;

    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    tail = nullptr;
    count = 0;
}
