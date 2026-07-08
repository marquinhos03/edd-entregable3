import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import re

print("1. Limpiando el archivo original desde cero...")
# Leer el archivo como texto crudo, ignorando errores de codificación
with open('resultados_experimentos.csv', 'r', encoding='utf-8', errors='ignore') as f_in:
    lineas = f_in.readlines()

lineas_limpias = []
for linea in lineas:
    # Esta expresión regular mantiene SOLO letras (\w), números, guiones bajos (_), puntos (.) y punto y coma (;)
    # Destruye cualquier espacio, tabulación, salto de línea mal formado o "byte nulo" invisible de C++.
    linea_limpia = re.sub(r'[^\w\.;]', '', linea)
    
    if linea_limpia: # Si la línea no quedó vacía tras la purga
        lineas_limpias.append(linea_limpia)

# Guardar un nuevo CSV totalmente limpio
with open('resultados_limpios.csv', 'w', encoding='utf-8') as f_out:
    for linea in lineas_limpias:
        f_out.write(linea + '\n')

print("2. Archivo 'resultados_limpios.csv' creado con éxito.")
print("3. Cargando datos limpios a Pandas...")
df = pd.read_csv('resultados_limpios.csv', sep=';')

# Convertir a numérico (ahora será 100% seguro porque los datos están prístinos)
df['num_elementos'] = pd.to_numeric(df['num_elementos'])
df['tiempo_segundos'] = pd.to_numeric(df['tiempo_segundos'])
df['espacio_bytes'] = pd.to_numeric(df['espacio_bytes'])

print("4. Así lucen los datos ahora (primeras 5 filas):")
print(df.head())

if df.empty:
    print("\nERROR: El DataFrame sigue vacío. Hay un problema grave con los datos base.")
else:
    print("\n5. Generando gráficas...")
    sns.set_theme(style="whitegrid")

    fig, axes = plt.subplots(2, 2, figsize=(16, 12))
    fig.suptitle('Análisis de Rendimiento: Tablas Hash', fontsize=18, fontweight='bold')

    # Gráfica 1
    sns.lineplot(data=df[df['tipo_clave'] == 'id'], x='num_elementos', y='tiempo_segundos', hue='tipo_tabla', marker='o', ax=axes[0, 0])
    axes[0, 0].set_title('Tiempo vs Elementos (Clave: ID)')
    axes[0, 0].set_xlabel('Número de Elementos')
    axes[0, 0].set_ylabel('Tiempo (segundos)')

    # Gráfica 2
    sns.lineplot(data=df[df['tipo_clave'] == 'name'], x='num_elementos', y='tiempo_segundos', hue='tipo_tabla', marker='o', ax=axes[0, 1])
    axes[0, 1].set_title('Tiempo vs Elementos (Clave: Name)')
    axes[0, 1].set_xlabel('Número de Elementos')
    axes[0, 1].set_ylabel('Tiempo (segundos)')

    # Gráfica 3
    sns.lineplot(data=df[df['tipo_clave'] == 'id'], x='num_elementos', y='espacio_bytes', hue='tipo_tabla', marker='o', ax=axes[1, 0])
    axes[1, 0].set_title('Espacio vs Elementos (Clave: ID)')
    axes[1, 0].set_xlabel('Número de Elementos')
    axes[1, 0].set_ylabel('Espacio (bytes)')

    # Gráfica 4
    sns.lineplot(data=df[df['tipo_clave'] == 'name'], x='num_elementos', y='espacio_bytes', hue='tipo_tabla', marker='o', ax=axes[1, 1])
    axes[1, 1].set_title('Espacio vs Elementos (Clave: Name)')
    axes[1, 1].set_xlabel('Número de Elementos')
    axes[1, 1].set_ylabel('Espacio (bytes)')

    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.savefig('graficas_resultados.png', dpi=300)
    plt.show()