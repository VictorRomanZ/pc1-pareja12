#include <iostream>
#include <vector>
#include <cassert>
#include "../src/solution.hpp"

void run_tests() {
    // Test 1: Caso normal
    {
        std::vector<int> nums = {1, 2, 3, 4};
        std::vector<int> expected = {24, 12, 8, 6};
        
        assert(productExceptSelf(nums) == expected && "Fallo en Test 1 Optimo");
        assert(productExceptSelfNaive(nums) == expected && "Fallo en Test 1 Ingenuo");
    }

    // Test 2: Caso borde con un cero 
    {
        std::vector<int> nums = {-1, 1, 0, -3, 3};
        std::vector<int> expected = {0, 0, 9, 0, 0};
        
        assert(productExceptSelf(nums) == expected && "Fallo en Test 2");
    }

    // Test 3: Caso extremo con multiples ceros
    {
        std::vector<int> nums = {0, 4, 0};
        std::vector<int> expected = {0, 0, 0};
        
        assert(productExceptSelf(nums) == expected && "Fallo en Test 3");
    }

    std::cout << "¡Todos los tests pasaron exitosamente!\n";
}

int main() {
    run_tests();
    return 0;
}