cmake_minimum_required(VERSION 3.22)
project(PC1_Algoritmos LANGUAGES CXX)

# Obligar a usar C++17 como pide el curso
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1. Empaquetar tu algoritmo en una librería interna
add_library(solution_lib src/solution.cpp)
# Activar las advertencias obligatorias del profesor
target_compile_options(solution_lib PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(solution_lib PUBLIC src)

# 2. Construir el ejecutable principal (main.cpp)
add_executable(main_app src/main.cpp)
target_link_libraries(main_app PRIVATE solution_lib)

# 3. Construir el ejecutable de Pruebas (tests.cpp)
add_executable(run_tests tests/tests.cpp)
target_link_libraries(run_tests PRIVATE solution_lib)

# 4. Construir el ejecutable de Benchmark (benchmark.cpp)
add_executable(run_bench bench/benchmark.cpp)
target_link_libraries(run_bench PRIVATE solution_lib)