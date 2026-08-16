#include "GestorProductividad.h"
#include <fstream>

GestorProductividad::GestorProductividad() : estadoA(false), estadoB(false), estadoC(false) {}

void GestorProductividad::registrarMatriz(char tipo, const Matriz& nuevaMatriz) {
    if (tipo == 'A') {
        matrizA = nuevaMatriz;
        estadoA = true;
    } else if (tipo == 'B') {
        matrizB = nuevaMatriz;
        estadoB = true;
    }
    estadoC = false; 
}

bool GestorProductividad::actualizarCelda(char tipo, int f, int c, double valor) {
    if (tipo == 'A' && estadoA) {
        matrizA.setValor(f, c, valor);
        estadoC = false;
        return true;
    } else if (tipo == 'B' && estadoB) {
        matrizB.setValor(f, c, valor);
        estadoC = false;
        return true;
    }
    return false;
}

bool GestorProductividad::eliminarMatriz(char tipo) {
    bool eliminado = false;
    if (tipo == 'A' && estadoA) { estadoA = false; eliminado = true; }
    else if (tipo == 'B' && estadoB) { estadoB = false; eliminado = true; }
    else if (tipo == 'C' && estadoC) { estadoC = false; eliminado = true; }
    return eliminado;
}

bool GestorProductividad::ejecutarCalculo() {
    if (!estadoA || !estadoB) return false;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            double suma = 0.0;
            for (int k = 0; k < 3; ++k) {
                suma += matrizA.getValor(i, k) * matrizB.getValor(k, j);
            }
            matrizC.setValor(i, j, suma);
        }
    }
    estadoC = true;
    return true;
}

bool GestorProductividad::guardarEnArchivo(const std::string& ruta) const {
    std::ofstream arch(ruta);
    if (!arch.is_open()) return false;
    
    if (estadoA) {
        arch << "A\n";
        for(int i=0; i<3; ++i) {
            for(int j=0; j<3; ++j) arch << matrizA.getValor(i,j) << " ";
            arch << "\n";
        }
    }
    if (estadoB) {
        arch << "B\n";
        for(int i=0; i<3; ++i) {
            for(int j=0; j<3; ++j) arch << matrizB.getValor(i,j) << " ";
            arch << "\n";
        }
    }
    arch.close();
    return true;
}

int GestorProductividad::cargarDesdeArchivo(const std::string& ruta) {
    std::ifstream arch(ruta);
    if (!arch.is_open()) return 0;
    
    std::string tipo;
    int cargadas = 0;
    while (arch >> tipo) {
        if (tipo == "A" || tipo == "B") {
            Matriz temp;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    double val;
                    if (arch >> val) temp.setValor(i, j, val);
                }
            }
            registrarMatriz(tipo[0], temp);
            cargadas++;
        }
    }
    arch.close();
    return cargadas;
}

bool GestorProductividad::tieneA() const { return estadoA; }
bool GestorProductividad::tieneB() const { return estadoB; }
bool GestorProductividad::tieneC() const { return estadoC; }
const Matriz& GestorProductividad::getA() const { return matrizA; }
const Matriz& GestorProductividad::getB() const { return matrizB; }
const Matriz& GestorProductividad::getC() const { return matrizC; }