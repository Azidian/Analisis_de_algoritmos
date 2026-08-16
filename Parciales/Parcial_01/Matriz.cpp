#include "Matriz.h"
#include <iostream>
#include <iomanip>

Matriz::Matriz(int f, int c) : filas(f), columnas(c) {
    datos = std::vector<std::vector<double>>(filas, std::vector<double>(columnas, 0.0));
}

void Matriz::setValor(int f, int c, double valor) {
    datos[f][c] = valor;
}

double Matriz::getValor(int f, int c) const {
    return datos[f][c];
}

void Matriz::imprimir() const {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // Formateado limpio para decimales (ej: 4.50)
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) << datos[i][j] << " ";
        }
        std::cout << "\n";
    }
}