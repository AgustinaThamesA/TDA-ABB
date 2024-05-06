#include "pa2m.h"
#include "src/abb_estructura_privada.h"
#include "src/abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cosa {
	int clave;
	char contenido[10];
} cosa_t;

cosa_t *crear_cosa(int clave)
{
	cosa_t *c = calloc(1, sizeof(cosa_t));
	if (c == NULL)
		return NULL;
	c->clave = clave;
	return c;
}

int comparador(void *elemento1, void *elemento2)
{
	if (elemento1 == NULL || elemento2 == NULL)
		return 0;
	if (((cosa_t *)elemento1)->clave > ((cosa_t *)elemento2)->clave)
		return 1;
	if (((cosa_t *)elemento1)->clave < ((cosa_t *)elemento2)->clave)
		return -1;
	return 0;
}

void destruir_elemento(void *elemento)
{
	if (elemento == NULL)
		return;
	free(elemento);
}

void crear_arbol_devuelve_arbol_con_nodos_null()
{
	abb_t *abb = abb_crear(NULL);
	pa2m_afirmar(abb_vacio(abb) && abb_tamanio(abb) == 0,
		     "Se crea árbol vacío y con tamaño 0.");
	abb_destruir(abb);
}

void insertar_elementos()
{
	abb_t *abb = NULL;
	cosa_t *prueba_100 = crear_cosa(100);
	abb_t *prueba = abb_insertar(abb, prueba_100);
	pa2m_afirmar(prueba == 0, "No se puede insertar en un árbol nulo.");
	destruir_elemento(prueba_100);

	abb = abb_crear(comparador);

	cosa_t *prueba_1 = crear_cosa(1);
	cosa_t *prueba_2 = crear_cosa(2);
	cosa_t *prueba_3 = crear_cosa(3);
	cosa_t *prueba_4 = crear_cosa(4);
	cosa_t *prueba_5 = crear_cosa(5);
	cosa_t *prueba_6 = crear_cosa(6);

	abb_insertar(abb, prueba_3);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 1,
		     "Inserta correctamente la raíz del árbol.");

	abb_insertar(abb, prueba_2);
	abb_insertar(abb, prueba_1);
	abb_insertar(abb, prueba_6);
	abb_insertar(abb, prueba_4);
	abb_insertar(abb, prueba_5);

	pa2m_afirmar(
		!abb_vacio(abb) && abb_tamanio(abb) == 6,
		"Inserta correctamente 5 elementos a un árbol que ya tiene raíz.");

	destruir_elemento(prueba_1);
	destruir_elemento(prueba_2);
	destruir_elemento(prueba_3);
	destruir_elemento(prueba_4);
	destruir_elemento(prueba_5);
	destruir_elemento(prueba_6);

	abb_destruir(prueba);
	abb_destruir(abb);
}

void buscar_elementos()
{
	abb_t *abb = abb_crear(comparador);

	cosa_t *prueba_1 = crear_cosa(1);
	cosa_t *prueba_2 = crear_cosa(2);
	cosa_t *prueba_3 = crear_cosa(3);
	cosa_t *prueba_4 = crear_cosa(4);
	cosa_t *prueba_5 = crear_cosa(5);
	cosa_t *prueba_6 = crear_cosa(6);

	abb_insertar(abb, prueba_3);
	abb_insertar(abb, prueba_2);
	abb_insertar(abb, prueba_1);
	abb_insertar(abb, prueba_6);
	abb_insertar(abb, prueba_4);
	abb_insertar(abb, prueba_5);

	void *elemento_encontrado = abb_buscar(abb, &prueba_1->clave);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 6 &&
			     *(int *)elemento_encontrado == prueba_1->clave,
		     "El elemento 1 se encuentra en la raíz.");

	elemento_encontrado = abb_buscar(abb, &prueba_2->clave);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 6 &&
			     *(int *)elemento_encontrado == prueba_2->clave,
		     "El elemento 2 se encuentra en la raíz.");

	elemento_encontrado = abb_buscar(abb, &prueba_3->clave);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 6 &&
			     *(int *)elemento_encontrado == prueba_3->clave,
		     "El elemento 3 se encuentra en la raíz.");

	elemento_encontrado = abb_buscar(abb, &prueba_4->clave);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 6 &&
			     *(int *)elemento_encontrado == prueba_4->clave,
		     "El elemento 4 se encuentra en la raíz.");

	elemento_encontrado = abb_buscar(abb, &prueba_5->clave);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 6 &&
			     *(int *)elemento_encontrado == prueba_5->clave,
		     "El elemento 5 se encuentra en la raíz.");

	elemento_encontrado = abb_buscar(abb, &prueba_6->clave);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 6 &&
			     *(int *)elemento_encontrado == prueba_6->clave,
		     "El elemento 6 se encuentra en la raíz.");

	destruir_elemento(prueba_1);
	destruir_elemento(prueba_2);
	destruir_elemento(prueba_3);
	destruir_elemento(prueba_4);
	destruir_elemento(prueba_5);
	destruir_elemento(prueba_6);

	abb_destruir(abb);
}

void pruebas_borrar()
{
	abb_t *abb = abb_crear(comparador);

	cosa_t *prueba_1 = crear_cosa(1);
	cosa_t *prueba_2 = crear_cosa(2);
	cosa_t *prueba_3 = crear_cosa(3);
	cosa_t *prueba_4 = crear_cosa(4);
	cosa_t *prueba_5 = crear_cosa(5);
	cosa_t *prueba_6 = crear_cosa(6);
	cosa_t *prueba_7 = crear_cosa(7);

	abb_insertar(abb, prueba_3);
	abb_insertar(abb, prueba_2);
	abb_insertar(abb, prueba_1);
	abb_insertar(abb, prueba_6);
	abb_insertar(abb, prueba_4);
	abb_insertar(abb, prueba_5);
	abb_insertar(abb, prueba_7);

	void *elemento_eliminado = abb_quitar(abb, &prueba_6->clave);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 6 &&
			     *(int *)elemento_eliminado == prueba_6->clave,
		     "Saca correctamente el elemento 6 (con dos hijos).");

	elemento_eliminado = abb_quitar(abb, &prueba_2->clave);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 5 &&
			     *(int *)elemento_eliminado == prueba_2->clave,
		     "Saca correctamente el elemento 2 (con un hijo).");

	elemento_eliminado = abb_quitar(abb, &prueba_3->clave);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 4 &&
			     *(int *)elemento_eliminado == prueba_3->clave,
		     "Saca correctamente la raíz del árbol.");

	elemento_eliminado = abb_quitar(abb, &prueba_4->clave);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 3 &&
			     *(int *)elemento_eliminado == prueba_4->clave,
		     "Saca correctamente el elemento 4 (una hoja).");

	destruir_elemento(prueba_1);
	destruir_elemento(prueba_2);
	destruir_elemento(prueba_3);
	destruir_elemento(prueba_4);
	destruir_elemento(prueba_5);
	destruir_elemento(prueba_6);
	destruir_elemento(prueba_7);

	abb_destruir(abb);
}

void destructor(void *elemento)
{
	free(elemento);
}

void abb_destruir_todo_funcionalidad()
{
	abb_t *abb = abb_crear(comparador);
	int *prueba_1_pointer = malloc(sizeof(int));
	*prueba_1_pointer = 1;
	int *prueba_2_pointer = malloc(sizeof(int));
	*prueba_2_pointer = 2;
	abb_insertar(abb, prueba_1_pointer);
	abb_insertar(abb, prueba_2_pointer);

	pa2m_afirmar(
		!abb_vacio(abb) && abb_tamanio(abb) == 2,
		"Inserción correcta de elementos que usan memoria en el heap en abb "
		"con 2 elementos int que ocupan memoria del stack.");

	abb_destruir_todo(abb, destructor);
}

bool imprimir_abb_con_cada_elemento(void *elemento, void *aux)
{
	printf("%d ", *(int *)elemento);
	return true;
}

void abb_con_cada_elemento_funcionalidad()
{
	abb_t *abb = abb_crear(comparador);

	cosa_t *prueba_1 = crear_cosa(1);
	cosa_t *prueba_2 = crear_cosa(2);
	cosa_t *prueba_3 = crear_cosa(3);
	cosa_t *prueba_4 = crear_cosa(4);
	cosa_t *prueba_5 = crear_cosa(5);
	cosa_t *prueba_6 = crear_cosa(6);
	cosa_t *prueba_7 = crear_cosa(7);

	abb_insertar(abb, prueba_3);
	abb_insertar(abb, prueba_2);
	abb_insertar(abb, prueba_1);
	abb_insertar(abb, prueba_6);
	abb_insertar(abb, prueba_4);
	abb_insertar(abb, prueba_5);
	abb_insertar(abb, prueba_7);

	printf("Iteraciones de abb_con_cada_elemento:");
	printf("\n	Inorden: ");
	abb_con_cada_elemento(abb, INORDEN, imprimir_abb_con_cada_elemento,
			      NULL);

	printf("\n	Preorden: ");
	abb_con_cada_elemento(abb, PREORDEN, imprimir_abb_con_cada_elemento,
			      NULL);

	printf("\n	Postorden: ");
	abb_con_cada_elemento(abb, POSTORDEN, imprimir_abb_con_cada_elemento,
			      NULL);

	destruir_elemento(prueba_1);
	destruir_elemento(prueba_2);
	destruir_elemento(prueba_3);
	destruir_elemento(prueba_4);
	destruir_elemento(prueba_5);
	destruir_elemento(prueba_6);
	destruir_elemento(prueba_7);

	abb_destruir(abb);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== Pruebas creación ========================");
	crear_arbol_devuelve_arbol_con_nodos_null();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas inserción ========================");
	insertar_elementos();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas búsqueda ========================");
	buscar_elementos();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas eliminación ========================");
	pruebas_borrar();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas recorrer ========================");
	abb_con_cada_elemento_funcionalidad();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas destruir todo ========================");
	abb_destruir_todo_funcionalidad();

	// clang-format -i -style=file abb.c

	return pa2m_mostrar_reporte();
}
