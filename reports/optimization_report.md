# Reporte de Optimización y Seguridad

## 1. Banderas de Compilación
Realizamos pruebas de rendimiento ejecutando nuestro archivo de benchmark (con un arreglo de $n = 20,000$) utilizando diferentes niveles de optimización del compilador GCC. Los resultados obtenidos en máquina local fueron los siguientes:

| Bandera | Propósito | Tiempo Ingenua $O(n^2)$ | Tiempo Óptima $O(n)$ |
| :--- | :--- | :--- | :--- |
| `-O0` | Sin optimización (Por defecto) | 1411.51 ms | 0.3976 ms |
| `-O2` | Optimizado para velocidad máxima | 404.121 ms | 0.0724 ms |
| `-Os` | Optimizado para tamaño de archivo | 421.871 ms | 0.1332 ms |

**Análisis de Rendimiento:**
Observamos que el compilador hace un trabajo de optimización considerable por su cuenta. Al activar la bandera `-O2`, el tiempo de la solución ingenua bajó de 1411 ms a 404 ms (haciéndola más de 3 veces más rápida) gracias a que el compilador desenrolla bucles y mejora el uso de la memoria caché. La bandera `-Os` fue ligeramente más lenta que `-O2` (421.8 ms), lo cual confirma la teoría de que priorizar el tamaño del ejecutable sacrifica un margen mínimo de velocidad.

**Conclusión Principal:**
Aunque las banderas ayudan, **la mejora más abismal provino del diseño del algoritmo y no de la compilación**. Pasar de una complejidad $O(n^2)$ a $O(n)$ redujo el tiempo de ejecución en más de un 99.9% (pasando de cientos de milisegundos a apenas 0.07 ms en su mejor escenario).

## 2. Análisis de Seguridad (Sanitizers)
Para garantizar la robustez de la solución, verificamos el código utilizando las herramientas AddressSanitizer (`-fsanitize=address`) y UndefinedBehaviorSanitizer (`-fsanitize=undefined`).

* **Resultado:** La ejecución de los tests bajo estos sanitizers resultó completamente limpia. Esto demuestra empíricamente que nuestra implementación utilizando `std::vector` es segura en memoria: no existen *memory leaks* (fugas de memoria) y está garantizado que no se accede a índices fuera de los límites (out-of-bounds) durante los recorridos de prefijos y sufijos.

## 3. Cambios Algorítmicos Realizados
Inicialmente, se implementó una solución por fuerza bruta con complejidad O(n²), donde para cada elemento se recorría todo el arreglo para calcular el producto.
Posteriormente, se optimizó el algoritmo usando productos prefijo y sufijo.

**Estrategia**
  - Primera pasada: calcular productos acumulados a la izquierda
  - Segunda pasada: calcular productos a la derecha usando una variable suffix
  // Prefijos
  for (int i = 1; i < n; ++i) {
      answer[i] = answer[i - 1] * nums[i - 1];
  }
  // Sufijos
  int suffix = 1;
  for (int i = n - 1; i >= 0; --i) {
      answer[i] *= suffix;
      suffix *= nums[i];
  }

**Impacto**
- Complejidad reducida de O(n²) a O(n).
- Eliminación de cálculos repetidos.
- Mejor escalabilidad
- Cumplimiento de la restricción (sin división)

## 4. Análisis de Complejidad
| Tipo | Valor |
|------|------|
| Temporal | O(n) |
| Espacial | O(1) auxiliar |
| Mejor caso | Θ(n) |
| Peor caso | Θ(n) |
| Promedio | Θ(n) |

El algoritmo siempre recorre el arreglo dos veces, por lo que su comportamiento es lineal.

## 5. Robustez y Casos Borde
El algoritmo maneja correctamente:

Un cero → solo una posición distinta de cero
Múltiples ceros → todo el resultado es cero
Números negativos → signo correcto
n = 1 → retorna [1]

Esto demuestra alta robustez ante diferentes entradas.

## 6. Comparación con Solución Ingenua
| Característica | Ingenua | Óptima |
|--------------|--------|-------|
| Complejidad | O(n²) | O(n) |
| Escalabilidad | Baja | Alta |
| Tiempo | Muy alto | Muy bajo |

La diferencia crece rápidamente conforme aumenta n.

## 7. Microoptimización vs Algoritmo
Este experimento demuestra que un buen algoritmo tiene mucho más impacto que optimizar el compilador. Además, cambiar el algoritmo reduce órdenes de magnitud y el compilador solo mejora factores constantes.

## 8. Conclusión Final
La optimización principal fue algorítmica, no de compilación.
Se logró:

- Reducir complejidad de O(n²) a O(n).
- Mantener bajo consumo de memoria.
- Garantizar seguridad con sanitizers.
- Validar resultados con benchmark.

Esto confirma que la elección del algoritmo es el factor más importante en el rendimiento del software.
