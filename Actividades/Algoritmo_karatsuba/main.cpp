#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// Función para pausar la ejecución y esperar a que el usuario presione Enter
void pausarPaso() {
    cout << "[Presiona ENTER para continuar...]";
    cin.get();
    cout << "----------------------------------------\n";
}

// Cuenta la cantidad de dígitos de un número
int contarDigitos(long long n) {
    if (n == 0)
        return 1;

    int contador = 0;
    while (n > 0) {
        contador++;
        n /= 10;
    }
    return contador;
}

// Calcula 10^exp
long long potencia10(int exp) {
    long long resultado = 1;
    for (int i = 0; i < exp; i++)
        resultado *= 10;
    return resultado;
}

// Algoritmo de Karatsuba con traza paso a paso
long long karatsuba(long long x, long long y) {
    cout << "\n>>> Evaluando: x = " << x << ", y = " << y << "\n";

    // Caso base
    if (x < 10 || y < 10) {
        long long res = x * y;
        cout << "  [Caso Base] Multiplicación directa: " << x << " * " << y << " = " << res << "\n";
        pausarPaso();
        return res;
    }

    // Número de dígitos del número más grande
    int n = max(contarDigitos(x), contarDigitos(y));

    // Mitad de los dígitos
    int m = n / 2;
    long long potencia = potencia10(m);

    // Dividir los números
    long long x1 = x / potencia;
    long long x0 = x % potencia;
    long long y1 = y / potencia;
    long long y0 = y % potencia;

    cout << "  -> Partición (m = " << m << ", divisor = 10^" << m << "):\n";
    cout << "     x1 = " << x1 << " | x0 = " << x0 << "\n";
    cout << "     y1 = " << y1 << " | y0 = " << y0 << "\n";
    pausarPaso();

    // Tres multiplicaciones de Karatsuba
    cout << "  -> Calculando z0 (x0 * y0)...\n";
    long long z0 = karatsuba(x0, y0);

    cout << "  -> Calculando z2 (x1 * y1)...\n";
    long long z2 = karatsuba(x1, y1);

    cout << "  -> Calculando z1 ((x1 + x0) * (y1 + y0) - z2 - z0)...\n";
    long long z1 = karatsuba(x1 + x0, y1 + y0) - z2 - z0;

    cout << "  -> Estado de variables intermedias:\n";
    cout << "     z0 = " << z0 << ", z2 = " << z2 << ", z1 = " << z1 << "\n";

    // Combinar resultados
    long long resultadoFinal = z2 * potencia * potencia + z1 * potencia + z0;
    cout << "  -> Combinación parcial: " << resultadoFinal << "\n";
    pausarPaso();

    return resultadoFinal;
}

int main() {
    long long numero1, numero2;

    cout << "Ingrese el primer numero: ";
    cin >> numero1;

    cout << "Ingrese el segundo numero: ";
    cin >> numero2;

    // Limpiar el búfer para que cin.get() funcione correctamente tras leer números
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nIniciando algoritmo paso a paso...\n";
    pausarPaso();

    long long resultado = karatsuba(numero1, numero2);

    cout << "\n========================================\n";
    cout << " RESULTADO FINAL: " << resultado << "\n";
    cout << "========================================\n";

    return 0;
}