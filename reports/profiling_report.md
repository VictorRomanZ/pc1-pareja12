# Análisis de Rendimiento (Profiling con gprof)

## Identificación del Cuello de Botella
Utilizamos la herramienta GNU Profiler (`gprof`) para generar un perfil de ejecución de nuestro programa. Debido a la extrema eficiencia de nuestra solución óptima en sistemas Windows, el profiler registró tiempos de CPU por debajo del umbral de muestreo estándar para esa función. Sin embargo, cruzando los datos con nuestro benchmark en tiempo real, confirmamos el siguiente comportamiento asintótico:

**Distribución del Tiempo de CPU:**
* `productExceptSelfNaive(std::vector<int>&)`: Consume más del **99.9%** del tiempo total de ejecución (aprox. 1411 ms para n=20,000).
* `productExceptSelf(std::vector<int>&)`: Consume menos del **0.1%** del tiempo total de ejecución (aprox. 0.39 ms para n=20,000).

**Conclusión:**
El programa pierde la totalidad de su tiempo de vida útil atrapado dentro de los dos bucles `for` anidados de la solución ingenua. La función óptima, al ser lineal $O(n)$, elimina este cuello de botella validando nuestra estrategia de usar prefijos y sufijos.