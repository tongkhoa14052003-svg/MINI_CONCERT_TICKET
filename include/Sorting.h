#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include "Product.h"

enum class SortField {
    PRICE,
    RATING
};

// Selection Sort: O(n^2)
void selectionSort(
    std::vector<Product>& products,
    SortField field = SortField::PRICE
);

// QuickSort: trung binh O(n log n), xau nhat O(n^2)
void quickSort(
    std::vector<Product>& products,
    SortField field = SortField::PRICE
);

// Binary Search theo ma ve.
// Dieu kien: vector phai duoc sap xep tang dan theo ID.
Product* binarySearchById(
    std::vector<Product>& products,
    int id
);

#endif