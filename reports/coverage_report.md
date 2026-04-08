# Reporte de Cobertura de Pruebas (gcov)

## 1. Herramienta Utilizada
Para medir la cobertura de nuestras pruebas automatizadas, utilizamos la herramienta `gcov` incluida con el compilador GCC.

## 2. Resultados Obtenidos
Al ejecutar nuestras pruebas definidas en `tests/tests.cpp` sobre el código fuente `src/solution.cpp`, obtuvimos los siguientes resultados:

* **Porcentaje de líneas ejecutadas:** 100.00%
* **Funciones probadas:** 2 de 2 (`productExceptSelf` y `productExceptSelfNaive`)

## 3. Análisis de los Casos de Prueba
Logramos una cobertura total del código gracias a que diseñamos nuestros asserts pensando en todos los flujos lógicos posibles:

1. **Camino estándar:** Arreglos normales sin ceros (`{1, 2, 3, 4}`). Obliga al programa a pasar por todas las multiplicaciones iterativas normales.
2. **Caso borde (Un Cero):** Arreglos con exactamente un cero. Prueba la lógica condicional que anula todas las posiciones de la respuesta final excepto donde estaba el cero.
3. **Caso extremo (Múltiples Ceros):** Evalúa la rama del código que detecta que, al haber más de un cero, devuelve un vector completamente lleno de ceros de forma inmediata.

**Conclusión:**
La herramienta confirma que no quedaron líneas de código muerto. Nuestras pruebas obligan al algoritmo a transitar por el 100% de su estructura, demostrando que es robusto ante los escenarios exigidos por LeetCode.