
#include "DataGenerator.h"

#include <fstream>
#include <random>

std::vector<Product> generateProducts(int count) {
    std::vector<Product> products;

    if (count <= 0) {
        return products;
    }

    products.reserve(static_cast<size_t>(count));

    const std::string events[] = {
        "Live Concert Ha Noi",
        "Music Festival Sai Gon",
        "Dem Nhac Thanh Xuan",
        "Summer Music Festival",
        "Acoustic Night",
        "Rock The Stage",
        "K-Pop Music Night",
        "Vietnam Music Awards"
    };

    const std::string types[] = {
        "Standard",
        "VIP",
        "Premium"
    };

    const double prices[] = {
        350000,
        750000,
        1200000
    };

    std::mt19937 rng(42);

    std::uniform_int_distribution<int> eventDist(0, 7);
    std::uniform_int_distribution<int> typeDist(0, 2);
    std::uniform_int_distribution<int> stockDist(0, 500);
    std::uniform_int_distribution<int> ratingDist(30, 50);

    for (int i = 0; i < count; ++i) {
        int eventIndex = eventDist(rng);
        int typeIndex = typeDist(rng);

        Product p;

        p.id = 100001 + i;
        p.name = events[eventIndex] + " - " +
                 types[typeIndex];
        p.price = prices[typeIndex];
        p.stock = stockDist(rng);
        p.rating = ratingDist(rng) / 10.0;

        products.push_back(p);
    }

    return products;
}

bool saveProductsToCSV(
    const std::vector<Product>& products,
    const std::string& filename
) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    file << "ID,Name,Price,Stock,Rating\n";

    for (const Product& p : products) {
        file << p.id << ","
             << p.name << ","
             << p.price << ","
             << p.stock << ","
             << p.rating << "\n";
    }

    return static_cast<bool>(file);
}
