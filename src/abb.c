#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

nodo_abb_t *nodo_crear(void *elemento){
	nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));
	if (nodo == NULL) {
		free(nodo);
		return NULL;
	}
	nodo->elemento = elemento;
	nodo->izquierda = NULL;
	nodo->derecha = NULL;
	return nodo;
}
 
abb_t *abb_crear(abb_comparador comparador)
{
	abb_t *abb = malloc(sizeof(abb_t));
	if (abb == NULL){
		free(abb);
		return NULL;
	}
	abb->comparador = comparador;
	abb->tamanio = 0;
	abb->nodo_raiz = NULL;
	return abb;
}

abb_t *abb_insertar_recursivo(abb_t *arbol, nodo_abb_t *nodo_actual, void *elemento){
	if (arbol == NULL || nodo_actual == NULL)
		return NULL;
	
	if (nodo_actual->izquierda == NULL && nodo_actual->derecha == NULL) {
		nodo_abb_t *nodo_aux = nodo_crear(elemento);
		if (nodo_aux == NULL)
			return NULL;
		nodo_actual->izquierda = nodo_aux;
		(arbol->tamanio)++;
		return arbol;
	}

	if (arbol->comparador(elemento, nodo_actual->elemento) <= 0){
		arbol = abb_insertar_recursivo(arbol, nodo_actual->izquierda, elemento);
		if (arbol == NULL)
			return NULL;
	} else {
		arbol = abb_insertar_recursivo(arbol, nodo_actual->derecha, elemento);
		if (arbol == NULL)
			return NULL;
	}
		
	return arbol;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento){
	if (arbol == NULL)
		return NULL;
	
	if (arbol->nodo_raiz == NULL) {
		arbol->nodo_raiz = nodo_crear(elemento);
		if (arbol->nodo_raiz == NULL)
			return NULL;
		arbol->tamanio = 1;
		return arbol;
	}
	arbol = abb_insertar_recursivo(arbol, elemento, arbol->nodo_raiz);
	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	return elemento;
}

nodo_abb_t *buscar_nodo_abb(nodo_abb_t *nodo, void *elemento, abb_comparador(comparador)){
	if (nodo == NULL || nodo->elemento == NULL)
		return NULL;
	
	if (comparador(elemento, nodo->elemento) <= 0)
		return buscar_nodo_abb(nodo->izquierda, elemento, comparador);
	
	if (comparador(elemento, nodo->elemento) > 0)
		return buscar_nodo_abb(nodo->derecha, elemento, comparador);
	
	return nodo;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (abb_vacio(arbol))
		return NULL;
	
	nodo_abb_t *nodo_a_buscar = buscar_nodo_abb(arbol->nodo_raiz, elemento, arbol->comparador);
	
	if (nodo_a_buscar == NULL || nodo_a_buscar->elemento == NULL)
		return NULL;
	
	return nodo_a_buscar->elemento;
}

bool abb_vacio(abb_t *arbol)
{
	return (arbol == NULL || arbol->nodo_raiz == NULL);
}

size_t abb_tamanio(abb_t *arbol)
{
	return (arbol == NULL) ? 0 : arbol->tamanio;
}

void destruir_nodo_abb(abb_t *arbol, nodo_abb_t *nodo){
	if (nodo == NULL || arbol == NULL)
		return;
	
	if (nodo->izquierda != NULL)
		destruir_nodo_abb(arbol, nodo->izquierda);
	
	if (nodo->derecha != NULL)
		destruir_nodo_abb(arbol, nodo->derecha);
	
	free(nodo);
}

void abb_destruir(abb_t *arbol)
{
	if (arbol == NULL)
		return;
	if (arbol->nodo_raiz != NULL){
		destruir_nodo_abb(arbol, arbol->nodo_raiz);
		free(arbol->nodo_raiz);
		arbol->nodo_raiz = NULL;
	}
		
	free(arbol);
}

void destruir_todo_nodo_abb(abb_t *arbol, nodo_abb_t *nodo, void (*destructor)(void *)){
	if (nodo == NULL || arbol == NULL)
		return;
	
	if (nodo->izquierda != NULL)
		destruir_todo_nodo_abb(arbol, nodo->izquierda, destructor);
	
	if (nodo->derecha != NULL)
		destruir_todo_nodo_abb(arbol, nodo->derecha, destructor);
	
	if (destructor != NULL && nodo->elemento != NULL)
		destructor(nodo->elemento);
	
	free(nodo);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == NULL)
		return;
	if (arbol->nodo_raiz)
		destruir_todo_nodo_abb(arbol, arbol->nodo_raiz, destructor);
	free(arbol);
}

size_t recorrido_inorden_con_cada_elem(nodo_abb_t *raiz, bool (*funcion)(void *, void *), size_t cantidad, void *aux, bool *recorrido_completo){
	if (raiz == NULL || (*recorrido_completo)) 
		return cantidad;
	
	if (raiz->izquierda)
		cantidad = recorrido_inorden_con_cada_elem(raiz->izquierda, funcion, cantidad, aux, recorrido_completo);
	
	if ((*recorrido_completo))
		return cantidad;
	
	(*recorrido_completo) = funcion(raiz->elemento, aux);
	cantidad++;

	if ((*recorrido_completo))
		return cantidad;
	
	if (raiz->derecha)
		cantidad = recorrido_inorden_con_cada_elem(raiz->derecha, funcion, cantidad, aux, recorrido_completo);

	return cantidad;
}

size_t recorrido_preorden_con_cada_elem(nodo_abb_t *raiz, bool (*funcion)(void *, void *), size_t cantidad, void *aux, bool *recorrido_completo){
	if (raiz == NULL || (*recorrido_completo)) 
		return cantidad;

	(*recorrido_completo) = funcion(raiz->elemento, aux);
	cantidad++;

	if ((*recorrido_completo))
		return cantidad;
	
	if (raiz->izquierda)
		cantidad = recorrido_preorden_con_cada_elem(raiz->izquierda, funcion, cantidad, aux, recorrido_completo);
	
	if ((*recorrido_completo))
		return cantidad;
	
	if (raiz->derecha)
		cantidad = recorrido_preorden_con_cada_elem(raiz->derecha, funcion, cantidad, aux, recorrido_completo);

	return cantidad;
}

size_t recorrido_postorden_con_cada_elem(nodo_abb_t *raiz, bool (*funcion)(void *, void *), size_t cantidad, void *aux, bool *recorrido_completo){
	if (raiz == NULL || (*recorrido_completo)) 
		return cantidad;
	
	if (raiz->izquierda)
		cantidad = recorrido_postorden_con_cada_elem(raiz->izquierda, funcion, cantidad, aux, recorrido_completo);
	
	if ((*recorrido_completo))
		return cantidad;
	
	if (raiz->derecha)
		cantidad = recorrido_postorden_con_cada_elem(raiz->derecha, funcion, cantidad, aux, recorrido_completo);

	(*recorrido_completo) = funcion(raiz->elemento, aux);
	cantidad++;

	if ((*recorrido_completo))
		return cantidad;

	return cantidad;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (arbol == NULL || arbol->nodo_raiz == NULL || funcion == NULL)
		return 0;
	
	size_t cant_veces_funcion = 0;
	bool *recorrido_completo = NULL;

	if (recorrido == INORDEN){
		recorrido_inorden_con_cada_elem(arbol->nodo_raiz, funcion, cant_veces_funcion, aux, recorrido_completo);
	} else if (recorrido == PREORDEN){
		recorrido_preorden_con_cada_elem(arbol->nodo_raiz, funcion, cant_veces_funcion, aux, recorrido_completo);
	} else if (recorrido == POSTORDEN){
		recorrido_postorden_con_cada_elem(arbol->nodo_raiz, funcion, cant_veces_funcion, aux, recorrido_completo);
	} 
	
	return cant_veces_funcion;
}

bool recorrido_inorden(nodo_abb_t *nodo, void **array, size_t tamanio_array, size_t *cant_almacenados){
	if (nodo == NULL)
		return true;

	bool hay_mas_elementos = recorrido_inorden(nodo->izquierda, array, tamanio_array, cant_almacenados);

	if(hay_mas_elementos == false)
		return false;

	if((*cant_almacenados) >= tamanio_array)
		return true;
	
	array[*cant_almacenados] = nodo->elemento;
	(*cant_almacenados)++;

	return recorrido_inorden(nodo->derecha, array, tamanio_array, cant_almacenados);
}

bool recorrido_preorden(nodo_abb_t *nodo, void **array, size_t tamanio_array, size_t *cant_almacenados){
	if (nodo == NULL || (*cant_almacenados) >= tamanio_array)
		return true;
	
	array[*cant_almacenados] = nodo->elemento;
	(*cant_almacenados)++;

	bool hay_mas_elementos = recorrido_preorden(nodo->izquierda, array, tamanio_array, cant_almacenados);

	if(hay_mas_elementos == false)
		return false;
	
	return recorrido_preorden(nodo->derecha, array, tamanio_array, cant_almacenados);
}

bool recorrido_postorden(nodo_abb_t *nodo, void **array, size_t tamanio_array, size_t *cant_almacenados){
	if (nodo == NULL)
		return true;

	bool hay_mas_elementos = recorrido_postorden(nodo->izquierda, array, tamanio_array, cant_almacenados);

	if(hay_mas_elementos == false)
		return false;

	if (recorrido_postorden(nodo->derecha, array, tamanio_array, cant_almacenados) == false)
		return false;

	if((*cant_almacenados) >= tamanio_array)
		return true;
	
	array[*cant_almacenados] = nodo->elemento;
	(*cant_almacenados)++;

	return true;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (arbol == NULL || tamanio_array == 0)
		return 0;

	size_t cant_almacenados = 0;

	if (recorrido == INORDEN){
		recorrido_inorden(arbol->nodo_raiz, array, tamanio_array, &cant_almacenados);
	} else if (recorrido == PREORDEN){
		recorrido_preorden(arbol->nodo_raiz, array, tamanio_array, &cant_almacenados);
	} else if (recorrido == POSTORDEN){
		recorrido_postorden(arbol->nodo_raiz, array, tamanio_array, &cant_almacenados);
	} 
	
	return cant_almacenados;
}
