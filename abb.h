#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>


/* *****************************************************************
 *                    		 ABB
 * *****************************************************************/

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);

typedef void (*abb_destruir_dato_t) (void *);

// Crea una abb.
// Post: devuelve un abb vacio.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Agrega un nuevo elemento al abb. Devuelve falso en caso de error.
// Pre: el abb fue creado.
// Post: se agregó un nuevo elemento al abb, ordenado en la posicion que le corresponde
// del abb.
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

// Saca el elemento que contiene la clave ingresada por parametro y devuelve
// el dato. Si el abb no tiene elementos o la clave no se encuentra, devuelve NULL.
// Pre: el abb fue creado.
// Post: se devolvió el dato de la clave ingresada, en caso de encontrarse en el arbol
void *abb_borrar(abb_t *arbol, const char *clave);

// Obtiene el dato perteneciente a la clave recibida por parametro y lo devuelve
// En caso de hallarse vacia o no hallarse la clave, devuelve NULL.
// Pre: el abb fue creado.
// Post: se devolvió el dato perteneciente a la clave, en caso de hallarse en el arbol.
void *abb_obtener(const abb_t *arbol, const char *clave);

// Devuelve verdadero o falso en caso de que una clave se encuentre o no en el abb.
// Pre: el abb fue creado.
// Post: devuelve verdadero o falso si la clave esta o no en el abb.
bool abb_pertenece(const abb_t *arbol, const char *clave);

// Devuelve la cantidad de elementos que se encuentra en el abb.
// Pre: el abb fue creado.
// Post: se devolvio la cantidad de elementos.
size_t abb_cantidad(abb_t *arbol);

// Destruye el abb y todo su contenido.
// Pre: el abb fue creado.
// Post: se eliminaron todos los elementos del abb.
void abb_destruir(abb_t *arbol);

/* *****************************************************************
 *                    	ITER-ABB-EXTERNO
 * *****************************************************************/
 
typedef struct abb_iter abb_iter_t;

// Crea un iterador. Debe recibir una abb por parametro.
// Pre: el abb fue creado.
// Post: devuelve un iterador que recorrera el abb inorder,
// con la posicion actual en el nodo de menor valor.
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Avanza una posicion el abb. Si el iterador llega al final devuelve falso;
// en caso contrario devuelve verdadero.
// Pre: el iterador fue creado.
// Post: se avanzo un elemento en el abb, en cuanto esta operacion sea valida.
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Obtiene el dato del elemento actual en el que se encuentra el iterador.
// Si el abb se encuentra vacio o el iterador se halla al final, devuelve NULL.
// Pre: el iterador fue creado.
// Post: se devolvio el elemento actual del abb, en cuando no se halle vacio o al final.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Devuelve verdadero o falso, segun si el iterador se halla o no al final del abb.
// Pre: el iterador fue creado.
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: el iterador fue destruido.
void abb_iter_in_destruir(abb_iter_t* iter);

/* *****************************************************************
 *                    	ITER-ABB-INTERNO
 * *****************************************************************/

// Aplica la funcion recibida por parametro a cada elemento del abb,
// recorriendolo inorder.
// Pre: el abb y la funcion visitar fueron creadas.
// Post: la funcion visitar fue aplicada a cada elemento del abb inorder
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

#endif
