#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Función para verificar si una cadena contiene solo '0' y '1'
bool esBinarioValido(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (c != '0' && c != '1') {
            return false; // Si encuentra un '2' o cualquier otra cosa, retorna falso
        }
    }
    return true;
}

// Función para sumar dos números binarios representados como vectores de bits
vector<int> sumarBinarios(const vector<int>& a, const vector<int>& b) {
    vector<int> resultado;
    int i = a.size() - 1;
    int j = b.size() - 1;
    int acarreo = 0;

    while (i >= 0 || j >= 0 || acarreo > 0) {
        int suma = acarreo;
        if (i >= 0) suma += a[i--];
        if (j >= 0) suma += b[j--];

        resultado.push_back(suma % 2);
        acarreo = suma / 2;
    }

    reverse(resultado.begin(), resultado.end());
    return resultado;
}

// Función para desplazar y multiplicar el vector por un bit (0 o 1)
vector<int> multiplicarPorBitYDesplazar(const vector<int>& a, int bit, int desplazamiento) {
    if (bit == 0) return {0};
    
    vector<int> res = a;
    for (int k = 0; k < desplazamiento; k++) {
        res.push_back(0);
    }
    return res;
}

// Función principal que simula la multiplicación manual
vector<int> multiplicarBinarios(const vector<int>& a, const vector<int>& b) {
    vector<int> total = {0};
    int n = b.size();

    for (int i = n - 1; i >= 0; i--) {
        int bit = b[i];
        if (bit == 1) {
            int desplazamiento = (n - 1) - i;
            vector<int> filaParcial = multiplicarPorBitYDesplazar(a, bit, desplazamiento);
            total = sumarBinarios(total, filaParcial);
        }
    }
    return total;
}

// Convierte el string validado al vector de estructura de datos
vector<int> convertirAvector(const string& str) {
    vector<int> vec;
    for (char c : str) {
        vec.push_back(c - '0'); 
    }
    return vec;
}

int main() {
    string entrada1, entrada2;

    cout << "=== MULTIPLICACION DE NUMEROS BINARIOS ===" << endl << endl;
    
    // Ciclo para pedir el primer número hasta que sea válido
    while (true) {
        cout << "Ingrese el primer numero binario (ej. 101): ";
        cin >> entrada1;
        
        if (esBinarioValido(entrada1)) {
            break; // Si es válido, salimos del ciclo
        }
        cout << "[!] Error: Solo se permiten los digitos 0 y 1. Intente de nuevo.\n" << endl;
    }

    cout << endl;

    // Ciclo para pedir el segundo número hasta que sea válido
    while (true) {
        cout << "Ingrese el segundo numero binario (ej. 011): ";
        cin >> entrada2;
        
        if (esBinarioValido(entrada2)) {
            break; // Si es válido, salimos del ciclo
        }
        cout << "[!] Error: Solo se permiten los digitos 0 y 1. Intente de nuevo.\n" << endl;
    }

    // Convertimos las entradas válidas a nuestras estructuras de datos (vectores)
    vector<int> numero1 = convertirAvector(entrada1);
    vector<int> numero2 = convertirAvector(entrada2);

    // Realizamos la multiplicación
    vector<int> resultado = multiplicarBinarios(numero1, numero2);

    // Mostramos el resultado
    cout << "\n----------------------------------------" << endl;
    cout << "Resultado de la multiplicacion binaria: ";
    for (int bit : resultado) {
        cout << bit;
    }
    cout << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}
