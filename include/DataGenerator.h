
#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <vector>
#include <string>
#include "Product.h"

std::vector<Product> generateProducts(int count);

bool saveProductsToCSV(
    const std::vector<Product>& products,
    const std::string& filename
);

#endif
