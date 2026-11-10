#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <limits>

#include "Product.h"
#include "DataGenerator.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "BST.h"
#include "HashTable.h"
#include "SearchHistory.h"
#include "Sorting.h"
#include "Cart.h"
#include "Order.h"

using namespace std;

// Tim san pham theo ma trong vector
Product* findProduct(
    vector<Product>& products,
    int id
) {
    for (Product& product : products) {
        if (product.id == id) {
            return &product;
        }
    }

    return nullptr;
}

// Hien thi danh sach san pham
void displayProducts(
    const vector<Product>& products,
    int limit = 20
) {
    cout << "\n========== DANH SACH VE CA NHAC ==========\n";

    cout << "ID       TEN VE"
         << "                                 GIA"
         << "              TON"
         << "   RATING\n";

    int displayed = 0;

    for (const Product& product : products) {
        if (displayed >= limit) {
            break;
        }

        displayProduct(product);
        ++displayed;
    }

    cout << "Tong so ve: " << products.size() << '\n';
}

// Hien thi menu
void showMenu() {
    cout << "\n";
    cout << "============================================\n";
    cout << "       MINI CONCERT TICKET SYSTEM\n";
    cout << "          HE THONG BAN VE CA NHAC\n";
    cout << "============================================\n";

    cout << "1. Hien thi danh sach ve\n";
    cout << "2. Tim kiem ve theo ma bang BST\n";
    cout << "3. Tim kiem ve theo ten bang Hash Table\n";
    cout << "4. Sap xep ve theo gia\n";
    cout << "5. Them ve vao gio hang\n";
    cout << "6. Xem gio hang\n";
    cout << "7. Xoa ve khoi gio hang\n";
    cout << "8. Hoan tac thao tac xoa\n";
    cout << "9. Thanh toan va tao don hang\n";
    cout << "10. Xu ly don hang tiep theo\n";
    cout << "11. Xem lich su tim kiem\n";
    cout << "12. Thong ke du lieu va benchmark\n";
    cout << "13. Tim kiem ve theo ma bang Binary Search\n";
    cout << "0. Thoat chuong trinh\n";

    cout << "============================================\n";
    cout << "Nhap lua chon: ";
}

// Kiem tra mang da sap xep tang dan theo gia chua
bool isSortedByPrice(const vector<Product>& products) {
    for (size_t i = 1; i < products.size(); ++i) {
        if (products[i].price < products[i - 1].price) {
            return false;
        }
    }

    return true;
}

// Benchmark Selection Sort va QuickSort
void runBenchmark(const vector<Product>& products) {
    cout << "\n========== BENCHMARK ==========\n";

    cout << "So sanh tren cung mot bo du lieu.\n";
    cout << "Tong so phan tu: " << products.size() << '\n';

    // Hai ban sao cung lay tu mot bo du lieu goc
    vector<Product> selectionData = products;
    vector<Product> quickData = products;

    // Selection Sort
    cout << "\nDang chay Selection Sort...\n";
    cout << "Luu y: Selection Sort voi 100.000 phan tu "
         << "co the mat nhieu thoi gian.\n";

    auto startSelection = chrono::high_resolution_clock::now();

    selectionSort(selectionData, SortField::PRICE);

    auto endSelection = chrono::high_resolution_clock::now();

    double selectionTime =
        chrono::duration<double, milli>(
            endSelection - startSelection
        ).count();

    // QuickSort
    cout << "\nDang chay QuickSort...\n";

    auto startQuick = chrono::high_resolution_clock::now();

    quickSort(quickData, SortField::PRICE);

    auto endQuick = chrono::high_resolution_clock::now();

    double quickTime =
        chrono::duration<double, milli>(
            endQuick - startQuick
        ).count();

    cout << "\n========== KET QUA BENCHMARK ==========\n";

    cout << "Selection Sort:\n";
    cout << "So phan tu: " << selectionData.size() << '\n';
    cout << "Thoi gian: " << selectionTime << " ms\n";
    cout << "Do phuc tap: O(n^2)\n";

    cout << "\nQuickSort:\n";
    cout << "So phan tu: " << quickData.size() << '\n';
    cout << "Thoi gian: " << quickTime << " ms\n";
    cout << "Do phuc tap trung binh: O(n log n)\n";

    cout << "\nKiem tra ket qua:\n";

    if (isSortedByPrice(selectionData) &&
        isSortedByPrice(quickData)) {
        cout << "Ca hai thuat toan sap xep dung theo gia tang dan.\n";
    } else {
        cout << "Phat hien ket qua sap xep khong chinh xac.\n";
    }

    if (quickTime > 0) {
        cout << "\nQuickSort nhanh hon Selection Sort khoang: "
             << selectionTime / quickTime << " lan (theo thoi gian do).\n";
    }

    cout << "\nLuu y: Ket qua thoi gian co the thay doi "
         << "theo cau hinh may tinh.\n";

    cout << "========================================\n";
}

// Tim kiem Binary Search
void runBinarySearch(vector<Product>& products) {
    int id;

    cout << "\n========== BINARY SEARCH ==========\n";
    cout << "Nhap ma ve can tim: ";

    if (!(cin >> id)) {
        cout << "Ma ve khong hop le.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    // Tao ban sao va sap xep tang dan theo ID
    vector<Product> sortedById = products;

    sort(
        sortedById.begin(),
        sortedById.end(),
        [](const Product& a, const Product& b) {
            return a.id < b.id;
        }
    );

    Product* result = binarySearchById(sortedById, id);

    if (result != nullptr) {
        cout << "\nTim thay ve:\n";
        displayProduct(*result);
    } else {
        cout << "Khong tim thay ve co ma " << id << ".\n";
    }

    cout << "Do phuc tap tim kiem: O(log n).\n";
    cout << "Luu y: Can O(n log n) de sap xep du lieu truoc khi tim "
         << "neu danh sach chua duoc sap xep.\n";

    cout << "===================================\n";
}

int main() {
    cout << "Dang khoi tao he thong...\n";

    // 1. Tao 100.000 ve ca nhac
    const int PRODUCT_COUNT = 100000;

    vector<Product> products = generateProducts(PRODUCT_COUNT);

    if (products.empty()) {
        cout << "Khong tao duoc du lieu san pham.\n";
        return 1;
    }

    // 2. Luu du lieu vao file CSV
    if (saveProductsToCSV(products, "data/products.csv")) {
        cout << "Da luu du lieu vao data/products.csv\n";
    } else {
        cout << "Khong the luu file CSV.\n";
    }

    // 3. Khoi tao Linked List
    cout << "Dang tao Linked List...\n";

    LinkedList productList;

    for (const Product& product : products) {
        productList.addBack(product);
    }

    // 4. Khoi tao BST
    cout << "Dang tao Binary Search Tree...\n";

    BST productTree;

    vector<Product> shuffledProducts = products;

    mt19937 rng(random_device{}());

    shuffle(
        shuffledProducts.begin(),
        shuffledProducts.end(),
        rng
    );

    for (const Product& product : shuffledProducts) {
        productTree.insert(product);
    }

    // 5. Khoi tao Hash Table
    cout << "Dang tao Hash Table...\n";

    HashTable productHash(200003);

    for (const Product& product : products) {
        productHash.insert(product);
    }

    // 6. Khoi tao cac chuc nang khac
    SearchHistory searchHistory;
    Cart cart;
    Queue orderQueue;

    int nextOrderId = 1001;

    cout << "\nKhoi tao thanh cong!\n";
    cout << "Tong so ve: " << products.size() << '\n';

    int choice;

    do {
        showMenu();

        if (!(cin >> choice)) {
            cout << "Vui long nhap mot so hop le.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            continue;
        }

        switch (choice) {

        case 1: {
            displayProducts(products, 20);
            break;
        }

        case 2: {
            int id;

            cout << "Nhap ma ve can tim: ";

            if (!(cin >> id)) {
                cout << "Ma ve khong hop le.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            Product* result = productTree.search(id);

            if (result != nullptr) {
                cout << "\nTim thay ve:\n";
                displayProduct(*result);

                searchHistory.recordSearch(
                    "Ma ve: " + to_string(id)
                );
            } else {
                cout << "Khong tim thay ve.\n";
            }

            break;
        }

        case 3: {
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            string name;

            cout << "Nhap ten su kien va loai ve: ";
            getline(cin, name);

            vector<Product> results =
                productHash.search(name);

            if (results.empty()) {
                cout << "Khong tim thay ve phu hop.\n";
            } else {
                cout << "\nKet qua tim kiem:\n";

                for (const Product& product : results) {
                    displayProduct(product);
                }

                searchHistory.recordSearch(name);
            }

            break;
        }

        case 4: {
            vector<Product> sortedProducts = products;

            quickSort(
                sortedProducts,
                SortField::PRICE
            );

            cout << "\nDANH SACH VE SAP XEP THEO GIA TANG DAN\n";

            cout << "ID       TEN VE"
                 << "                                 GIA"
                 << "              TON"
                 << "   RATING\n";

            int limit = min(
                static_cast<int>(sortedProducts.size()),
                20
            );

            for (int i = 0; i < limit; ++i) {
                displayProduct(sortedProducts[i]);
            }

            break;
        }

        case 5: {
            int id;
            int quantity;

            cout << "Nhap ma ve: ";

            if (!(cin >> id)) {
                cout << "Ma ve khong hop le.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            cout << "Nhap so luong: ";

            if (!(cin >> quantity)) {
                cout << "So luong khong hop le.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            Product* product = findProduct(products, id);

            if (product == nullptr) {
                cout << "Khong tim thay ma ve.\n";
            } else if (cart.addProduct(*product, quantity)) {
                cout << "Da them ve vao gio hang.\n";
            } else {
                cout << "Khong the them ve. "
                     << "Hay kiem tra so luong ton kho.\n";
            }

            break;
        }

        case 6: {
            cart.display();
            break;
        }

        case 7: {
            int id;

            cout << "Nhap ma ve can xoa: ";

            if (!(cin >> id)) {
                cout << "Ma ve khong hop le.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            if (cart.removeProduct(id)) {
                cout << "Da xoa ve. "
                     << "Ban co the hoan tac thao tac nay.\n";
            } else {
                cout << "Khong tim thay ve trong gio hang.\n";
            }

            break;
        }

        case 8: {
            if (cart.undoLastRemoval()) {
                cout << "Da khoi phuc ve vua xoa.\n";
            } else {
                cout << "Khong co thao tac xoa de hoan tac.\n";
            }

            break;
        }

        case 9: {
            if (cart.isEmpty()) {
                cout << "Gio hang dang trong.\n";
                break;
            }

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            string customerName;

            cout << "Nhap ten khach hang: ";
            getline(cin, customerName);

            if (customerName.empty()) {
                cout << "Ten khach hang khong duoc de trong.\n";
                break;
            }

            Order order = cart.checkout(
                nextOrderId,
                customerName
            );

            bool enoughStock = true;

            for (const OrderItem& item : order.items) {
                Product* product = findProduct(
                    products,
                    item.product.id
                );

                if (product == nullptr ||
                    product->stock < item.quantity) {
                    enoughStock = false;
                    break;
                }
            }

            if (!enoughStock) {
                cout << "Ton kho khong du. "
                     << "Khong the tao don hang.\n";
                break;
            }

            for (const OrderItem& item : order.items) {
                Product* product = findProduct(
                    products,
                    item.product.id
                );

                product->stock -= item.quantity;
            }

            orderQueue.enqueue(order);

            displayOrder(order);

            ++nextOrderId;

            cart.clear();

            cout << "Tao don hang thanh cong!\n";
            cout << "Don hang da duoc dua vao hang doi FIFO.\n";

            break;
        }

        case 10: {
            Order order;

            if (orderQueue.dequeue(order)) {
                order.status = "Da xu ly";

                cout << "\nDang xu ly don hang:\n";
                displayOrder(order);
            } else {
                cout << "Khong co don hang dang cho.\n";
            }

            break;
        }

        case 11: {
            searchHistory.display();
            break;
        }

        case 12: {
            cout << "\n========== THONG KE HE THONG ==========\n";

            cout << "Tong so san pham: "
                 << products.size() << '\n';

            cout << "So node Linked List: "
                 << productList.size() << '\n';

            cout << "Dung luong Hash Table: "
                 << productHash.getCapacity() << '\n';

            cout << "So phan tu Hash Table: "
                 << productHash.countItems() << '\n';

            cout << "So ve trong gio hang: "
                 << cart.getItemCount() << '\n';

            cout << "So don hang dang cho: "
                 << orderQueue.size() << '\n';

            cout << "So tu khoa trong lich su: "
                 << searchHistory.size() << '\n';

            cout << "=======================================\n";

            runBenchmark(products);

            break;
        }

        case 13: {
            runBinarySearch(products);
            break;
        }

        case 0: {
            cout << "Cam on ban da su dung he thong!\n";
            break;
        }

        default: {
            cout << "Lua chon khong hop le. "
                 << "Vui long chon lai.\n";
            break;
        }

        }

    } while (choice != 0);

    return 0;
}