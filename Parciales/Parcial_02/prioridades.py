from catalogo import agrupar_por_categoria, ancho_id
from config import TAMANO_BLOQUE, TEXTO_PRIORIDAD
from formato import confirmar, contar_productos, formatear_pesos, subtitulo, titulo


def menu_prioridades(catalogo, prioridades):
    """Submenu de la opcion 2. Se repite hasta que el usuario elija volver."""
    if not catalogo:
        print("\nEl catalogo esta vacio, no hay nada que priorizar.")
        return

    while True:
        pendientes = [p for p in catalogo if p["id"] not in prioridades]
        asignados = [p for p in catalogo if p["id"] in prioridades]

        titulo("Asignar o cambiar prioridades")
        print(f"1. Calificar productos SIN prioridad  ({len(pendientes)} pendientes)")
        print(f"2. Cambiar prioridades YA asignadas   ({len(asignados)} asignadas)")
        print("3. Trabajar una categoria especifica")
        print("4. Revisar todo el catalogo desde el principio")
        print("5. Volver al menu principal")

        opcion = input("\nSeleccione una opcion: ").strip()

        if opcion == "1":
            if not pendientes:
                print("\nYa calificaste todos los productos del catalogo.")
                continue
            _recorrer(pendientes, prioridades, catalogo)

        elif opcion == "2":
            if not asignados:
                print("\nTodavia no hay prioridades asignadas para cambiar.")
                continue
            _recorrer(asignados, prioridades, catalogo)

        elif opcion == "3":
            seleccion = _elegir_categoria(catalogo)
            if seleccion:
                _recorrer(seleccion, prioridades, catalogo)

        elif opcion == "4":
            _recorrer(catalogo, prioridades, catalogo)

        elif opcion == "5":
            return

        else:
            print("\nOpcion invalida, intente de nuevo.")


def _elegir_categoria(catalogo):
    """Lista las categorias y devuelve los productos de la elegida."""
    grupos = agrupar_por_categoria(catalogo)
    categorias = list(grupos.keys())

    print()
    for numero, categoria in enumerate(categorias, start=1):
        print(f"{numero}. {categoria} ({contar_productos(len(grupos[categoria]))})")

    entrada = input("\nNumero de la categoria (ENTER para cancelar): ").strip()
    if not entrada:
        return []

    if entrada.isdigit() and 1 <= int(entrada) <= len(categorias):
        return grupos[categorias[int(entrada) - 1]]

    print("Categoria invalida.")
    return []


def _recorrer(productos, prioridades, catalogo):
    """
    Recorre los productos indicados agrupados por categoria y en bloques
    cortos (TAMANO_BLOQUE por pantalla), preguntando despues de cada bloque
    si el usuario desea continuar.
    """
    grupos = agrupar_por_categoria(productos)
    ancho = ancho_id(catalogo)
    total = len(productos)
    procesados = 0

    for categoria, items in grupos.items():
        subtitulo(f"CATEGORIA: {categoria.upper()} ({contar_productos(len(items))})")

        for inicio in range(0, len(items), TAMANO_BLOQUE):
            bloque = items[inicio:inicio + TAMANO_BLOQUE]

            for producto in bloque:
                prioridad = _pedir_prioridad(producto, prioridades, ancho)

                if prioridad is None:  # el usuario escribio S
                    print(f"\nAsignacion interrumpida. Se guardaron "
                          f"{procesados} de {total} productos revisados.")
                    return

                if prioridad == 0:
                    # omitir: si ya tenia prioridad, se elimina
                    prioridades.pop(producto["id"], None)
                else:
                    prioridades[producto["id"]] = prioridad

                procesados += 1

            if procesados < total:
                print(f"\nProgreso: {procesados} de {total} productos.")
                if not confirmar("¿Desea continuar asignando prioridades?"):
                    print("Asignacion pausada por el usuario.")
                    return

    print(f"\nListo: se revisaron los {total} productos de esta seleccion.")


def _pedir_prioridad(producto, prioridades, ancho):
    """
    Pide y valida la prioridad de un solo producto.
    Devuelve un entero 0-3, o None si el usuario quiere salir (S).
    """
    actual = prioridades.get(producto["id"])
    etiqueta = f"[{producto['id']:>{ancho}}]"
    sangria = " " * (len(etiqueta) + 1)

    print(f"\n{etiqueta} {producto['nombre']} ({producto['presentacion']})")
    print(f"{sangria}Precio: {formatear_pesos(producto['precio'])}")
    if actual is not None:
        print(f"{sangria}Prioridad actual: {TEXTO_PRIORIDAD[actual]}")

    while True:
        entrada = input(
            f"{sangria}Prioridad (1=Alta 2=Media 3=Baja 0=Omitir, S=Salir): > "
        ).strip().upper()

        if entrada == "S":
            return None
        if entrada in {"0", "1", "2", "3"}:
            return int(entrada)

        print(f"{sangria}Entrada invalida. Escriba 1, 2, 3, 0 o S.")
