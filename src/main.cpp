#include <iostream>
#include <vector>
#include "solution.hpp"

static void printVector(const std::vector<int>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4};
    std::vector<int> result = productExceptSelf(nums);

    std::cout << "Entrada: ";
    printVector(nums);
    std::cout << "\nSalida: ";
    printVector(result);
    std::cout << "\n";

    return 0;
}
