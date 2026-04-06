#include "solution.hpp"

std::vector<int> productExceptSelf(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    std::vector<int> answer(n, 1);

    // answer[i] almacenará primero el producto prefix:
    // nums[0] * nums[1] * ... * nums[i-1]
    for (int i = 1; i < n; ++i) {
        answer[i] = answer[i - 1] * nums[i - 1];
    }

    // suffix almacenará el producto de los elementos a la derecha
    int suffix = 1;
    for (int i = n - 1; i >= 0; --i) {
        answer[i] *= suffix;
        suffix *= nums[i];
    }

    return answer;
}

std::vector<int> productExceptSelfNaive(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    std::vector<int> answer(n, 1);

    for (int i = 0; i < n; ++i) {
        int product = 1;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                product *= nums[j];
            }
        }
        answer[i] = product;
    }

    return answer;
}
