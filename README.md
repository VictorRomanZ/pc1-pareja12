# Práctica Calificada 1 - Estructuras de Datos y Algoritmos

## Datos Generales
* **Integrantes:** Roman Zela Victor Ducante y Montoya Dulanto Alvaro Raul
* **Problema asignado:** 12. Product of Array Except Self (LeetCode 238)
* **Enlace al enunciado:** [LeetCode - Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/)

## 1. Especificación del Problema
* **Especificación breve:** El problema nos da un arreglo de números y nos pide devolver otro arreglo donde cada posición tenga el producto de todos los números, menos el de esa misma posición. La condición fuerte es que tiene que correr en tiempo $O(n)$ y está prohibido usar división.
* **Entrada:** Un vector de enteros que pasamos por referencia constante `const std::vector<int>& nums` para no hacer copias innecesarias en memoria.
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
* **Robustez y Casos Borde:** El código aguanta bien los casos raros. Si hay un cero, anula todo menos su posición. Si hay varios ceros, todo el arreglo se vuelve cero automáticamente. El uso de `static_cast<int>` garantiza robustez frente a advertencias del compilador.
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
| Build | Bandera | Tiempo Naive O(n^2) | Tiempo Óptimo O(n) |
| :--- | :--- | :--- | :--- |
| Depuración | -O0 | 1411.51 ms | 0.3976 ms |
| Release | -O2 | 404.121 ms | 0.0724 ms |
| Compacto | -Os | 421.871 ms | 0.1332 ms |

* **Observaciones de Compilación:** Con la bandera -O2, la versión ingenua mejoró muchísimo su tiempo (bajó de 1411 ms a 404 ms por optimizaciones internas del compilador), pero aún así, nuestra versión óptima incluso en -O0 (sin optimizar nada, 0.39 ms) es inmensamente superior. La bandera -Os priorizó reducir el peso del archivo, por lo que fue ligeramente más lenta que -O2.
* **Sanitizers:** Al verificar el programa con -fsanitize=address,undefined, no hubo alertas ni errores de memoria. Confirmamos que no hay fugas (memory leaks) y no nos salimos de los límites del vector.
* **Cobertura (Coverage):** Usamos la herramienta gcov y confirmamos que nuestros tests evalúan el 100% de las líneas y ramas de nuestro algoritmo. No quedó código muerto sin probar.
* **Profiling:** Con gprof vimos empíricamente que el programa se pasa casi el 99.9% del tiempo ejecutando la función ingenua. Esto es porque $O(n^2)$ pesa muchísimo más que $O(n)$ cuando la entrada es grande.
* **Microoptimización vs Algoritmo:** Este experimento demuestra empíricamente que pensar en un buen diseño asintótico ($O(n)$) es infinitamente mejor que solo pedirle al compilador que arregle un mal código ($O(n^2)$).

## 7. Herramientas de IA y Trabajo Colaborativo
* **Live Share:** Se utilizó la extensión Live Share de VS Code para el desarrollo simultáneo. Mientras un integrante estructuraba los prototipos y el `CMakeLists.txt`, el otro escribía las pruebas unitarias, agilizando el flujo de trabajo y permitiendo la revisión de código en tiempo real.
* **Validación del uso de GitHub Copilot:**
  * **Sugerencia Aceptada:**
    - Copilot sugirió la firma de la función y la inicialización del vector:
      ```cpp
      std::vector<int> answer(n, 1);
      ```
    - También propuso la estructura básica de los bucles `for`, lo cual fue aceptado porque sigue buenas prácticas y evita errores de índices.  
  * **Sugerencia Rechazada:**
    - Copilot sugirió una solución usando división:
      ```cpp
      answer[i] = totalProduct / nums[i];
      ```
    - Esta sugerencia fue rechazada porque el problema prohíbe el uso de división y además falla en presencia de ceros.
    - También se rechazó el uso de dos arreglos auxiliares ('left' y 'right') porque aumenta el uso de memoria a O(n), mientras que nuestra solución usa O(1)             auxiliar.
* **Construcción del código:**
  * Primero se planteó una solución ingenua O(n²), usando dos bucles anidados para multiplicar todos los elementos excepto el actual.
  * Luego se identificó que había cálculos repetidos innecesarios.
  * Se diseñó una solución óptima O(n) basada en:
    - Productos prefijo (izquierda)
    - Productos sufijo (derecha)
  * Se implementó en dos pasadas:
    - Primera pasada: se guardan los productos acumulados a la izquierda.
    - Segunda pasada: se multiplica por los productos acumulados a la derecha usando una variable auxiliar `suffix`.
  * Finalmente, se optimizó el uso de memoria evitando arreglos adicionales y manteniendo solo una variable auxiliar.

