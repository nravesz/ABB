#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 



void prueba_crear_abb_vacio()
{
	printf("COMIENZO PRUEBAS ABB VACIO\n");
    abb_t* arbol = abb_crear(strcmp,NULL);

    print_test("Crear abb vacio", arbol);
    print_test("Abb vacío, la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    abb_destruir(arbol);
    print_test("El arbol se destruyó correctamente\n", true);
}

void prueba_abb_algunos_elementos()
{
	printf("\nCOMIENZO PRUEBAS ABB CON ELEMENTOS\n");
	
	abb_t* arbol = abb_crear(strcmp,NULL);
	
    char *clave1 = "perro", *valor1a = "guau" ;
    char *clave2 = "gato", *valor2a = "miau";
    char *clave3= "mama", *valor3a="love", *valor3b="hernaan";
    char *clave4 = "zorro", *valor4a = "gghuau";
	
	print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1a));
	print_test("Hay 1 elemento en el arbol", abb_cantidad(arbol) == 1);
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2a));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);
    print_test("Prueba abb insertar clave4", abb_guardar(arbol, clave4, valor4a));
    print_test("El primer dato ingresado corresponde a su clave", abb_obtener(arbol,clave1) == valor1a );
    print_test("La clave1 pertence al arbol", abb_pertenece(arbol,clave1));
    print_test("La clave2 pertence al arbol", abb_pertenece(arbol,clave2));
    print_test("La clave3 no pertence al arbol", abb_pertenece(arbol,clave3)==false);
    
    print_test("Elimino la clave1", abb_borrar(arbol,clave1)==valor1a);
    print_test("La clave1 ya no pertence al arbol", !abb_pertenece(arbol,clave2));
    print_test("La cantidad de elementos es 1", abb_cantidad(arbol) == 2);
    print_test("No puedo eliminar la clave3", abb_borrar(arbol,clave3)==NULL);
    print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3a));
    print_test("Elimino la clave1", abb_borrar(arbol,clave1)==valor1a);
    print_test("Prueba abb insertar clave3 on nuevo dato", abb_guardar(arbol, clave3, valor3b));
    print_test("La cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    
    abb_destruir(arbol);
    print_test("El arbol se destruyó correctamente\n", true);
}

void pruebas_abb_volumen()
{
	printf("\nCOMIENZO PRUEBAS ABB ITER\n");
	abb_t* arbol = abb_crear(strcmp,NULL);
	
	char *clave1 = "perro", *valor1a = "guau";
    char *clave2 = "gato", *valor2a = "miau";
    char *clave3= "mama", *valor3a="love";
    char *clave4 = "arco", *valor4a = "gghuau";
    char *clave5 = "abeja", *valor5a = "miafghu";
    char *clave6= "zorro", *valor6a="lofhgve";
	
	printf("Inserto varias cosas:\n");
	
	print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1a));
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2a));
	print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3a));
	print_test("Prueba abb insertar clave4", abb_guardar(arbol, clave4, valor4a));
	print_test("Prueba abb insertar clave5", abb_guardar(arbol, clave5, valor5a));
	print_test("Prueba abb insertar clave6", abb_guardar(arbol, clave6, valor6a));
	
	printf("Elimino los elementos:\n");
	
	print_test("Elimino la clave1", abb_borrar(arbol,clave1)==valor1a);
	print_test("Elimino la clave2", abb_borrar(arbol,clave1)==valor2a);
	print_test("Elimino la clave3", abb_borrar(arbol,clave1)==valor3a);
	print_test("Elimino la clave4", abb_borrar(arbol,clave1)==valor4a);
	print_test("Elimino la clave5", abb_borrar(arbol,clave1)==valor5a);
	print_test("Elimino la clave6", abb_borrar(arbol,clave1)==valor6a);
	
	
	abb_destruir(arbol);
    print_test("El arbol se destruyó correctamente\n", true);
	
}	
	
void pruebas_abb_iter()
{
	printf("\nCOMIENZO PRUEBAS ABB ITER\n");
	abb_t* arbol = abb_crear(strcmp,NULL);
	
	char *clave1 = "perro", *valor1a = "guau";
    char *clave2 = "gato", *valor2a = "miau";
    char *clave3= "mama", *valor3a="love";
    char *clave4 = "arco", *valor4a = "gghuau";
    char *clave5 = "abeja", *valor5a = "miafghu";
    char *clave6= "zorro", *valor6a="lofhgve";
	
	printf("Inserto varias cosas:\n");
	
	print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1a));
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2a));
	print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3a));
	print_test("Prueba abb insertar clave4", abb_guardar(arbol, clave4, valor4a));
	print_test("Prueba abb insertar clave5", abb_guardar(arbol, clave5, valor5a));
	print_test("Prueba abb insertar clave6", abb_guardar(arbol, clave6, valor6a));
	
	printf("Creo iter\n");
	
	abb_iter_t* iter= abb_iter_in_crear(arbol);
	
	print_test("Actual es el correcto", strcmp(abb_iter_in_ver_actual(iter),clave5)==0);
	print_test("El iter avanza",abb_iter_in_avanzar(iter));
	print_test("Actual es el correcto", strcmp(abb_iter_in_ver_actual(iter),clave4)==0);
	print_test("El iter avanza",abb_iter_in_avanzar(iter));
	print_test("Actual es el correcto", strcmp(abb_iter_in_ver_actual(iter),clave2)==0);
	print_test("El iter avanza",abb_iter_in_avanzar(iter));
	print_test("Actual es el correcto", strcmp(abb_iter_in_ver_actual(iter),clave3)==0);
	print_test("El iter avanza",abb_iter_in_avanzar(iter));
	print_test("El iter está al final",!abb_iter_in_avanzar(iter));
	
	abb_iter_in_destruir(iter);
	print_test("El iter se destruyó correctamente\n", true);
	
	abb_destruir(arbol);
    print_test("El arbol se destruyó correctamente\n", true);
	
}	

void pruebas_abb_alumno(){
	prueba_crear_abb_vacio();
	prueba_abb_algunos_elementos();
	pruebas_abb_volumen();
	pruebas_abb_iter();
}
