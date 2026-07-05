# Entregable 3: Tablas Hash

## 👥 Integrantes
- Matías Cuello
- Marco Liguempi

---

## 💻 Instalación, compilación y ejecución

### 1. Clonar el repositorio

```bash
git clone https://github.com/marquinhos03/edd-entregable3.git
cd edd-entregable3
```

### 2. Compilación y Ejecución

Se puede compilar y ejecutar tanto de forma individual (para probar una implementación de Tabla Hash específica) como de forma automatizada (para correr todo el estudio experimental).

#### 🐧 2.1 Linux

- **Compilación:**

```bash
g++ main.cpp -o main
```

- **Ejecución de un experimento individual:**
Se deben pasar dos argumentos: el tipo de tabla hash y el tipo de clave.

```bash
./main <tipo_tabla> <tipo_clave>
# Ejemplo: ./main abierto id
```

- **Ejecución automatizada (Estudio completo):**

```bash
chmod +x run_experiments.sh
./run_experiments.sh
```

---

## ⚙️ Parámetros válidos para ejecución individual

Al ejecutar `./main` manualmente, se debe elegir una combinación de los siguientes parámetros:

- `<tipo_tabla>` validos:
    - `unordered_map` (Librería estándar STL)
    - `abierto` (Hashing Abierto por encadenamiento)
    - `cerrado_linear` (Hashing Cerrado - Linear Probing)
    - `cerrado_quadratic` (Hashing Cerrado - Quadratic Probing)
    - `cerrado_double` (Hashing Cerrado - Double Hashing)
- `<tipo_clave>` validos:
    - `id` (Usa la columna `user_id` de tipo `long long`)
    - `name` (Usa la columna `user_screen_name` de tipo `string`)