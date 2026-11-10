
#include "HashTable.h"

#include <functional>
#include <cstddef>

// Khoi tao mot nut trong bang bam
HashTable::HashNode::HashNode(const Product& product)
    : data(product),
      next(nullptr) {
}

// Khoi tao bang bam
HashTable::HashTable(int size)
    : capacity(size > 0 ? size : 1009),
      table(static_cast<std::size_t>(capacity), nullptr) {
}

// Huy bang bam
HashTable::~HashTable() {
    clear();
}

// Ham bam ten ve
int HashTable::hashFunction(const std::string& key) const {
    std::hash<std::string> hash;

    return static_cast<int>(hash(key) % capacity);
}

// Them ve vao bang bam
void HashTable::insert(const Product& product) {
    int index = hashFunction(product.name);

    HashNode* current = table[index];

    // Kiem tra ID da ton tai chua
    while (current != nullptr) {
        if (current->data.id == product.id) {
            current->data = product;
            return;
        }

        current = current->next;
    }

    // Tao nut moi
    HashNode* newNode = new HashNode(product);

    // Chen vao dau danh sach lien ket
    newNode->next = table[index];
    table[index] = newNode;
}

// Tim kiem ve theo ten
std::vector<Product> HashTable::search(
    const std::string& name
) const {
    std::vector<Product> results;

    int index = hashFunction(name);

    HashNode* current = table[index];

    while (current != nullptr) {
        if (current->data.name == name) {
            results.push_back(current->data);
        }

        current = current->next;
    }

    return results;
}

// Xoa ve theo ID
bool HashTable::remove(int id) {
    for (int i = 0; i < capacity; ++i) {
        HashNode* current = table[i];
        HashNode* previous = nullptr;

        while (current != nullptr) {
            if (current->data.id == id) {
                if (previous == nullptr) {
                    table[i] = current->next;
                } else {
                    previous->next = current->next;
                }

                delete current;

                return true;
            }

            previous = current;
            current = current->next;
        }
    }

    return false;
}

// Lay kich thuoc bang bam
int HashTable::getCapacity() const {
    return capacity;
}

// Dem tong so ve trong bang bam
int HashTable::countItems() const {
    int total = 0;

    for (int i = 0; i < capacity; ++i) {
        HashNode* current = table[i];

        while (current != nullptr) {
            ++total;
            current = current->next;
        }
    }

    return total;
}

// Xoa toan bo bang bam
void HashTable::clear() {
    for (int i = 0; i < capacity; ++i) {
        HashNode* current = table[i];

        while (current != nullptr) {
            HashNode* nextNode = current->next;

            delete current;

            current = nextNode;
        }

        table[i] = nullptr;
    }
}
