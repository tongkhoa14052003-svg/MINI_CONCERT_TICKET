#include "Sorting.h"

#include <utility>
#include <random>

namespace {

bool isLess(
    const Product& a,
    const Product& b,
    SortField field
) {
    if (field == SortField::PRICE) {
        if (a.price != b.price) {
            return a.price < b.price;
        }
    } else {
        if (a.rating != b.rating) {
            return a.rating < b.rating;
        }
    }

    return a.id < b.id;
}

int partition(
    std::vector<Product>& products,
    int low,
    int high,
    SortField field,
    std::mt19937& rng
) {
    std::uniform_int_distribution<int> dist(low, high);

    int pivotIndex = dist(rng);

    std::swap(products[pivotIndex], products[high]);

    Product pivot = products[high];

    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (isLess(products[j], pivot, field)) {
            ++i;
            std::swap(products[i], products[j]);
        }
    }

    std::swap(products[i + 1], products[high]);

    return i + 1;
}

void quickSortRecursive(
    std::vector<Product>& products,
    int low,
    int high,
    SortField field,
    std::mt19937& rng
) {
    while (low < high) {
        int pivotIndex = partition(
            products,
            low,
            high,
            field,
            rng
        );

        if (pivotIndex - low < high - pivotIndex) {
            quickSortRecursive(
                products,
                low,
                pivotIndex - 1,
                field,
                rng
            );

            low = pivotIndex + 1;
        } else {
            quickSortRecursive(
                products,
                pivotIndex + 1,
                high,
                field,
                rng
            );

            high = pivotIndex - 1;
        }
    }
}

}

void selectionSort(
    std::vector<Product>& products,
    SortField field
) {
    int n = static_cast<int>(products.size());

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;

        for (int j = i + 1; j < n; ++j) {
            if (isLess(products[j], products[minIndex], field)) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(products[i], products[minIndex]);
        }
    }
}

void quickSort(
    std::vector<Product>& products,
    SortField field
) {
    if (products.size() < 2) {
        return;
    }

    std::mt19937 rng(std::random_device{}());

    quickSortRecursive(
        products,
        0,
        static_cast<int>(products.size()) - 1,
        field,
        rng
    );
}

// Binary Search theo ID
// Yeu cau vector da duoc sap xep tang dan theo ID.
Product* binarySearchById(
    std::vector<Product>& products,
    int id
) {
    int left = 0;
    int right = static_cast<int>(products.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (products[mid].id == id) {
            return &products[mid];
        }

        if (products[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return nullptr;
}