import csv
import os

from config import COLUMNAS_ESPERADAS, ORDEN_CATEGORIAS


def cargar_catalogo(ruta):
    """
    Carga el catalogo desde un CSV con columnas:
        id,nombre,categoria,presentacion,precio

    Devuelve una lista de diccionarios con los productos validos.
    Las filas invalidas se reportan y se omiten, sin detener la carga.
    """
    if not os.path.isfile(ruta):
        print(f"No se encontro el archivo '{ruta}'.")
        return []

    catalogo = []
    ids_vistos = set()

    with open(ruta, newline="", encoding="utf-8") as archivo:
        lector = csv.DictReader(archivo)

        if lector.fieldnames is None or not COLUMNAS_ESPERADAS.issubset(set(lector.fieldnames)):
            print("El archivo CSV no tiene las columnas esperadas: "
                  "id,nombre,categoria,presentacion,precio")
            return []

        for num_fila, fila in enumerate(lector, start=2):  # la fila 1 es el encabezado
            try:
                producto = _validar_fila(fila, ids_vistos)
            except (ValueError, KeyError) as error:
                print(f"Fila {num_fila} invalida, se omite ({error}).")
                continue

            ids_vistos.add(producto["id"])
            catalogo.append(producto)

    # Se deja ordenado por id para que el catalogo siempre salga en orden
    catalogo.sort(key=lambda p: p["id"])
    return catalogo


def _validar_fila(fila, ids_vistos):
    """Convierte una fila del CSV en un producto valido o lanza ValueError."""
    id_producto = int(fila["id"])
    nombre = fila["nombre"].strip()
    categoria = fila["categoria"].strip()
    presentacion = fila["presentacion"].strip()
    precio = int(fila["precio"])

    if not nombre or not categoria or not presentacion:
        raise ValueError("hay campos de texto vacios")
    if precio <= 0:
        raise ValueError("el precio debe ser positivo")
    if id_producto in ids_vistos:
        raise ValueError(f"id duplicado ({id_producto})")

    return {
        "id": id_producto,
        "nombre": nombre,
        "categoria": categoria,
        "presentacion": presentacion,
        "precio": precio,
    }


def agrupar_por_categoria(productos):
    """
    Devuelve un diccionario {categoria: [productos ordenados por id]}.
    Las categorias salen en el orden definido en ORDEN_CATEGORIAS y las que
    no esten en esa lista se agregan al final en orden alfabetico.
    """
    grupos = {}
    for producto in productos:
        grupos.setdefault(producto["categoria"], []).append(producto)

    for lista in grupos.values():
        lista.sort(key=lambda p: p["id"])

    conocidas = [c for c in ORDEN_CATEGORIAS if c in grupos]
    otras = sorted(c for c in grupos if c not in ORDEN_CATEGORIAS)

    return {categoria: grupos[categoria] for categoria in conocidas + otras}


def indexar_por_id(catalogo):
    """Diccionario {id: producto} para consultas en O(1)."""
    return {p["id"]: p for p in catalogo}


def ancho_id(catalogo):
    """Ancho necesario para alinear los ids (2 digitos, 3 digitos, etc.)."""
    if not catalogo:
        return 2
    return max(2, len(str(max(p["id"] for p in catalogo))))
