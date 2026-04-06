# Práctica Calificada 1 - Estructuras de Datos y Algoritmos

## Datos Generales
* **Integrantes:** Roman Zela Victor Ducante y Montoya Dulanto Alvaro Raul
* **Problema asignado:** 12. Product of Array Except Self (LeetCode 238)
* **Enlace al enunciado:** [LeetCode - Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/)

## 1. Especificación del Problema
* **Especificación breve:** El problema nos da un arreglo de números y nos pide devolver otro arreglo donde cada posición tenga el producto de todos los números, menos el de esa misma posición. La condición fuerte es que tiene que correr en tiempo $O(n)$ y está prohibido usar división.
* **Entrada:** Un vector de enteros que pasamos por referencia constante`const std::vector<int>& nums` para no hacer copias innecesarias en memoria.
* **Salida:** Un vector de enteros `std::vector<int>` con los productos calculados.
* **Tamaño de entrada relevante:** $n$, donde $n$ es la cantidad de elementos en el arreglo `nums` (hasta $10^5$). Se procesa mediante `static_cast<int>(nums.size())` para evitar advertencias de signo.

## 2. Análisis Algorítmico
* **Descripción de la solución:** Nuestra solución usa la idea de guardar prefijos y sufijos. Hacemos dos pasadas con bucles `for`. En la primera (de izquierda a derecha), guardamos el producto de los números anteriores en nuestro vector de respuesta. En la segunda (de derecha a izquierda), calculamos el producto de los números que están a la derecha usando una variable simple y lo multiplicamos por lo que ya habíamos guardado.
* **Determinismo:** El algoritmo es estrictamente determinista. Si le pasamos el mismo arreglo `nums`, siempre va a dar exactamente el mismo resultado porque no dependemos de nada aleatorio ni variables globales.
* **Factibilidad:** Es factible porque hacer dos bucles `for` separados toma un tiempo lineal, así que el programa no va a dar Time Limit Exceeded (TLE), incluso si el arreglo tiene $10^5$ elementos.
* **Finitud:** El programa siempre termina. Solo tenemos dos bucles `for` que van de `0` a `n-1` y de regreso. Como `n` es un número fijo, es imposible que se quede atrapado en un bucle infinito.
* **Argumento de correctitud:** Funciona porque al multiplicar todo lo que está a la izquierda de un número por todo lo que está a su derecha, obtenemos el producto de todo el arreglo sin tocar ese número en específico. Así evitamos usar la división.
* **Invariante:** En el primer bucle, justo antes de actualizar la respuesta en la posición `i`, nuestra variable `left_product` tiene guardado el producto exacto de todos los elementos desde la posición `0` hasta la `i-1`.
* **Monotonicidad:** Los índices de nuestros bucles avanzan de uno en uno, siempre creciendo en la primera pasada y siempre decreciendo en la segunda.

## 3. Complejidad y Eficiencia
* **Complejidad Temporal:** $O(n)$ - Solo recorremos el arreglo completo dos veces.
* **Complejidad Espacial:** $O(1)$ auxiliar - Sin contar el arreglo de respuesta (que el problema dice que no cuenta para la memoria), solo estamos creando un par de variables tipo `int`.
* **Mejor, Peor y Caso Promedio:** Para los tres casos, la complejidad temporal es exactamente $\Theta(n)$. El algoritmo siempre recorre todo el arreglo sin importar los valores.
* **Jerarquía de crecimiento:** Crecimiento Lineal $O(n)$.
* **Alternativa Ingenua o menos eficiente:** La función `productExceptSelfNaive` es nuestra versión a la fuerza bruta. Usa dos `for` anidados para multiplicar todo saltándose la posición actual. Eso nos da un tiempo cuadrático de $O(n^2)$, que es ineficiente para arreglos grandes.

## 4. Diseño e Ingeniería
* **Robustez y Casos Borde:** El código aguanta bien los casos raros. Si hay un cero, anula todo menos su posición. Si hay varios ceros, todo el arreglo se vuelve cero automáticamente.. El uso de `static_cast<int>` garantiza robustez frente a advertencias del compilador.
* **Degeneración:** Esta solución no tiene riesgo de degenerar. Su rendimiento es constante e inamovible frente a cualquier distribución de datos (ordenados, inversos, ceros, negativos).
* **Reutilización:** Pusimos la lógica en funciones separadas (`standalone`) dentro de un `solution.hpp`. Es mucho más limpio así y nos sirvió bastante para poder llamar a las funciones desde los tests y el benchmark sin tener que estar copiando y pegando código.

## 5. Instrucciones
Para reproducir los experimentos, se requiere CMake y un compilador compatible con C++17.

* **Compilar:**
  ```bash
  mkdir build
  cd build
  cmake ..
  cmake --build .
* **Ejecutar Pruebas:**  ./run_tests
* **Ejecutar Benchmark:**  ./run_bench
  
## 6. Reporte Experimental
* **Benchmark Realizado:** Comparamos el tiempo que le toma a la solución a fuerza bruta contra nuestra solución óptima usando `<chrono>`. Para que de verdad se note la diferencia asintótica, llenamos un vector con 20,000 números.

**Tabla Resumida de Builds y Resultados**
| Build | Bandera | Tiempo Naive O(n^2) | Tiempo Óptimo O(n) | Tamaño Ejecutable |
| :--- | :--- | :--- | :--- | :--- |
| Depuración | -O0 | ~452.3 ms | ~0.15 ms | ~142 KB |
| Depurable Opt. | -Og | ~185.1 ms | ~0.08 ms | ~118 KB |
| Release | -O2 | ~58.4 ms | ~0.02 ms | ~76 KB |
| Compacto | -Os | ~65.2 ms | ~0.03 ms | ~58 KB |

* **Observaciones de Compilación:** Con la bandera -O2, la versión mala mejoró bastante su tiempo, pero aún así, nuestra versión óptima incluso en -O0 (sin optimizar nada) es superior. La bandera -Os hizo que el ejecutable pese un poco menos, como esperábamos.
* **Sanitizers:** Al correr el programa con `-fsanitize=address,undefined`, no hubo errores de compilación (Exit Code 0). Cero fugas de memoria y no nos salimos de los límites del vector.
* **Cobertura (Coverage):** Usamos `--coverage` y confirmamos que nuestros tests pasan por el 100% de las líneas de nuestro algoritmo. No dejamos código inalcanzable.
* **Profiling:** Con `gprof` vimos empíricamente que el programa se pasa casi el 99% del tiempo ejecutando la función ingenua. Esto es porque $O(n^2)$ pesa muchísimo más que O(n) cuando la entrada es grande.
* **Microoptimización vs Algoritmo:** Este experimento demuestra que pensar en un buen algoritmo es mejor que solo ponerle `-O3` al compilador para intentar arreglar un código lento.

## 7. Herramientas de IA y Trabajo Colaborativo
* **Live Share:** Se utilizó la extensión Live Share de VS Code para el desarrollo simultáneo. Mientras un integrante estructuraba los prototipos y el `CMakeLists.txt`, el otro escribía las pruebas unitarias, agilizando el flujo de trabajo y permitiendo la revisión de código en tiempo real.
* **Validación del uso de GitHub Copilot:**
  * **Sugerencia Aceptada:** 
  * **Sugerencia Rechazada:**