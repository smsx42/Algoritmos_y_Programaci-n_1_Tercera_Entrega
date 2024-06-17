#ifndef FUNCIONES_FOSTER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NOMBRE 50
#define MAX_COLOR 50
#define MAX_VIRTUDES 10
#define MAX_DEFECTOS 10
#define MAX_DESCRIPCION 200
#define MAX_AMIGOS 100

#define IGUAL '='
#define MAYOR '>'
#define MENOR '<'


typedef struct aspecto{
    char descripcion[MAX_DESCRIPCION];
}aspecto_t;

typedef struct fue_amigo{
    char nombre[MAX_NOMBRE];
}fue_amigo_t;

typedef struct numero_amigo{
    char nombre[MAX_NOMBRE];
}numero_amigo_t;

typedef struct los_elegidos{
    char nombre[MAX_NOMBRE];
}los_elegidos_t;

typedef struct amigo{
    char nombre[MAX_NOMBRE];
    char color[MAX_COLOR];
    int altura;
    aspecto_t virtudes[MAX_VIRTUDES];
    int tope_virtudes;
    aspecto_t defectos[MAX_DEFECTOS];
    int tope_defectos;
    bool esta_en_mansion;
}amigo_t;

typedef struct lista_ninio{
    char color[MAX_COLOR];
    int altura;
    char comparacion;
    char virtud[MAX_DESCRIPCION];
    char defecto[MAX_DESCRIPCION];
    fue_amigo_t ex_amigo[MAX_NOMBRE];
    int tope_examigo;
}lista_ninio_t;


/* Muestra por pantalla las especificaciones que debe cumplir un amigo.
*/
void imprimir_seleccionados(lista_ninio_t ninio);

/* Modifica el estado del amigo.
 * Devolverá -1 en el caso de que no se halla podido leer el archivo y 
 * devolverá el estado del amigo en el caso de que se halla elegido a un amigo.
*/  
int modificar_estado(char ruta_archivo_dat[MAX_NOMBRE], amigo_t amigo, long unsigned int posicion);

/* Agrega a la lista de los amigos que tuvo un niño una vez
 * elegido un amigo.
*/
void agregar_a_lista(char amigo_agregado[MAX_NOMBRE], char ruta_archivo_txt[MAX_NOMBRE]);

/* Determina e informa al usuario el amigo imaginario dependiendo las especificaciones dadas por el niño.
 * devolverá -1 en el caso de que no se halla elegido a ningun amigo, y se devolverá una valor de retorno que 
 * representa la posicion de un amigo en la lista de la mansión, si se eligió al amigo.
*/
int elegir_amigo(amigo_t amigo, los_elegidos_t amigos_seleccionados[MAX_AMIGOS], numero_amigo_t amigo_posicion[MAX_AMIGOS], int tope_posicion, int tope_amigos_seleccionados, char nuevo_amigo[MAX_NOMBRE], char ruta_archivo_dat [MAX_NOMBRE], char ruta_archivo_txt[MAX_NOMBRE]);


/* Realiza las comparaciones entre los elementos de la lista de amigos y a la lista del ninio.
 * Devolverá -1 en el caso de que no se halla podidio leer el archvio y
 * devolverá 0 en el caso de que se hallan podido realizar las comparaciones.
*/
int comparacion_amigos(los_elegidos_t amigos_seleccionados[MAX_AMIGOS], lista_ninio_t ninio, char ruta_archivo_dat[MAX_NOMBRE], char ruta_archivo_txt[MAX_NOMBRE]);


/* Se encargará de devolver a un amigo a la mansión; para ello se actualizaran los valores
 * de la lista de la mansión modificando su status. Devolverá -1 si no se pudo leer el
 * archivo y devolverá 0 si se puedo devolver al amigo.
*/
int devolver_amigo(amigo_t amigo, char amigo_devolver[MAX_NOMBRE], char ruta_archivo_dat[MAX_NOMBRE]);

/* Crea un archivo binario en forma de lista con todas las características de los amigos imaginarios de la mansion.
 * Devolverá -1 en el caso de que no se halla podido crear el archvio y 
 * devolverá 0  en el caso de que se halla podido crear.
*/
int escribir_amigos_mansion(char ruta_archivo_dat[MAX_NOMBRE]);

/* Le pregunta al usuario las especificaciones que debe tener el amigo para ser adoptado y los amigos
 * que tubo el niño; creara una un archivo de texto con dichas 
 * especificacions y listará a los amigos que tuvo el niño.
 * Devolverá -1 si no se pudo crear el archivo, y devolverá 0 si se puedo crear.
*/
int escribir_lista_ninio(char ruta_archivo_txt[MAX_NOMBRE]);

/* Imprime por pantalla una lista con todos los amigos del arhivo.dat, devuelve -1 si no se
 * pudo leer el arhcivo y 1 si se pudo imprimir.
*/ 
int listar_amigos(char ruta_archivo_dat[MAX_NOMBRE]);

/* Imprime por pantalla todas las especificaciones del niño y los nombres de los ex amigos, devuelve
 * -1 si no se pudo leer el archivo.txt y 0 si se pudo mostrar.
*/
int lista_ninio(char ruta_archivo_txt[MAX_NOMBRE]);

/* Determina y devuelve el nombre de un amigo imaginario perteneciante a la lista de amigos, si se cumplen todas especificaciones.
 * Devolverá -1 si no se pudo crear el archivo, y devolverá 0 si se puedo crear.
*/
int determinar_amigo(char ruta_archivo_dat[MAX_NOMBRE], char ruta_archivo_txt[MAX_NOMBRE]);



#endif /* __FUNCIONES_FOSTER_H__ */
