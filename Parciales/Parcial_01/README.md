# Sistema de Asignación de Productividad

Este es un sistema de consola desarrollado en C++ diseñado para calcular y gestionar la productividad total de un equipo de desarrolladores a lo largo de diferentes fases de múltiples proyectos. El cálculo central se basa en la **multiplicación de matrices** para relacionar la eficiencia individual con los requerimientos de tiempo de cada proyecto.

---

## Características Principales

* **Arquitectura Limpia (MVC):** El código está dividido lógicamente en Modelo (`Matriz`), Controlador (`GestorProductividad`) y Vista (`InterfazUsuario`), garantizando un diseño modular y escalable.
* **Validación Robusta de I/O:** El sistema está protegido contra entradas inválidas. El ingreso accidental de caracteres no numéricos no rompe la ejecución ni genera bucles infinitos.
* **Persistencia de Datos:** Permite guardar el estado actual de las matrices en un archivo de texto (`datos_matrices.txt`) y cargarlo en futuras ejecuciones. (El archivo debe tener el nombre `datos_matrices.txt`)
* **Interfaz de Consola Amigable:** Uso de codificación UTF-8 para una visualización limpia con iconos interactivos, además de limpieza de consola controlada sin depender de comandos agresivos del sistema operativo.

---

## Lógica (Las Matrices)

Este sistema basa el núcleo de su procedimiento en **C = A × B**:

1. **Matriz A (Productividad):** 
   * Representa los *puntos por hora* aportados.
   * *Filas:* Desarrolladores.
   * *Columnas:* Proyectos.
2. **Matriz B (Horas Requeridas):** 
   * Representa el tiempo que exige cada etapa.
   * *Filas:* Proyectos.
   * *Columnas:* Fases del proyecto.
3. **Matriz C (Productividad Total):** 
   * El resultado algorítmico de la multiplicación. 
   * *Filas:* Desarrolladores.
   * *Columnas:* Fases del proyecto.
   * Define cuántos puntos totales completará cada desarrollador en una fase específica sumando el esfuerzo de todos los proyectos.

---

## Estructura del Proyecto

El repositorio está organizado en 7 archivos fuente que separan la declaración (`.h`) de la implementación (`.cpp`):

* `main.cpp`: Punto de entrada que configura la consola y arranca la interfaz.
* `Matriz.h` / `Matriz.cpp`: Estructura de datos para manejar cuadrículas dinámicas de 3x3.
* `GestorProductividad.h` / `GestorProductividad.cpp`: Lógica, cálculos matemáticos y persistencia en archivos.
* `InterfazUsuario.h` / `InterfazUsuario.cpp`: Menú interactivo, validaciones `try-catch` y manejo del buffer de la consola.

---

## Instalación y Compilación

Para compilar y ejecutar este proyecto localmente, necesitas tener instalado un compilador de C++ como **GCC (MinGW en Windows)**.

1. Clona este repositorio:
```bash
git clone https://github.com/Azidian/Analisis_de_algoritmos/new/main/Parciales/Parcial_01.git
```

Navega a la carpeta del proyecto:

```bash
cd "Parciales\Parcial_01"
```
Compila el código enlazando todos los archivos .cpp:
```bash
g++ main.cpp Matriz.cpp GestorProductividad.cpp InterfazUsuario.cpp -o asignacion_tareas
```
Ejecuta el programa:

```bash
asignacion_tareas.exe
```
o también, 
```bash
 ./asignacion_tareas
```
_Usa el que necesites dependiendo de tu sistema operativo._


---
Autor
Wendy Vanessa Atehortua Chaverra - Estudiante de EAFIT - wvatehortc@eafit.edu.co

Proyecto realizado como actividad evaluativa (70% del parcial) aplicando diseño de algoritmos, abstracción matemática y programación orientada a objetos en C++.
