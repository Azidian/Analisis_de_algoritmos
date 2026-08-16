#ifndef GESTOR_PRODUCTIVIDAD_H
#define GESTOR_PRODUCTIVIDAD_H

#include "Matriz.h"
#include <string>

class GestorProductividad {
private:
    Matriz matrizA;
    Matriz matrizB;
    Matriz matrizC;
    bool estadoA, estadoB, estadoC;

public:
    GestorProductividad();

    void registrarMatriz(char tipo, const Matriz& nuevaMatriz);
    bool actualizarCelda(char tipo, int f, int c, double valor);
    bool eliminarMatriz(char tipo);
    bool ejecutarCalculo();

    // Archivos
    bool guardarEnArchivo(const std::string& ruta) const;
    int cargarDesdeArchivo(const std::string& ruta);

    // Getters
    bool tieneA() const;
    bool tieneB() const;
    bool tieneC() const;
    const Matriz& getA() const;
    const Matriz& getB() const;
    const Matriz& getC() const;
};

#endif