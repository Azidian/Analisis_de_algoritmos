ANCHO = 62


def formatear_pesos(valor):
    """Formatea un entero como pesos colombianos: 60000 -> '$60.000'."""
    return "$" + f"{valor:,}".replace(",", ".")


def titulo(texto):
    """Titulo principal centrado entre lineas dobles."""
    print()
    print("=" * ANCHO)
    print(texto.upper().center(ANCHO))
    print("=" * ANCHO)


def subtitulo(texto):
    """Encabezado secundario, usado para cada categoria."""
    print(f"\n--- {texto} ---")


def separador():
    print("-" * ANCHO)


def pausar(mensaje="Presione ENTER para volver al menu..."):
    input(f"\n{mensaje}")


def contar_productos(cantidad):
    """'1 producto' / '8 productos'."""
    return f"{cantidad} producto" + ("" if cantidad == 1 else "s")


def confirmar(pregunta):
    """Pregunta si/no. Devuelve True solo si el usuario responde 's'."""
    return input(f"{pregunta} (s/n): ").strip().lower() == "s"
