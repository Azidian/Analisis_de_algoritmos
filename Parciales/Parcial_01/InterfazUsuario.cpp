#include "InterfazUsuario.h"
#include <iostream>
#include <cctype> // Para toupper

using namespace std;

// ================= UTILIDADES DE TERMINAL =================
void InterfazUsuario::limpiarConsola() const {
    cout << string(50, '\n');
}

void InterfazUsuario::esperarEnter() const {
    cout << "\nPresione Enter para continuar...";
    string temp;
    getline(cin, temp); 
}

double InterfazUsuario::leerDecimalSeguro(const string& mensaje, double min, double max) const {
    string entrada;
    double numero;
    while (true) {
        cout << mensaje;
        getline(cin, entrada);
        try {
            numero = stod(entrada); 
            if (numero >= min && numero <= max) return numero;
            cout << "  [Error] Numero fuera de rango.\n";
        } catch (...) {
            cout << "  [Error] Entrada invalida. Ingrese un numero (ej. 2.5).\n";
        }
    }
}

int InterfazUsuario::leerEnteroSeguro(const string& mensaje, int min, int max) const {
    string entrada;
    int numero;
    while (true) {
        cout << mensaje;
        getline(cin, entrada);
        try {
            numero = stoi(entrada); 
            if (numero >= min && numero <= max) return numero;
            cout << "  [Error] Numero fuera de rango (" << min << " - " << max << ").\n";
        } catch (...) {
            cout << "  [Error] Entrada invalida. Ingrese solo un numero entero.\n";
        }
    }
}

char InterfazUsuario::leerOpcionMatriz() const {
    string entrada;
    while (true) {
        getline(cin, entrada);
        if (!entrada.empty()) {
            char c = toupper(entrada[0]);
            if (c == 'A' || c == 'B') return c;
        }
        cout << "  [Error] Matriz no existe. Ingrese solo 'A' o 'B': "; 
    }
}

// ================= MENÚS Y LÓGICA =================
void InterfazUsuario::registrarInformacionMenu() {
    cout << "\nQue matriz desea registrar? (A / B): ";
    char tipo = leerOpcionMatriz();

    if ((tipo == 'A' && gestor.tieneA()) || (tipo == 'B' && gestor.tieneB())) {
        cout << "\n[Atencion] La Matriz " << tipo << " ya tiene datos actualmente:\n";
        if (tipo == 'A') gestor.getA().imprimir();
        else gestor.getB().imprimir();

        cout << "\nDesea sobreescribirla? (S para Si, cualquier tecla para No): ";
        string resp;
        getline(cin, resp);
        if (resp.empty() || toupper(resp[0]) != 'S') {
            cout << "Operacion cancelada.\n";
            return;
        }
    }

    Matriz tempMatriz(3, 3);
    cout << "\n--- Ingresando datos para la Matriz " << tipo << " ---\n";
    
    if (tipo == 'A') {
        cout << "Significado: PRODUCTIVIDAD (Puntos completados por hora).\n";
        cout << " > Filas (0-2): Desarrolladores\n";
        cout << " > Columnas (0-2): Proyectos\n\n";
    } else {
        cout << "Significado: HORAS REQUERIDAS (Tiempo necesario por fase).\n";
        cout << " > Filas (0-2): Proyectos\n";
        cout << " > Columnas (0-2): Fases del proyecto\n\n";
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            string msj = "Fila " + to_string(i) + ", Columna " + to_string(j) + " : ";
            double valor = leerDecimalSeguro(msj, -10000.0, 10000.0); 
            tempMatriz.setValor(i, j, valor);
        }
    }
    
    gestor.registrarMatriz(tipo, tempMatriz);
    cout << "\n[Exito] Matriz " << tipo << " registrada correctamente.\n";
}

void InterfazUsuario::consultarInformacionMenu() const {
    cout << "\n--- Estado Actual de los Datos ---\n";
    if (gestor.tieneA()) {
        cout << "\nMatriz A (Productividad - Puntos por hora):\n";
        gestor.getA().imprimir();
    } else cout << "\n[!] Matriz A no registrada.\n";

    if (gestor.tieneB()) {
        cout << "\nMatriz B (Horas requeridas):\n";
        gestor.getB().imprimir();
    } else cout << "\n[!] Matriz B no registrada.\n";
}

void InterfazUsuario::actualizarInformacionMenu() {
    cout << "\nQue matriz desea actualizar? (A / B): ";
    char tipo = leerOpcionMatriz();

    if ((tipo == 'A' && !gestor.tieneA()) || (tipo == 'B' && !gestor.tieneB())) {
        cout << "\n[Error] La matriz " << tipo << " no tiene datos registrados aun.\n";
        return;
    }

    int f = leerEnteroSeguro("Ingrese la fila (0-2): ", 0, 2);
    int c = leerEnteroSeguro("Ingrese la columna (0-2): ", 0, 2);
    double valor = leerDecimalSeguro("Ingrese el nuevo valor: ", -10000.0, 10000.0);
    
    if (gestor.actualizarCelda(tipo, f, c, valor)) {
        cout << "\n[Exito] Valor actualizado.\n";
    }
}

void InterfazUsuario::eliminarInformacionMenu() {
    cout << "\nQue matriz desea eliminar? (A, B o C para borrar resultado): ";
    string entrada;
    getline(cin, entrada);
    if (entrada.empty()) return;

    char tipo = toupper(entrada[0]);
    if (tipo != 'A' && tipo != 'B' && tipo != 'C') {
        cout << "\n[Error] La matriz '" << tipo << "' no existe. Solo A, B o C.\n";
        return;
    }

    if (gestor.eliminarMatriz(tipo)) {
        cout << "\n[Exito] La informacion de la Matriz " << tipo << " fue eliminada correctamente.\n";
    } else {
        cout << "\n[!] No se pudo eliminar porque la Matriz " << tipo << " no tenia informacion previa.\n";
    }
}

void InterfazUsuario::menuArchivos() {
    cout << "\n--- GESTION DE ARCHIVOS ---\n";
    cout << "1. Guardar matrices actuales en archivo\n";
    cout << "2. Cargar matrices desde archivo\n";
    int op = leerEnteroSeguro("Seleccione una opcion (1-2): ", 1, 2);
    
    string ruta = "datos_matrices.txt";

    if (op == 1) {
        if (!gestor.tieneA() && !gestor.tieneB()) {
            cout << "\n[Error] No hay datos en memoria para guardar.\n";
            return;
        }
        if (gestor.guardarEnArchivo(ruta)) {
            cout << "\n[Exito] Datos guardados en el archivo: " << ruta << "\n";
        } else cout << "\n[Error] No se pudo crear el archivo.\n";
    } 
    else if (op == 2) {
        int cargadas = gestor.cargarDesdeArchivo(ruta);
        if (cargadas > 0) {
            cout << "\n[Exito] Se cargaron datos de " << cargadas << " matriz(ces) desde " << ruta << ".\n";
        } else {
            cout << "\n[Error] No se pudo leer el archivo o el formato es incorrecto.\n";
        }
    }
}

void InterfazUsuario::iniciar() {
    int opcion = 0;

    while (opcion != 8) {
        limpiarConsola();
        cout << "★ ================================================== ★\n";
        cout << "   ☆ SISTEMA CALCULO DE PRODUCTIVIDAD EN PROYECTOS ☆  \n";
        cout << "★ ================================================== ★\n";
        cout << "1. Registrar informacion manual (Matriz A o B)\n";
        cout << "2. Consultar informacion actual\n";
        cout << "3. Actualizar una celda\n";
        cout << "4. Eliminar informacion\n";
        cout << "5. Ejecutar calculo (A x B)\n";
        cout << "6. Mostrar resultados obtenidos\n";
        cout << "7. Gestionar datos por archivo (.txt)\n";
        cout << "8. Salir\n";
        cout << "★ ======================= ☆ ======================== ★\n";
        
        opcion = leerEnteroSeguro("Seleccione una opcion valida (1-8): ", 1, 8); 

        switch (opcion) {
            case 1: registrarInformacionMenu(); break;
            case 2: consultarInformacionMenu(); break;
            case 3: actualizarInformacionMenu(); break;
            case 4: eliminarInformacionMenu(); break;
            case 5:
                if (gestor.ejecutarCalculo()) {
                    cout << "\n[Exito] Calculo completado exitosamente.\n";
                    cout << "Desea ver el resultado ahora mismo? (S/N): ";
                    string resp;
                    getline(cin, resp);
                    if (!resp.empty() && toupper(resp[0]) == 'S') {
                        cout << "\n--- RESULTADO: Matriz C (Productividad Total) ---\n";
                        gestor.getC().imprimir();
                    }
                } else {
                    cout << "\n[Error] Faltan datos para realizar el calculo:\n";
                    if (!gestor.tieneA()) cout << " - Falta ingresar la Matriz A (Productividad).\n";
                    if (!gestor.tieneB()) cout << " - Falta ingresar la Matriz B (Horas).\n";
                }
                break;
            case 6:
                if (gestor.tieneC()) {
                    cout << "\n--- RESULTADO: Matriz C (Productividad Total) ---\n";
                    cout << " > Filas: Desarrolladores\n > Columnas: Fases del proyecto\n\n";
                    gestor.getC().imprimir();
                } else cout << "\n[Error] El calculo no se ha ejecutado aun o datos fueron alterados.\n";
                break;
            case 7: menuArchivos(); break; 
            case 8: cout << "\nSaliendo del sistema. Hasta pronto!\n"; break;
        }

        if (opcion != 8) {
            esperarEnter();
        }
    }
}