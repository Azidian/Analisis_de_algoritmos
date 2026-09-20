# Parcial 2 — Sistema de recomendación de compras de mercado
 
Estudiante: Wendy Vanessa Atehortua Chaverra 
 
## Problema
 
Una persona tiene un presupuesto fijo para hacer mercado y una lista de
productos, cada uno con un precio y un nivel de importancia (alta, media o
baja). El sistema debe seleccionar el conjunto de productos que **maximiza
la utilidad total sin exceder el presupuesto**.
 
## Cómo ejecutar
 
```bash
python sistema_mercado.py
```
 
Por defecto carga `productos.csv` (55 productos). 
 
Requiere Python 3 (no usa librerías externas, solo `csv`, `os` y `sys` de
la biblioteca estándar).
 
## Menú del sistema
 
1. **Ver catálogo** — muestra los productos agrupados por categoría y
   ordenados por id.
2. **Asignar o cambiar prioridades** — submenú para calificar los
   productos pendientes, cambiar los ya calificados, trabajar una
   categoría específica, o revisar todo el catálogo desde el principio.
   El recorrido se hace en bloques de 10 productos, preguntando si se
   desea continuar después de cada bloque.
3. **Ver prioridades asignadas** — lista lo ya calificado, agrupado por
   nivel de prioridad.
4. **Ingresar presupuesto y generar recomendación** — pide el presupuesto,
   corre el algoritmo de optimización y muestra el reporte final: total
   gastado, dinero disponible, utilidad total obtenida y los productos
   que quedaron por fuera por falta de presupuesto.
## Estructura del proyecto
 
El código está dividido en módulos según su responsabilidad, en vez de un
único archivo:
 
| Archivo             | Responsabilidad                                              |
|----------------------|--------------------------------------------------------------|
| `sistema_mercado.py` | Punto de entrada: menú principal y coordinación entre módulos |
| `config.py`          | Constantes: tabla de utilidad, orden de categorías, tamaño de bloque |
| `formato.py`         | Formato de moneda, títulos, separadores y pausas de pantalla  |
| `catalogo.py`        | Carga y validación del CSV, agrupación por categoría          |
| `listados.py`          | Opciones 1 y 3 del menú (mostrar catálogo y prioridades)      |
| `prioridades.py`     | Opción 2 del menú (asignar o cambiar prioridades)             |
| `algoritmo.py`       | Estrategia de optimización (codiciosa + backtracking con podas) |
| `reporte.py`         | Opción 4 del menú (presupuesto y reporte final)               |
| `productos.csv`      | Catálogo completo: 55 productos en 8 categorías               |

 
## Estructuras de datos
 
- **Catálogo**: lista de diccionarios. Se usa lista porque el algoritmo
  necesita acceso por índice en tiempo constante y recorrer los productos
  en distinto orden según la operación (por categoría e id para mostrar,
  por razón utilidad/precio para decidir).
- **Prioridades**: diccionario `{id_producto: prioridad}`. Se guarda
  aparte del catálogo porque el catálogo es fijo y compartido, mientras
  que la prioridad cambia según el usuario. Permite consultar o
  actualizar en O(1) y admite productos sin calificar (si se responde
  `0`, no se crea entrada).
- **Tabla de utilidades**: diccionario fijo `{1: 10, 2: 6, 3: 3}` que
  convierte la prioridad en puntos. Desacopla la escala de prioridades
  del algoritmo.
- **Carrito en construcción**: pila (lista usada como LIFO). Es la
  estructura natural para representar la solución parcial durante el
  recorrido en profundidad (DFS) del backtracking: al incluir un producto
  se apila, y al retroceder se desapila en O(1).
Presupuesto y precios se manejan como enteros (pesos colombianos, sin
decimales) para evitar errores de redondeo.
 
## Estrategia algorítmica
 
Se combinan dos estrategias, no solo una:
 
**1. Estrategia codiciosa (greedy) — compra base de referencia.**
Antes del backtracking, los candidatos se ordenan de mayor a menor razón
utilidad/precio y se recorren una sola vez, incluyendo cada producto
mientras quepa en lo que queda del presupuesto, sin retroceder. Esto da
una solución válida rápida (`O(n log n)` por el ordenamiento) que sirve
como punto de partida para inicializar la mejor solución conocida antes
de iniciar la búsqueda exhaustiva.
 
**2. Backtracking con podas — búsqueda de la solución óptima.**
Sobre los mismos candidatos ordenados, se explora un árbol de decisiones
binario (incluir / no incluir cada producto) en profundidad (DFS), con
dos cortes:
 
- **Poda de factibilidad**: si el producto no cabe en el presupuesto
  restante, esa rama se descarta de inmediato.
- **Poda de optimalidad (cota superior)**: si ni comprando todo lo que
  queda por evaluar se podría superar la mejor utilidad ya encontrada,
  la rama completa se abandona.
En caso de empate en utilidad, se prefiere la combinación de menor costo.
 
### Por qué backtracking y no fuerza bruta o codicioso puro
 
- **Fuerza bruta** evaluaría las 2ⁿ combinaciones posibles sin descartar
  ninguna rama por adelantado — inviable para catálogos de más de ~25
  productos priorizados.
- **Codicioso puro** es rápido (una sola pasada) pero no garantiza el
  óptimo: puede dejar por fuera una combinación mejor porque nunca
  reconsidera una decisión ya tomada. Aun así, es útil como cota inicial.
- **Backtracking** conserva la garantía de encontrar la solución óptima
  exacta (igual que la fuerza bruta), pero evita explorar las ramas que,
  por presupuesto o por cota de utilidad, no pueden mejorar lo ya
  encontrado — de ahí la analogía del laberinto: al chocar con una pared
  se retrocede y se prueba otro camino, en vez de quedar atascado.
El resultado del backtracking fue validado contra fuerza bruta en
catálogos pequeños generados aleatoriamente, confirmando que siempre
entrega el óptimo exacto.
 
## Autoría
 
Wendy Vanessa Atehortua Chaverra
 
