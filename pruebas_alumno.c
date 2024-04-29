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
	cosa_t *c = (cosa_t *)malloc(sizeof(cosa_t));
	if (c)
		c->clave = clave;
	return c;
}

int comparador(void *elemento1, void *elemento2){
	if (elemento1 == NULL || elemento2 == NULL || ((cosa_t*)elemento1)->clave == ((cosa_t*)elemento2)->clave)
		return 0;
	if (((cosa_t*)elemento1)->clave > ((cosa_t*)elemento2)->clave)
		return 1;
	return -1;
}

void destruir_elemento(void *elemento){
	if (elemento == NULL)
		return;
	free(elemento);
}

void crear_arbol_devuelve_arbol_con_nodos_null(){
	abb_t *abb = abb_crear(NULL);
	pa2m_afirmar(abb_vacio(abb) && abb_tamanio(abb) == 0, "Se crea árbol vacío y con tamaño 0.");
	abb_destruir(abb);
}

void inserta_raiz(){
	abb_t *abb = NULL;
	cosa_t *prueba_100 = crear_cosa(100);
	abb_t *prueba = abb_insertar(abb, prueba_100);
	pa2m_afirmar(prueba == 0, "No se puede insertar en un árbol nulo.");
	destruir_elemento(prueba_100);

	abb = abb_crear(NULL);

	cosa_t *prueba_1 = crear_cosa(1);
	cosa_t *prueba_2 = crear_cosa(2);
	cosa_t *prueba_3 = crear_cosa(3);
	cosa_t *prueba_4 = crear_cosa(4);
	cosa_t *prueba_5 = crear_cosa(5);
	cosa_t *prueba_6 = crear_cosa(6);

	prueba = abb_insertar(abb, prueba_3);

	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 1, "Inserta correctamente la raíz del árbol.");
	
	abb_insertar(abb, prueba_2);
	abb_insertar(abb, prueba_1);
	abb_insertar(abb, prueba_6);
	abb_insertar(abb, prueba_4);
	prueba = abb_insertar(abb, prueba_5);
	pa2m_afirmar(!abb_vacio(abb) && abb_tamanio(abb) == 6, "Inserta correctamente 5 elementos a un árbol que ya tiene raíz.");

	destruir_elemento(prueba_1);
	destruir_elemento(prueba_2);
	destruir_elemento(prueba_3);
	destruir_elemento(prueba_4);
	destruir_elemento(prueba_5);
	destruir_elemento(prueba_6);
	abb_destruir(prueba);
	abb_destruir(abb);
}


int main()
{
	pa2m_nuevo_grupo(
		"\n======================== Pruebas creación ========================");
	crear_arbol_devuelve_arbol_con_nodos_null();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas inserción ========================");
	inserta_raiz();


	pa2m_nuevo_grupo(
		"\n======================== Pruebas eliminación ========================");

	pa2m_nuevo_grupo(
		"\n======================== Pruebas recorrer ========================");
	
	pa2m_nuevo_grupo(
		"\n======================== Pruebas destruir todo ========================");

	return pa2m_mostrar_reporte();
}
