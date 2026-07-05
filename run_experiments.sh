#!/bin/bash

# Archivo de salida
OUTPUT_FILE="resultados_experimentos.csv"

# Imprimimos la cabecera del CSV
echo "tipo_tabla;tipo_clave;numElementos;tiempo_segundos" > $OUTPUT_FILE

echo "Iniciando experimentos. Por favor espera..."

# Repetiremos los experimentos 20 veces según la rúbrica
for (( c=1; c<=20; c++ ))
do
    echo "Ejecutando iteración $c de 20..."
    
    # Pruebas para la clave user_id 
    ./main unordered_map id >> $OUTPUT_FILE
    ./main abierto id >> $OUTPUT_FILE
    ./main cerrado_linear id >> $OUTPUT_FILE
    ./main cerrado_quadratic id >> $OUTPUT_FILE
    ./main cerrado_double id >> $OUTPUT_FILE

    # Pruebas para la clave user_screen_name 
    ./main unordered_map name >> $OUTPUT_FILE
    ./main abierto name >> $OUTPUT_FILE
    ./main cerrado_linear name >> $OUTPUT_FILE
    ./main cerrado_quadratic name >> $OUTPUT_FILE
    ./main cerrado_double name >> $OUTPUT_FILE
done

echo "¡Experimentos completados! Resultados en $OUTPUT_FILE"