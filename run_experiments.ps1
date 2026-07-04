$OutputFile = "resultados_experimentos.csv"

# Escribimos la cabecera
"algoritmo;tipo_clave;numElementos;tiempo_segundos" | Out-File -FilePath $OutputFile -Encoding utf8

Write-Host "Iniciando experimentos. Por favor espera..."

# Repetiremos los experimentos 20 veces
for ($c = 1; $c -le 20; $c++) {
    Write-Host "Ejecutando iteracion $c de 20..."
    
    # Pruebas para la clave user_id (long long)
    .\main.exe unordered_map id >> $OutputFile
    .\main.exe abierto id >> $OutputFile
    .\main.exe cerrado_linear id >> $OutputFile
    .\main.exe cerrado_quadratic id >> $OutputFile
    .\main.exe cerrado_double id >> $OutputFile

    # Pruebas para la clave user_screen_name (string)
    .\main.exe unordered_map name >> $OutputFile
    .\main.exe abierto name >> $OutputFile
    .\main.exe cerrado_linear name >> $OutputFile
    .\main.exe cerrado_quadratic name >> $OutputFile
    .\main.exe cerrado_double name >> $OutputFile
}

Write-Host "¡Experimentos completados! Resultados en $OutputFile"