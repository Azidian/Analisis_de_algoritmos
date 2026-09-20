import sys
 
import listados
from catalogo import cargar_catalogo
from config import RUTA_CATALOGO_DEFECTO
from formato import pausar, titulo
from prioridades import menu_prioridades
from reporte import generar_recomendacion
 
 
def mostrar_menu():
    titulo("Menu principal")
    print("1. Ver catalogo")
    print("2. Asignar o cambiar prioridades")
    print("3. Ver prioridades asignadas")
    print("4. Ingresar presupuesto y generar recomendacion")
    print("S. Salir")
 
 
def main():
    ruta = sys.argv[1] if len(sys.argv) > 1 else RUTA_CATALOGO_DEFECTO
    catalogo = cargar_catalogo(ruta)
 
    if not catalogo:
        print("No se pudo iniciar el sistema: el catalogo no se cargo correctamente.")
        return
 
    # Diccionario {id_producto: prioridad}. Vacio al iniciar.
    prioridades = {}
 
    print(f"\nCatalogo cargado correctamente: {len(catalogo)} productos.")
 
    while True:
        mostrar_menu()
        opcion = input("\nSeleccione una opcion: ").strip().upper()
 
        if opcion == "1":
            listados.ver_catalogo(catalogo)
            pausar()
        elif opcion == "2":
            menu_prioridades(catalogo, prioridades)
        elif opcion == "3":
            listados.ver_prioridades(catalogo, prioridades)
            pausar()
        elif opcion == "4":
            generar_recomendacion(catalogo, prioridades)
            pausar()
        elif opcion == "S":
            print("\nGracias por usar el sistema de recomendacion de mercado.")
            break
        else:
            print("\nOpcion invalida, intente de nuevo.")
 
 
if __name__ == "__main__":
    main()
 