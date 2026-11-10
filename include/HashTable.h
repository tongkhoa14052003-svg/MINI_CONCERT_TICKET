
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Product.h"

#include <vector>
#include <string>

class HashTable {
private:
    struct HashNode {
        Product data;
        HashNode* next;

        HashNode(const Product& product);
    };

    // Khai báo capacity trước table
    // để đảm bảo thứ tự khởi tạo chính xác
    int capacity;
    std::vector<HashNode*> table;

    int hashFunction(const std::string& key) const;

public:
    explicit HashTable(int size = 1009);

    ~HashTable();

    // Không cho phép sao chép bảng băm
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    // Thêm vé vào bảng băm
    void insert(const Product& product);

    // Tìm vé theo tên
    std::vector<Product> search(
        const std::string& name
    ) const;

    // Xóa vé theo ID
    bool remove(int id);

    // Lấy kích thước bảng băm
    int getCapacity() const;

    // Đếm tổng số vé
    int countItems() const;

    // Xóa toàn bộ dữ liệu
    void clear();
};

#endif
