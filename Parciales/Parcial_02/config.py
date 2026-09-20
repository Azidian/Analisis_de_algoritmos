# Archivo de catalogo por defecto (se puede pasar otro por linea de comandos)
RUTA_CATALOGO_DEFECTO = "productos.csv"

# Productos mostrados por pantalla al asignar prioridades
TAMANO_BLOQUE = 10

# Tabla de utilidades: prioridad -> puntos. Desacopla la escala de
# prioridades del algoritmo de optimizacion.
TABLA_UTILIDAD = {1: 10, 2: 6, 3: 3}

# Texto legible de cada prioridad
TEXTO_PRIORIDAD = {1: "Alta", 2: "Media", 3: "Baja"}

# Columnas obligatorias del CSV
COLUMNAS_ESPERADAS = {"id", "nombre", "categoria", "presentacion", "precio"}

# Orden en que se muestran las categorias (las que no esten aqui van al
# final, en orden alfabetico)
ORDEN_CATEGORIAS = [
    "Granos",
    "Despensa",
    "Lacteos",
    "Carnes",
    "Frutas y Verduras",
    "Aseo",
    "Mekato",
    "Licores",
]
