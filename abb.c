#define _XOPEN_SOURCE 500

#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "pila.h"

/* *****************************************************************
 *                    ESTRUCTURA DEL ABB
 * *****************************************************************/

typedef struct abb{
	struct nodo* raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
	size_t cant;
} abb_t;

typedef struct nodo{
	char* clave;
	void* dato;
	struct nodo* der;
	struct nodo* izq;
}nodo_t;


nodo_t* crear_nodo_doble(char* clave, void* dato);
char* strdup(const char *s);
void guardar_inorder(nodo_t* raiz, lista_t* lista);
void abb_inorder(abb_t *arbol);
nodo_t* buscar_nodo(nodo_t* actual,nodo_t** padre,const char* clave, abb_comparar_clave_t cmp);
nodo_t* minimo(nodo_t* raiz);
pila_t* pila_izq(const abb_t* arbol);

/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	
	abb_t* arbol = malloc(sizeof(abb_t));
	if(arbol==NULL)return NULL;
	arbol->raiz=NULL;
	arbol->cant=0;
	arbol->cmp=cmp;
	arbol->destruir_dato = destruir_dato;
	return arbol;
	
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	
	nodo_t* padre=NULL;
    nodo_t* nodo = buscar_nodo(arbol->raiz,&padre,clave, arbol->cmp);
    if(nodo){ //si está hay que cambiarle el dato
		void* dato_viejo= nodo->dato;
        nodo->dato=dato;
        if(arbol->destruir_dato)arbol->destruir_dato(dato_viejo); // si falla algo de memoria
    }
    else{
        nodo_t* nodo_nuevo = crear_nodo_doble(strdup(clave),dato);
        if(!nodo_nuevo)return false;
        arbol->cant++;
        if(padre){ //si tiene padre
            int result= arbol->cmp(padre->clave,clave);
            if(result >0){
                padre->izq=nodo_nuevo;
			}
			else{
				padre->der=nodo_nuevo;
			}
		}
		else{//no tiene padre osea recién empieza el árbol
			arbol->raiz=nodo_nuevo;
		}
	}
	abb_inorder(arbol);
	return true;
            
}

//intercambia nodos
void nodo_switch(nodo_t* *nodo_1,nodo_t* *nodo_2){
	char* clave_aux= (*nodo_1)->clave;
	void* dato_aux= (*nodo_1)->dato;
	(*nodo_1)->clave=(*nodo_2)->clave;
	(*nodo_1)->dato=(*nodo_2)->dato;
	(*nodo_2)->clave=clave_aux;
	(*nodo_2)->dato=dato_aux;
}


void borrar_nodo(nodo_t* nodo, nodo_t** padre, nodo_t** raiz,abb_t* arbol){
	//caso 1: no tiene hijos
	if(!(nodo)->der && !(nodo)->izq){
		if (*padre){
			int result= arbol->cmp((*padre)->clave,nodo->clave);
			if(result>0)(*padre)->izq= NULL;
			else{
				(*padre)->der=NULL;
			}
		}
		else{ //raiz
			*raiz=NULL;
		}
		free(nodo->clave);
		free(nodo); 
		return;
		
	}
	//caso 2 : tiene un solo hijo
	else if (!nodo->der || !nodo->izq) {
	//Al menos tien uno, asi que si entran aca es porque hay uno
		nodo_t* hijo = nodo->izq? nodo->izq : nodo->der;
		if (*padre){
			int result= arbol->cmp((*padre)->clave,nodo->clave);
			if (result > 0) (*padre)->izq = hijo;
			else (*padre)->der = hijo;
		}
		else{
			*raiz=hijo;		
		}
		free(nodo->clave);
		free(nodo);
		return;
	}
	//caso 3: tiende dos hijos
	else{
		nodo_t* nodo_aux= minimo((nodo)->der);
		char* clave= strdup(nodo_aux->clave); //copio?
		void* dato= nodo_aux->dato;
		abb_borrar(arbol,nodo_aux->clave); //revisar!!
		free(nodo->clave);
		nodo->clave=clave;
		nodo->dato=dato;
		
	}
}

void *abb_borrar(abb_t *arbol, const char *clave){ // ver si no tiene padre
	nodo_t* padre=NULL;
    nodo_t* nodo = buscar_nodo(arbol->raiz,&padre,clave, arbol->cmp);
    if(!nodo)return NULL; //no había nada que borrar
    //si llega aca es porque encontró el que se quiere borrar;
    arbol->cant--;
    void* dato= nodo->dato;
    if(arbol->cant==1){
		arbol->raiz=NULL;
		return dato;
	}
	borrar_nodo(nodo,&padre,&arbol->raiz,arbol);//tiene padre
	abb_inorder(arbol);
	return dato;
}



size_t abb_cantidad(abb_t *arbol){
	return arbol->cant;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	nodo_t* padre=NULL;
	nodo_t* nodo = buscar_nodo(arbol->raiz,&padre,clave,arbol->cmp);
	if(nodo){
		return nodo->dato;
	}
	else{
		return NULL;
	}
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	nodo_t* padre=NULL;
	nodo_t* nodo = buscar_nodo(arbol->raiz,&padre,clave,arbol->cmp);
	return nodo!=NULL;
}

void destruir(nodo_t* raiz, abb_destruir_dato_t destruir_dato){
	if(!raiz)return;
	destruir(raiz->izq,destruir_dato);
	destruir(raiz->der,destruir_dato);
	if(destruir_dato)destruir_dato(raiz->dato);
	free(raiz->clave);
	free(raiz);
}

void abb_destruir(abb_t *arbol){
	if(arbol->cant!=0){
		destruir(arbol->raiz,arbol->destruir_dato);
	}
	free(arbol);
}


/* *****************************************************************
 *                ESTRUCTURA DEL ITER EXTERNO ABB
 * *****************************************************************/

typedef struct abb_iter{
	nodo_t* actual;
	pila_t* pila;
	const abb_t* abb;	
}abb_iter_t;

/* *****************************************************************
 *                    PRIMITIVAS DEL ITER EXTERNO
 * *****************************************************************/
 
void pila_imprimir(pila_t* pila){
	if(pila_esta_vacia(pila))return;
	nodo_t* nodo=pila_desapilar(pila);
	printf("%s\n",nodo->clave);
	pila_imprimir(pila);
	pila_apilar(pila,nodo);
}


abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	abb_iter_t* iter= malloc(sizeof(abb_iter_t));
	iter->abb = arbol;
	pila_t* pila = pila_izq(arbol);
	if (!iter || !pila){
		return NULL;
	}
	iter->pila=pila;
	iter->actual = pila_desapilar(iter->pila);
	return iter;
}

void apilar_izq(pila_t* pila, nodo_t* raiz){
	if (!raiz){
		return;
	}
	pila_apilar(pila,raiz);
	apilar_izq(pila,raiz->izq);
}
	
pila_t* pila_izq(const abb_t* arbol){
	pila_t* pila = pila_crear();
	if (!pila || !arbol){
		return NULL;
	}
	apilar_izq(pila, arbol->raiz);
	return pila;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if(abb_iter_in_al_final(iter))return false;
	if(iter->actual->der){//si tiene derecho el actual
		printf("der:%s\n",iter->actual->der->clave);
		apilar_izq(iter->pila,iter->actual->der);
	}
	iter->actual=pila_desapilar(iter->pila);
	return true;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila);
}


const char *abb_iter_in_ver_actual(const abb_iter_t *iter){ //ver algún caso base
	if(abb_iter_in_al_final(iter))return NULL;
	return iter->actual->clave;
}

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITER INTERNO
 * *****************************************************************/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/* *****************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

nodo_t* crear_nodo_doble(char* clave, void* dato){
	
	nodo_t* nodo= malloc(sizeof(nodo_t));
	nodo->clave=clave;
	nodo->dato=dato;
	nodo->der=NULL;
	nodo->izq=NULL;
	return nodo;
}

char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   
    if (d == NULL) return NULL;          
    strcpy (d,s);                        
    return d;                            
}

/* *****************************************************************
 *                      FUNCIONES AUXILIARES PRUEBAS
 * *****************************************************************/
 
void guardar_inorder(nodo_t* raiz, lista_t* lista){
	if (!raiz) return;
	if(raiz->izq){
		guardar_inorder(raiz->izq,lista);
	}
	lista_insertar_ultimo(lista,raiz->clave);
	if(raiz->der){
		guardar_inorder(raiz->der,lista);
	}
}

void abb_inorder(abb_t *arbol){
	lista_t* lista = lista_crear();
	guardar_inorder(arbol->raiz, lista);
	lista_iter_t* iter=  lista_iter_crear(lista);
	while(!lista_iter_al_final(iter)){
		char* dato= lista_iter_ver_actual(iter);
		printf("%s\n",dato);
		lista_iter_avanzar(iter);
	}
	lista_destruir(lista,NULL);
	lista_iter_destruir(iter);
}

nodo_t* buscar_nodo(nodo_t* actual,nodo_t** padre,const char* clave, abb_comparar_clave_t cmp){
    if(!actual)return NULL;
    int result= cmp(actual->clave,clave);
    if(result==0){
        return actual;
    }
    (*padre)=actual;
    if(result >0){
        return buscar_nodo(actual->izq,padre,clave,cmp);
    }
    else{
        return buscar_nodo(actual->der,padre,clave,cmp);
    }
}

nodo_t* minimo(nodo_t* raiz){
	if(!(raiz)->izq)return raiz;
	return minimo(raiz->izq);
}
