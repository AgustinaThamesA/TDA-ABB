#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

nodo_abb_t *nodo_crear(void *elemento){
	nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));
	if (nodo == NULL) {
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
	if (abb == NULL && comparador == NULL){
		free(abb);
		return NULL;
	}
	abb->comparador = comparador;
	abb->tamanio = 0;
	abb->nodo_raiz = NULL;
	return abb;
}

nodo_abb_t *abb_insertar_recursivo(abb_t *arbol, nodo_abb_t *nodo_actual, void *elemento){
	if (arbol == NULL || !(arbol->comparador))
		return NULL;
	
	if (nodo_actual == NULL) {
		nodo_abb_t *nodo_aux = nodo_crear(elemento);
		if (nodo_aux == NULL)
			return NULL;
		return nodo_aux;
	}

	if (arbol->comparador(elemento, nodo_actual->elemento) <= 0){
		nodo_actual->izquierda = abb_insertar_recursivo(arbol, nodo_actual->izquierda, elemento);
		if (nodo_actual->izquierda == NULL)
			return NULL;
	} else {
		nodo_actual->derecha = abb_insertar_recursivo(arbol, nodo_actual->derecha, elemento);
		if (nodo_actual->derecha == NULL)
			return NULL;
	}
		
	return nodo_actual;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento){
	if (arbol == NULL)
		return NULL;

	if (arbol->nodo_raiz == NULL) {
		nodo_abb_t* nodo_aux = nodo_crear(elemento);
		if (nodo_aux == NULL)
			return NULL;
		arbol->nodo_raiz = nodo_aux;
		arbol->tamanio = 1;
		return arbol;
	}
	
	
	arbol->nodo_raiz->izquierda = abb_insertar_recursivo(arbol, arbol->nodo_raiz->izquierda, elemento);
	(arbol->tamanio)++;
	return arbol;
}

nodo_abb_t *sacar_nodo_inorden(nodo_abb_t *nodo, void **eliminado){
	if (nodo->derecha == NULL) {
		*eliminado = nodo->elemento;
		nodo_abb_t *nodo_aux = nodo->izquierda;
		free(nodo);
		return nodo_aux;
	}

	nodo->derecha = sacar_nodo_inorden(nodo->derecha, eliminado);

	return nodo;
}

nodo_abb_t *abb_quitar_recursivo(abb_t *arbol, nodo_abb_t *nodo, void *elemento, void **eliminado){
	if (abb_vacio(arbol))
		return NULL;
	if (arbol->comparador(elemento, nodo->elemento) == 0) {
		*eliminado = nodo->elemento;

		if (nodo->izquierda != NULL && nodo->derecha != NULL){
			void *nodo_derecha = NULL;
			nodo->izquierda = sacar_nodo_inorden(nodo->izquierda, &nodo_derecha);
			nodo->elemento = nodo_derecha;
			return nodo;
		} else {
			free(nodo);
			if (nodo->izquierda == NULL)
				return nodo->derecha;
			return nodo->izquierda;
		}
	} else if (arbol->comparador(elemento, nodo->elemento) < 0) {
		nodo->izquierda = abb_quitar_recursivo(arbol, nodo->izquierda, elemento, eliminado);
	} else {
		nodo->derecha = abb_quitar_recursivo(arbol, nodo->derecha, elemento, eliminado);
	}
	return nodo;
}


void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;
	
	void *eliminado = NULL;

	if (elemento != abb_buscar(arbol, elemento))
		return NULL;

	arbol->nodo_raiz = abb_quitar_recursivo(arbol, arbol->nodo_raiz, elemento, &eliminado);
	(arbol->tamanio)--;

	return eliminado;
}

nodo_abb_t *buscar_nodo_abb(nodo_abb_t *nodo, void *elemento, abb_comparador comparador){
	if (nodo == NULL || comparador == NULL)
		return NULL;
	
	if (comparador(elemento, nodo->elemento) < 0)
		return buscar_nodo_abb(nodo->izquierda, elemento, comparador);

	if (comparador(elemento, nodo->elemento) > 0)
		return buscar_nodo_abb(nodo->derecha, elemento, comparador);
	else
		return nodo;
}


void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (abb_vacio(arbol))
		return NULL;
	
	nodo_abb_t *nodo_buscado = buscar_nodo_abb(arbol->nodo_raiz, elemento, arbol->comparador);
	if (nodo_buscado == NULL)
		return NULL;
	//return nodo_buscado->elemento;
	return elemento;
}


bool abb_vacio(abb_t *arbol)
{
	return (arbol == NULL || arbol->nodo_raiz == NULL || abb_tamanio(arbol) == 0);
}

size_t abb_tamanio(abb_t *arbol)
{
	if (arbol == NULL)
		return 0;
	return arbol->tamanio;
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
