#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>

class Matriz {
private:
    std::vector<std::vector<double>> datos; // Cambiado a double para soportar decimales
    int filas, columnas;

public:
    Matriz(int f = 3, int c = 3);
    void setValor(int f, int c, double valor);
    double getValor(int f, int c) const;
    void imprimir() const;
};

#endif