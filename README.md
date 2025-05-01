# TAREA 2 EDA

## **Profesor**
- **Cristian Alejandro Fuentes Rojas** <br>
  <cristian.fuentes.r@uai.cl>

## **Integrantes**
- **Vicente Concha, Martín González, Vicente Pulgar**

# **Tarea 2: Priorización de ciudades en riesgo sísmico**

## Solución desarrollada 
> **Tarea2-EDA**

- La solución que desarrollamos en esta tarea está enfocada en ordenar las ciudades en base al riesgo de terremoto, basándonos en información que obtuvimos de un CSV, el cual contiene el nivel de sismo y el porcentaje de riesgo de que pueda ocurrir dicho suceso. Luego de esto, ordenamos las ciudades por orden alfabético inverso (Z-A). Para poder desarrollar este sistema de priorización, utilizamos la siguiente estructura:

## 1. Procesamiento, ordenamiento y validación de los datos

### 1.1 Procesamiento de los datos

- En primer lugar, llamamos a nuestro CSV el cual contiene toda la información necesaria para poder realizar la priorización, el cual puede contener y manejar más de 1000 registros. si nos encontramos con datos faltantes, la priorización se basa en su nivel de sismo, por lo tanto los definiremos como alta(5-4), media(3) y baja(2-1) prioridad.

### 1.2 Ordenamiento de los datos

- Para el ordenamiento de los datos, utilizamos algoritmos de ordenamiento basados QuickSorting, los cuales nos ayudaron a clasificar nuestra infromación, ya que tenemos que tomar en cuenta el porcensaje de riesgo de que pueda ocurrir un sismo. Si los sismos contienen el mismo nivel de sismo, los comparamos por su porcentaje de riesgo. Finalmente, para tener un ordenamiento lógico y basado en las prioridades definidas. El ordenamiento de los datos es el siguiente, primero las ciudades que no tienen porcentaje de riesgo (nulos), estas dependiendo del riesgo (5.4.3,2 u 1) van ordenadas de distinta manera (arriba, almedio u abajo), luego los que tienen ambos datos. estos irán bajando progresivamente hasta el menor porcentaje. Las ciudades van ordenadas de manera alfabética  pero inverso.

### 1.3 Validación de los datos

- Finalmente, para poder validar que nuestros datos están bien estructurados, revisaremos si los valores utilizados en el nivel de sismo se manejen entre 1-5 y si nuestro porcentaje de riesgo se maneja entre 1-100%.

## 2. Implementación de funciones.

- para tener un buen manejo de datos, aparte de manejar los datos, tenemos que definir qué tipo de valores utilizaremos(int. float, char) para un buen manejo de nuestra información, definiendo nuestras funciones (.h) aparte, y luego las aplicamos a nuestro código (.c).

## 3. Compilación

- Por último, para poder compilar nuestro código, debemos utilizar la siguiente entrada:

./tarea2 input.csv (n° de ciudades a priorizar) output.txt

- De esta manera, nos entregará la cantidad de ciudades que hayamos definido clasificadas en base a su nivel sísmico y porcentaje de riesgo.
 
