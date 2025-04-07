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
