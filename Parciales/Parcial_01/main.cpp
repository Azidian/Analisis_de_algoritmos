#include "InterfazUsuario.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    InterfazUsuario ui;
    ui.iniciar();
    return 0;
}