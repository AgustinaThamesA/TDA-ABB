# TDA ABB

## Repositorio de Agustina Thames Alderete - 111287 - athames@fi.uba.ar

A la hora de correr el programa, yo utilicé la línea para compilar y la línea de ejecución con valgrind, ya que el makefile ya tenía incorporada una forma más eficiente de hacerlo.

- Para ejecutar con valgrind usando mis pruebas:

```bash
make valgrind-alumno
```

- Para ejecutar con valgrind usando el archivo de ejemplo dado por la cátedra:
```bash
make 
```
---
##  Funcionamiento

### Funcionamiento general del programa:

En este TP se implementa el Árbol Binario de Búsqueda (ABB). Fueron desarrolladas las funciones especificadas en el archivo abb.h, y se crearon algunas nuevas para favorecer la implementación del TDA. En su mayoría, se utilizaron estructuras recursivas para facilitar la redacción y comprensión del código. Las operaciones generales, que se pueden hacer con los elementos del abb ó con el abb, implementadas son: crear, insertar, borrar, buscar, recorrer y destruir. El resto de las funciones son empleadas en las funciones generales (y en las pruebas) para comprobar casos bordes, o hasta formar una condición.

Una explicación a grandes rasgos de lo que hace mi implementación del TDA-ABB es:
- **nodo_crear**: función para crear un nuevo nodo, guardando el elemento pasado como parámetro y otros dos espacios para guardar los nodos izquierdo y derecho. Al finalizar todo, devuelve el nodo vacío.
- **abb_crear**: función para crear un nuevo abb, guardando el comparador, e inicializando el tamaño del mismo. Al finalizar todo, devuelve el abb vacío.
- **abb_insertar_recursivo**: función recursiva para insertar un elemento en el árbol. Busca la posición adecuada según el comparador y agrega el nuevo nodo.
- **abb_insertar**: función principal para insertar un elemento en el abb. Llama a abb_insertar_recursivo y actualiza el tamaño del árbol.
- **borrar_hoja, borrar_1_hijo, borrar_2_hijos, borrar_nodo**: son funciones auxiliares utilizadas para borrar nodos del abb, teniendo en cuenta diferentes casos (sin hijos, un hijo, dos hijos).
- **arbol_borrar_recursivo**: función recursiva para borrar un nodo del abb.
- **abb_quitar**: función principal para quitar un elemento del abb. Llama a arbol_borrar_recursivo y actualiza el tamaño del árbol.
- **buscar_nodo_abb**: función recursiva para buscar un elemento en el abb.
- **abb_buscar**: función principal para buscar un elemento en el abb. Llama a buscar_nodo_abb.
- **abb_vacio, abb_tamanio**: funciones para verificar si el árbol está vacío y obtener su tamaño.
- **destruir_nodo_abb**: función para destruir un nodo del abb.
- **abb_destruir**: función principal para destruir el abb, liberando memoria de todos los nodos.
- **destruir_todo_nodo_abb**: función para destruir un nodo del abb y sus elementos utilizando un destructor.
- **abb_destruir_todo**: función principal para destruir el abb y sus elementos utilizando un destructor.
inorden_con_cada_elemento, preorden_con_cada_elemento, postorden_con_cada_elemento: Funciones auxiliares para realizar un recorrido inorden, preorden o postorden del abb, aplicando una función a cada elemento.
- **abb_con_cada_elemento**: función principal para recorrer el abb en un orden específico y aplicar una función a cada elemento.
inorden_recorrer, preorden_recorrer, postorden_recorrer: Funciones auxiliares para realizar un recorrido inorden, preorden o postorden del abb y almacenar los elementos en un arreglo.
- **abb_recorrer_rec**: función recursiva para recorrer el abb en un orden específico y almacenar los elementos en un arreglo.
- **abb_recorrer**: función principal para recorrer el abb en un orden específico y almacenar los elementos en un arreglo.

### Diagramas relevantes:




### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
### 1. Explique teóricamente (y utilizando gráficos) qué es un árbol, árbol binario y árbol binario de búsqueda. Explique cómo funcionan, cuáles son sus operaciones básicas (incluyendo el análisis de complejidad de cada una de ellas) y por qué es importante la distinción de cada uno de estos diferentes tipos de árboles. Ayúdese con diagramas para explicar.

#### Árbol
Un árbol es una colección de nodos los cuales, a su vez, pueden estar conectados a múltiples nodos. Una de las características que lo destaca, es que facilita la búsqueda y la eliminación de un elemento (lo cual era mucho más complejo en el TDA de Lista).

Un árbol está compuesto por un nodo principal, llamado **nodo raíz**, y cero o muchos subárboles no vacíos, los cuales tienen su nodo raíz conectado mediante un vértice al nodo raíz.

<div align="center">
<img width="70%" src="img/estructura_arbol.drawio.svg">
</div>

Estando en un nodo, puedo ver los subárboles que se encuentran 'debajo' del mismo. En este caso, el nodo donde estamos parados es el **nodo padre**, y los nodos que se encuentran 'debajo' de este mismo serían sus **nodos hijos**. 

##### Casos especiales: 
- El nodo raíz no tiene padre
- **Hojas:** son aquellos nodos que no tienen hijos.

#### Árbol Binario
Son árboles relacionados a las operaciones de búsqueda, que tienen el objetivo de aproximarse a la búsqueda binaria. En este caso, el **nodo raíz está únicamente conectado con dos subárboles**, el subárbol izquierdo y el subárbol derecho.

<div align="center">
<img width="70%" src="img/estructura_abb.drawio.svg">
</div>

Las operaciones que se pueden realizar con un árbol binario son:
- Crear
- Destruir
- Insertar
- Borrar
- Buscar
- Vacío
- Recorrer

##### Recorridos
Para recorrer este tipo de árbol, hay tres posibles recorridos. En todos los casos, se llama recursivamente a la misma función que tiene las 3 acciones para hacer y se va comparando según el orden adecuado. (Por convención, 'N' es el nodo actual, 'D' es el subárbol derecho, e 'I' es el subárbol izquierdo):

- **Recorrido Preorden (NID)**: primero se visita N, después I y por último D. Cuando termina todos los subárboles izquierdos, 'vuelve uno atrás' y empieza a recorrer hacia abajo para la derecha, y así sucesivamente hasta que termina todos los nodos del árbol.
- **Recorrido Inorden (IND)**: primero se visita I, después N, y por último D. 
- **Recorrido Postorden (IDN)**: primero se visita I, después D, y por último N.

#### Árbol Binario de Búsqueda (ABB)
A diferencia del tipo explicado anteriormente, en este caso hay un orden, por lo que tenemos una forma de comparar los elementos para poder definir este orden y cada nodo del árbol posee un valor o una clave única.

Características:
- Las claves mayores se insertan en los subárboles derechos.
- Las claves menores se insertan en los subárboles izquierdos.
- Ambos subárboles también son ABBs.
- 'El hijo izquierdo siempre es menor que el nodo padre, y el hijo derecho siempre es mayor.'

##### Operaciones con ABBs
La **búsqueda** de un elemento comienza en el nodo raíz:
1. La clave buscada se compara con la clave del nodo raíz.
2. Si las claves son iguales, la búsqueda se detiene.
3. Si la clave buscada es mayor que la clave raíz, la búsqueda se reanuda en el subárbol derecho. Si la clave buscada es menor que la clave raíz, la búsqueda se reanuda en el subárbol izquierdo.

La **inserción**:
1. Comparo la clave del elemento a insertar con la clave del nodo raíz. Si es mayor, avanzo hacia el subárbol derecho, si es menor hacia el izquierdo.
2. Repetir el paso 1 hasta encontrar un elemento con clave igual o llegar al final del subárbol donde debo insertar el nuevo elemento.
3. Cuando se llega al final, creo un nuevo nodo, asignando NULL a los punteros izquierdo y derecho del mismo. Luego coloco el nuevo nodo como hijo izquierdo o derecho del anterior según sea el valor de la clave.

La **eliminación** (tomándose como ejemplo un árbol que tiene números enteros como elementos):
- *Borrar Nodo Hoja*: hago directamente la liberación de memoria de ese nodo.
- *Borrar Nodo con un Hijo*: hago que el nodo anterior al que quiero borrar apunte al nodo hijo, y luego libero la memoria del nodo que se desea.
- *Borrar Nodo con dos Hijos*: en este caso, elijo el sucesor o antecesro inmediato al número más cercano al que quiero borrar. Para encontrar el antecesor, voy a la rama izquierda y después todo a la derecha hasta encontrar una hoja (el antecesor). Por el contrario, para encontrar el sucesor, voy a la rama derecha y después todo a la izquierda hasta encontrar una hoja (el sucesor). El nodo encontrado es el que va a reemplazar al nodo a borrar. Por último, hago libero la memoria correspondiente.


### 2. Explique su implementación y decisiones de diseño (por ejemplo, si tal o cuál funciones se plantearon de forma recursiva, iterativa o mixta y por qué, que dificultades encontró al manejar los nodos y punteros, reservar y liberar memoria, etc).
