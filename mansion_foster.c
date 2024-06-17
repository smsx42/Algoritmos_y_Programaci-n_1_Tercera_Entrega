#include "funciones_foster.h"

int main(int argc, char *argv[]){

    char ruta_archivo_txt[MAX_NOMBRE];
    char ruta_archivo_dat[MAX_NOMBRE];
    amigo_t amigo;
    char amigo_devolver[MAX_NOMBRE];
    
    
    if(argc == 1){
        return 0;
    }
    
    if(strcmp(argv[1], "listar_amigos") == 0){
        if(argc == 2){
            return 0;
        }
        strcpy(ruta_archivo_dat, argv[2]);
        listar_amigos(ruta_archivo_dat);
    }

    if(strcmp(argv[1], "lista_ninio") == 0){
        if(argc == 2){
            return 0;
        }
        strcpy(ruta_archivo_txt, argv[2]);
        lista_ninio(ruta_archivo_txt);
    }

    if(strcmp(argv[1], "determinar_amigo") == 0){
        if(argc == 2 || argc == 3){
            return 0;
        }
        strcpy(ruta_archivo_dat, argv[2]);
        strcpy(ruta_archivo_txt, argv [3]);
        determinar_amigo(ruta_archivo_dat, ruta_archivo_txt);
    }

    if(strcmp(argv[1], "escribir_amigos_mansion") == 0){
        if(argc == 2){
            return 0;
        }
        strcpy(ruta_archivo_dat, argv[2]);
        escribir_amigos_mansion(ruta_archivo_dat);
    }

    if(strcmp(argv[1], "escribir_lista_ninio") == 0){
        if(argc == 2){
            return 0;
        }
        strcpy(ruta_archivo_txt, argv[2]);
        escribir_lista_ninio(ruta_archivo_txt);
    }
    if(strcmp(argv[1], "devolver_amigo") == 0){
       if(argc == 2 || argc == 3){
            return 0;
        }
       strcpy(ruta_archivo_dat, argv[2]);
       strcpy(amigo_devolver, argv[3]);
       devolver_amigo(amigo, amigo_devolver, ruta_archivo_dat);          
    }

    
    return 0;
}