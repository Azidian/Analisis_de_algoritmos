#ifndef INTERFAZ_USUARIO_H
#define INTERFAZ_USUARIO_H

#include "GestorProductividad.h"
#include <string>

class InterfazUsuario {
private:
    GestorProductividad gestor;

    void limpiarConsola() const;
    void esperarEnter() const;
    
    // Funciones seguras
    double leerDecimalSeguro(const std::string& mensaje, double min, double max) const;
    int leerEnteroSeguro(const std::string& mensaje, int min, int max) const;
    char leerOpcionMatriz() const;
    
    // Menús
    void registrarInformacionMenu();
    void consultarInformacionMenu() const;
    void actualizarInformacionMenu();
    void eliminarInformacionMenu();
    void menuArchivos();

public:
    void iniciar();
};

#endif