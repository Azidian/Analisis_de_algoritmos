import algoritmo
from config import TEXTO_PRIORIDAD
from formato import formatear_pesos, separador, titulo


def pedir_presupuesto():
    """Pide el presupuesto en pesos. Acepta 52000 o 52.000. None = cancelar."""
    while True:
        entrada = input("\nIngrese su presupuesto en pesos "
                        "(ENTER para cancelar): $").strip()
        if not entrada:
            return None
        try:
            presupuesto = int(entrada.replace(".", "").replace(",", ""))
        except ValueError:
            print("Por favor ingrese un numero entero valido.")
            continue

        if presupuesto <= 0:
            print("El presupuesto debe ser un numero positivo.")
            continue

        return presupuesto


def generar_recomendacion(catalogo, prioridades):
    if not prioridades:
        print("\nPrimero debe asignar prioridades a al menos un producto "
              "(opcion 2 del menu).")
        return

    presupuesto = pedir_presupuesto()
    if presupuesto is None:
        print("Operacion cancelada.")
        return

    # Candidatos: con prioridad asignada Y precio individual <= presupuesto
    candidatos = [p for p in catalogo
                  if p["id"] in prioridades and p["precio"] <= presupuesto]

    # Priorizados que quedan fuera desde el principio por su precio individual
    excluidos_por_precio = [p for p in catalogo
                            if p["id"] in prioridades and p["precio"] > presupuesto]

    titulo("Recomendacion de compra")
    print(f"Presupuesto ingresado: {formatear_pesos(presupuesto)}")
    print(f"Productos evaluados:   {len(prioridades)}")

    if not candidatos:
        print("Productos recomendados: 0")
        print("\nNingun producto priorizado cabe dentro del presupuesto.")
        return

    mejor = algoritmo.resolver(candidatos, presupuesto, prioridades)
    seleccion = mejor["seleccion"]

    print(f"Productos recomendados: {len(seleccion)}")

    _imprimir_seleccion(seleccion, prioridades)

    separador()
    print(f"TOTAL GASTADO:     {formatear_pesos(mejor['costo'])}")
    print(f"DISPONIBLE:        {formatear_pesos(presupuesto - mejor['costo'])}")
    print(f"UTILIDAD TOTAL:    {mejor['utilidad']} puntos")

    ids_elegidos = {p["id"] for p in seleccion}
    no_incluidos = ([p for p in candidatos if p["id"] not in ids_elegidos]
                    + excluidos_por_precio)
    _imprimir_no_incluidos(no_incluidos, prioridades)


def _imprimir_seleccion(seleccion, prioridades):
    """Lista numerada de lo que se recomienda comprar."""
    print()
    for numero, producto in enumerate(
            sorted(seleccion, key=lambda p: (prioridades[p["id"]], p["id"])),
            start=1):
        prioridad = TEXTO_PRIORIDAD[prioridades[producto["id"]]]
        print(f"{numero}. {producto['nombre']} ({producto['presentacion']})")
        print(f"   Precio: {formatear_pesos(producto['precio'])} | "
              f"Prioridad: {prioridad}\n")


def _imprimir_no_incluidos(no_incluidos, prioridades):
    if not no_incluidos:
        return
    print("\nNo incluidos por presupuesto:")
    for producto in sorted(no_incluidos, key=lambda p: p["precio"]):
        prioridad = TEXTO_PRIORIDAD[prioridades[producto["id"]]]
        print(f"- [{producto['id']}] {producto['nombre']} ({prioridad}) "
              f"- {formatear_pesos(producto['precio'])}")
