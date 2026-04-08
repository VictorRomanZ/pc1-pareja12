#include <iostream>
#include <vector>
#include <chrono>
#include "../src/solution.hpp"

int main() {
    // Generamos un arreglo grande n = 20,000 lleno de números 2 
    int n = 20000;
    std::vector<int> nums(n, 2); 
    
    std::cout << "--- Iniciando Benchmark (n = " << n << ") ---\n";

    // Medir solución ingenua O(n^2)
    auto start_naive = std::chrono::high_resolution_clock::now();
    productExceptSelfNaive(nums);
    auto end_naive = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_naive = end_naive - start_naive;

    // Medir solución óptima O(n)
    auto start_opt = std::chrono::high_resolution_clock::now();
    productExceptSelf(nums);
    auto end_opt = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_opt = end_opt - start_opt;

    // Imprimir los resultados
    std::cout << "Tiempo Solucion Ingenua O(n^2): " << time_naive.count() << " ms\n";
    std::cout << "Tiempo Solucion Optima O(n):  " << time_opt.count() << " ms\n";
    std::cout << "Diferencia: Optima es aprox " << (time_naive.count() / time_opt.count()) << " veces mas rapida.\n";

    return 0;
}