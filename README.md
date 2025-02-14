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

En este TDA se implementa el Árbol Binario de Búsqueda (ABB). Fueron desarrolladas las funciones especificadas en el archivo abb.h, y se crearon algunas nuevas para favorecer la implementación del TDA. En su mayoría, se utilizaron estructuras recursivas para facilitar la redacción y comprensión del código. Las operaciones generales, que se pueden hacer con los elementos del abb ó con el abb, implementadas son: crear, insertar, borrar, buscar, recorrer y destruir. El resto de las funciones son empleadas en las funciones generales (y en las pruebas) para comprobar casos bordes, o hasta formar una condición.

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

Los siguientes diagramas son un ejemplo de cómo fue pensado el algoritmo del TDA.

Por un lado, un ejemplo de diagrama de flujo (en este caso el de inserción), en donde se emplea recursión y se tienen en cuenta los casos bordes.

<div align="center">
<img width="70%" src="img/diagrama_flujo_insercion_abb.drawio.svg">
</div>

Por el otro, un diagrama que logra graficar cómo se utiliza el espacio de memoria en el programa, teniendo en cuenta los punteros correspondientes.

<div align="center">
<img width="70%" src="img/stack_heap_abb.drawio.svg">
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

- La complejidad de las operaciones mencionadas anteriormente en un ABB, es: **O(log(n))** ó O(n) en el caso de que el árbol esté desbalanceado. 

### 2. Explique su implementación y decisiones de diseño (por ejemplo, si tal o cuál funciones se plantearon de forma recursiva, iterativa o mixta y por qué, que dificultades encontró al manejar los nodos y punteros, reservar y liberar memoria, etc).

En líneas generales, considero que el código fue implementado mediante un buen manejo de nodos y punteros. En cuanto a la memoria, la dificultad generalmente aparecía en las pruebas, pero con la ejecución del código por Valgrind, se podían solucionar los errores de liberación de memoria.

#### Estructuras de Datos Utilizadas:
- **Nodo del Árbol (`nodo_abb_t`)**: Contiene un puntero al elemento que contiene, así como punteros a los hijos izquierdo y derecho.
- **Árbol Binario de Búsqueda (`abb_t`)**: Estructura principal que contiene un puntero a la raíz, el tamaño del árbol y una función comparadora.

#### Funciones Principales y Recursión:
La recursión ayuda a que mi código no utilice tantas estructuras iterativas, para lograr una mejor comprensión del código, y poder manejar las condiciones más fácilmente.
- **Inserción Recursiva**: `abb_insertar_recursivo` utiliza un enfoque recursivo para insertar elementos.
- **Borrado Recursivo**: `arbol_borrar_recursivo` elimina nodos recursivamente.
- **Recorrido Recursivo**: Funciones como `inorden_con_cada_elemento` utilizan la recursión para recorrer el árbol.

#### Estrategias de Borrado:
Fueron separados los 3 casos para que la implementación sea máz eficaz.
- **Borrado de Hojas**: `borrar_hoja` libera la memoria de un nodo hoja.
- **Borrado con 1 Hijo**: `borrar_1_hijo` maneja nodos con un solo hijo.
- **Borrado con 2 Hijos**: `borrar_2_hijos` aborda el caso de nodos con dos hijos.

#### Liberación de Memoria:
- **Destructor del Árbol y Nodos**: Funciones como `abb_destruir` y `abb_destruir_todo` liberan la memoria del abb correctamente. Luego el abb queda vacío.

#### Decisiones de Manejo de Punteros y Nodos:
- **Punteros Dobles**: Se utilizan punteros dobles en las funciones de borrado para modificar el puntero al nodo padre.
- **Validación de Punteros**: Se verifican los punteros pasados a las funciones para prevenir problemas de segmentación.
- **Asignación de Nodos**: Se asigna memoria dinámicamente para los nuevos nodos y se verifica la asignación.

#### Optimizaciones y Consideraciones:
- **Manejo de Tamaño del Árbol**: Se mantiene un contador de tamaño del árbol para operaciones eficientes.
- **Funciones de Recorrido Personalizables**: Se proporcionan funciones de recorrido que permiten al usuario especificar operaciones personalizadas en cada nodo.
