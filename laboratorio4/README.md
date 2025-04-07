# Universidad Nacional de San Antonio Abad del Cusco
# Departamento Académico de Informática
# ALGORITMOS PARALELOS Y DISTRIBUIDOS

## Práctica No 4
## Profesor: HANS HARLEY CCACYAHUILLCA BEJAR
## Alumno: Efrain Vitorino Marin  Cod: 160337
## EJERCICIOS DE APLICACION

### 1. OBJETIVO.
*   Aplicar la programación paralela con OpenMP a la solución de problemas computacionalmente intensivos.
*   Evaluar el Speedup y la Eficiencia de un programa paralelo.
*   Utilizar adecuadamente las directivas de OpenMP para paralelizar un problema.

### 2. INTRODUCCION.
La computación paralela se aplica a algoritmos de cálculo intensivo para acelerar el cálculo u abordar problemas de mayor dimensión.

#### 2.1. Métricas para evaluar el desempeño de un sistema paralelo
Se evalúa con métricas como Speedup y Eficiencia, considerando el algoritmo y la arquitectura.

1.  ¿Qué algoritmo es más rápido?
2.  ¿Qué tan beneficioso es el paralelismo?
3.  ¿Cómo se comporta el algoritmo al variar características?

##### 2.1.1. Speedup.
Mide el beneficio de paralelizar, como el cociente del tiempo secuencial (T1) entre el tiempo paralelo (Tp) con p procesadores:

S<sub>p</sub> = T<sub>1</sub> / T<sub>p</sub>

Speedup absoluto (T1 con el mejor algoritmo secuencial) y relativo (T1 ejecutando el algoritmo paralelo con un sólo procesador).

##### 2.1.2. Eficiencia
Mide la fracción de tiempo eficaz de los procesadores:

E = S<sub>p</sub> / p

### 3. DESARROLLO DE LA PRÁCTICA

#### 3.1. MULTIPLICACION DE MATRICES.
Paralelismo de datos donde cada hilo trabaja con datos distintos, pero con el mismo algoritmo.

## Result Matrix C:
54 55 54 55 61 58 42 50 52 48 
40 58 40 56 47 51 45 42 50 42 
51 64 58 56 56 65 43 60 63 55 
60 66 60 61 56 77 45 65 69 60 
68 73 67 70 68 75 47 64 73 65 
68 77 70 71 72 76 49 69 75 65 
70 76 60 68 53 70 53 69 71 60 
73 77 66 79 66 82 60 71 75 66 
60 71 64 72 67 81 59 70 71 63 
66 68 61 59 52 70 49 70 64 59 

## Ejercicio 1 - Multiplicación de Matrices
[Enlace al código fuente](/ejersicio1.cpp)
Valor de n: 12

## Result Matrix C:
72 71 82 79 82 86 81 76 77 82 66 69 
76 83 89 80 93 95 74 84 77 94 75 77 
65 69 81 79 77 89 87 75 72 82 77 73 
67 68 79 70 85 87 70 73 68 85 66 65 
70 77 81 79 83 92 77 81 80 79 74 82 
99 107 122 113 122 136 122 115 110 121 110 111 
79 85 88 89 94 98 95 84 87 91 87 87 
58 63 67 71 70 80 81 61 64 71 65 70 
64 72 70 75 81 83 82 70 77 72 63 77 
58 78 83 77 90 95 84 79 73 84 78 78 
64 64 76 73 76 91 73 77 72 74 68 73 
70 70 86 82 77 90 89 76 74 84 81 73 
