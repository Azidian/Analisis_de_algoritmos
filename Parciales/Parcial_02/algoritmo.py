from config import TABLA_UTILIDAD


def utilidad_de(producto, prioridades):
    """Convierte la prioridad del producto en puntos de utilidad."""
    return TABLA_UTILIDAD[prioridades[producto["id"]]]


def resolver(candidatos, presupuesto, prioridades):
    """
    Devuelve el diccionario {'utilidad', 'costo', 'seleccion'} con la mejor
    combinacion de productos que no excede el presupuesto.
    En caso de empate en utilidad, prefiere la de menor costo.
    """
    # 1) Ordenar por razon utilidad/precio descendente
    ordenados = sorted(
        candidatos,
        key=lambda p: utilidad_de(p, prioridades) / p["precio"],
        reverse=True,
    )

    # Utilidades precalculadas en el mismo orden, para no consultar
    # diccionarios dentro de la recursion
    utilidades = [utilidad_de(p, prioridades) for p in ordenados]

    # 2) Suma-sufijo de utilidades: cotas[i] = utilidad total de ordenados[i:]
    n = len(ordenados)
    cotas = [0] * (n + 1)
    for i in range(n - 1, -1, -1):
        cotas[i] = cotas[i + 1] + utilidades[i]

    # 3) Compra base de referencia: un recorrido codicioso sobre la lista ya
    #    ordenada. No garantiza el optimo, pero da una solucion valida en O(n)
    #    con la cual inicializar 'mejor', de modo que la poda de optimalidad
    #    empiece a cortar ramas desde el primer nivel del arbol y no despues
    #    de llegar a la primera hoja.
    mejor = _compra_base(ordenados, utilidades, presupuesto)
    carrito = []  # pila vacia al iniciar

    _explorar(ordenados, utilidades, cotas, 0, presupuesto, carrito, 0, 0, mejor)

    return mejor


def _compra_base(productos, utilidades, presupuesto):
    """
    Estrategia CODICIOSA: recorre los productos en orden de mayor a menor
    razon utilidad/precio y agrega cada uno si todavia cabe en lo que queda
    del presupuesto. Nunca retrocede, por eso no garantiza el optimo; su
    papel aqui es solo dar una cota inferior rapida al backtracking.
    """
    seleccion = []
    utilidad = 0
    costo = 0
    restante = presupuesto

    for posicion, producto in enumerate(productos):
        if producto["precio"] <= restante:
            seleccion.append(producto)
            utilidad += utilidades[posicion]
            costo += producto["precio"]
            restante -= producto["precio"]

    return {"utilidad": utilidad, "costo": costo, "seleccion": seleccion}


def _explorar(productos, utilidades, cotas, indice, presupuesto_restante,
              carrito, utilidad_actual, costo_actual, mejor):
    """DFS con poda sobre el arbol de decisiones incluir / no incluir."""
    # Caso base: ya se decidio sobre todos los candidatos
    if indice == len(productos):
        if (utilidad_actual > mejor["utilidad"] or
                (utilidad_actual == mejor["utilidad"] and costo_actual < mejor["costo"])):
            mejor["utilidad"] = utilidad_actual
            mejor["costo"] = costo_actual
            mejor["seleccion"] = list(carrito)  # copia del contenido de la pila
        return

    # Poda de optimalidad
    if utilidad_actual + cotas[indice] < mejor["utilidad"]:
        return

    producto = productos[indice]
    precio = producto["precio"]

    # Opcion 1: incluir el producto (si cabe en el presupuesto restante)
    if precio <= presupuesto_restante:
        carrito.append(producto)  # push
        _explorar(
            productos, utilidades, cotas, indice + 1,
            presupuesto_restante - precio, carrito,
            utilidad_actual + utilidades[indice], costo_actual + precio, mejor,
        )
        carrito.pop()  # backtrack: pop en O(1)

    # Opcion 2: descartar el producto y seguir con el siguiente
    _explorar(
        productos, utilidades, cotas, indice + 1,
        presupuesto_restante, carrito,
        utilidad_actual, costo_actual, mejor,
    )
