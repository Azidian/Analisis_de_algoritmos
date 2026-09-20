from catalogo import agrupar_por_categoria, ancho_id, indexar_por_id
from config import TEXTO_PRIORIDAD
from formato import contar_productos, formatear_pesos, subtitulo, titulo
 
 
def ver_catalogo(catalogo):
    """Muestra el catalogo separado por categorias y ordenado por id."""
    if not catalogo:
        print("\nEl catalogo esta vacio.")
        return
 
    titulo("Catalogo de productos")
 
    ancho = ancho_id(catalogo)
    grupos = agrupar_por_categoria(catalogo)
 
    for categoria, productos in grupos.items():
        subtitulo(f"{categoria.upper()} ({contar_productos(len(productos))})")
        for producto in productos:
            etiqueta = f"[{producto['id']:>{ancho}}]"
            print(f"\n{etiqueta} {producto['nombre']} ({producto['presentacion']})")
            print(f"{' ' * (len(etiqueta) + 1)}Precio: {formatear_pesos(producto['precio'])}")
 
    print(f"\nTotal de productos en catalogo: {len(catalogo)}")
    print(f"Categorias: {len(grupos)}")
 
 
def ver_prioridades(catalogo, prioridades):
    """Muestra los productos calificados, agrupados por nivel de prioridad."""
    if not prioridades:
        print("\nAun no se ha asignado ninguna prioridad. "
              "Use la opcion 2 del menu.")
        return
 
    titulo("Prioridades asignadas")
 
    ancho = ancho_id(catalogo)
    productos_por_id = indexar_por_id(catalogo)
 
    for nivel in (1, 2, 3):
        # ids ordenados, para que la lista no salga en orden aleatorio
        ids_nivel = sorted(i for i, p in prioridades.items() if p == nivel)
        if not ids_nivel:
            continue
 
        subtitulo(f"PRIORIDAD {TEXTO_PRIORIDAD[nivel].upper()} "
                  f"({contar_productos(len(ids_nivel))})")
 
        for id_producto in ids_nivel:
            producto = productos_por_id.get(id_producto)
            if producto is None:
                continue  # el producto ya no existe en el catalogo actual
            etiqueta = f"[{producto['id']:>{ancho}}]"
            print(f"\n{etiqueta} {producto['nombre']} ({producto['presentacion']})")
            print(f"{' ' * (len(etiqueta) + 1)}Categoria: {producto['categoria']}")
            print(f"{' ' * (len(etiqueta) + 1)}Precio: {formatear_pesos(producto['precio'])}")
 
    print(f"\nProductos con prioridad asignada: {len(prioridades)} "
          f"de {len(catalogo)} en el catalogo.")
 