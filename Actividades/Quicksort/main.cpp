#include <iostream> //Nos permite usar cout y endl para mostrar mensajes en la consola.
#include <vector> //Nos permite usar vectores que son arreglos dinamicos.

using namespace std; // Nos permite usar cout y endl sin prefijo std.

// Función para intercambiar dos valores
void intercambiar(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Función de partición: organiza los elementos según el pivote
int particion(vector<int>& arr, int inicio, int fin) {
    int pivote = arr[fin]; // Tomamos el último elemento como pivote
    int i = inicio - 1;    // Marca la frontera de los elementos menores

    for (int j = inicio; j < fin; j++) {
        // Si el elemento actual es menor que el pivote, va a la izquierda
        if (arr[j] < pivote) {
            i++;
            intercambiar(arr[i], arr[j]);
        }
    }

    // Colocamos el pivote justo después de los elementos menores
    intercambiar(arr[i + 1], arr[fin]);
    
    return i + 1; // Retornamos la posición final del pivote
}

// Función principal recursiva de Quick Sort
void quickSort(vector<int>& arr, int inicio, int fin) {
    if (inicio < fin) {
        // pi es el índice donde quedó ubicado el pivote
        int pi = particion(arr, inicio, fin);

        // Ordenamos la mitad izquierda y la mitad derecha recursivamente
        quickSort(arr, inicio, pi - 1);
        quickSort(arr, pi + 1, fin);
    }
}

int main() {
    int n;
    cout << "Ingrese la cantidad de elementos a ordenar: ";
    cin >> n;

    vector<int> datos(n);
    cout << "Ingrese los " << n << " elementos separados por espacio:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> datos[i];
    }

    cout << "Arreglo original: ";
    for (int num : datos) cout << num << " ";
    cout << endl;

    // Llamamos a quickSort desde el índice 0 hasta el último índice
    quickSort(datos, 0, datos.size() - 1);

    cout << "Arreglo ordenado:  ";
    for (int num : datos) cout << num << " ";
    cout << endl;

    return 0;
}
