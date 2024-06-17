#include "funciones_foster.h"

void imprimir_seleccionados(lista_ninio_t ninio){

    printf("Usted busca una migo cuyas especificaciones son:\n");
    printf("Color: %s\n", ninio.color);
    printf("Altura: %c%i\n", ninio.comparacion, ninio.altura);
    printf("Debe ser: %s\n", ninio.virtud);
    printf("No debe ser: %s\n", ninio.defecto);  
    printf("Entonces sus opciones son:\n");
    printf("\n");
}

int modificar_estado(char ruta_archivo_dat[MAX_NOMBRE], amigo_t amigo_a_modificar, long unsigned int posicion){

    FILE * arhcivo_modificar = fopen(ruta_archivo_dat, "r+");

    if(arhcivo_modificar == NULL){
        printf("Error al leer el archivo %s.\n", ruta_archivo_dat);
        return -1;
    }

    fseek(arhcivo_modificar, (long int)((posicion)*sizeof(amigo_t)), SEEK_SET);
    fread(&amigo_a_modificar, sizeof(amigo_t), 1, arhcivo_modificar);

    amigo_a_modificar.esta_en_mansion = false;

    (long unsigned int)fseek(arhcivo_modificar, -1*((int)sizeof(amigo_t)), SEEK_CUR);

    fwrite(&amigo_a_modificar, sizeof(amigo_t), 1, arhcivo_modificar);


    fclose(arhcivo_modificar);

    return 0;
}

void agregar_a_lista(char amigo_agregado[MAX_NOMBRE], char ruta_archivo_txt[MAX_NOMBRE]){

    FILE * archivo_ninio = fopen(ruta_archivo_txt, "a");

    if(archivo_ninio == NULL){
        printf("Error al leer el archivo %s.\n", ruta_archivo_txt);
        return;
    }

    printf("%s\n", amigo_agregado);

    fprintf(archivo_ninio, "\n");
    fprintf(archivo_ninio, "%s", amigo_agregado);

    fclose(archivo_ninio);

}

int elegir_amigo(amigo_t amigo, los_elegidos_t amigos_seleccionados[MAX_AMIGOS], numero_amigo_t amigo_posicion[MAX_AMIGOS], int tope_posicion, int tope_amigos_seleccionados, char nuevo_amigo[MAX_NOMBRE], char ruta_archivo_dat[MAX_NOMBRE], char ruta_archivo_txt[MAX_NOMBRE]){

    long unsigned int posicion;

    if(tope_amigos_seleccionados > 1){
        for(int i = 0; i < tope_amigos_seleccionados; i++){
            if((i + 1) == tope_amigos_seleccionados){
                break;
            }
            if(strcmp(amigos_seleccionados[i].nombre , amigos_seleccionados[i + 1].nombre) < 1){
                strcpy(nuevo_amigo, amigos_seleccionados[i + 1].nombre);
            }
        }
        printf("Por orden alfabético, el nuevo amigo es: %s\n", nuevo_amigo);
    }
    else if(tope_amigos_seleccionados == 0){
        printf("No hay ningún amigo que cumpla esas especificaciones.\n");
        printf("No se eligió a ningun amigo.\n");
    }
    else if(tope_amigos_seleccionados == 1){
        strcpy(nuevo_amigo, amigos_seleccionados[0].nombre);
        printf("El nuevo amigo es: %s\n", nuevo_amigo);
    }
    
    
    for(long unsigned int i = 0; i < tope_posicion; i++){
        if(tope_amigos_seleccionados >= 1){
            if(strcmp(amigo_posicion[i].nombre, nuevo_amigo) == 0){
                posicion = i;
                modificar_estado(ruta_archivo_dat, amigo, posicion);
            }
        }
        
    }
    
    if(tope_amigos_seleccionados >= 1){
        agregar_a_lista(nuevo_amigo, ruta_archivo_txt);
    }



    return (int)posicion;
}

int comparacion_amigos(los_elegidos_t amigos_seleccionados[MAX_AMIGOS], lista_ninio_t ninio, char ruta_archivo_dat[MAX_NOMBRE], char ruta_archivo_txt[MAX_NOMBRE]){

    amigo_t amigo;
    numero_amigo_t amigo_posicion[MAX_AMIGOS];
    int tope_posicion = 0;
    int tope_amigos_seleccionados = 0;
    int contador_virtudes = 0;
    int contador_defectos = 0;
    int contador_nombres = 0;
    char nuevo_amigo[MAX_NOMBRE];

    FILE * archivo_amigos = fopen(ruta_archivo_dat, "r");

    if(archivo_amigos == NULL){
        printf("Error al leer el archivo %s.\n", ruta_archivo_dat);
        return -1;
    }

    long unsigned int leidos_amigos = fread(&amigo, sizeof(amigo_t), 1, archivo_amigos);

     while(leidos_amigos == 1){

        
        if(strcmp(amigo.color, ninio.color) == 0){
            if(((ninio.altura == amigo.altura) && (ninio.comparacion == IGUAL)) || ((amigo.altura >= ninio.altura) && (ninio.comparacion == MAYOR)) || ((amigo.altura <= ninio.altura) && (ninio.comparacion == MENOR))){ 
                for(int i = 0; i < amigo.tope_virtudes; i++){
                    for(int j = 0; j < amigo.tope_defectos; j++){
                        if(strcmp(ninio.virtud, amigo.virtudes[i].descripcion) == 0 || strcmp(ninio.defecto, amigo.defectos[j].descripcion) == 0){
                            if(strcmp(ninio.virtud, amigo.virtudes[i].descripcion) == 0){
                                contador_virtudes ++;
                            }
                            if(strcmp(ninio.defecto, amigo.defectos[j].descripcion) == 0){
                                contador_defectos ++;
                            }    
                        }
                    }
                }
                
                if(contador_virtudes > 0 && contador_defectos == 0){
                    printf("%s\n", amigo.nombre);
                    for(int i = 0; i < ninio.tope_examigo; i++){
                        if(strcmp(amigo.nombre, ninio.ex_amigo[i].nombre) == 0){
                        contador_nombres ++;
                        }
                    }
                    if(contador_nombres > 0){
                        printf("Ya tuvo al amigo %s.\n", amigo.nombre);
                    }
                    if(contador_nombres == 0 && amigo.esta_en_mansion == false){
                        printf("%s ya no se encuentra en la mansión.\n", amigo.nombre);
                    }
                    else if(contador_nombres == 0 && amigo.esta_en_mansion != false){
                        
                        
                        strcpy(amigos_seleccionados[tope_amigos_seleccionados].nombre, amigo.nombre);
                        tope_amigos_seleccionados ++;
                        
                        
                    }
                    
                }
            
            }
        }
        contador_nombres = 0;
        contador_virtudes = 0;
        contador_defectos = 0;

        

        strcpy(amigo_posicion[tope_posicion].nombre, amigo.nombre);
        tope_posicion++;

        leidos_amigos = fread(&amigo, sizeof(amigo_t), 1, archivo_amigos);
    }

    elegir_amigo(amigo, amigos_seleccionados, amigo_posicion, tope_posicion, tope_amigos_seleccionados, nuevo_amigo, ruta_archivo_dat, ruta_archivo_txt);

    fclose(archivo_amigos);

    return 0;



}

int devolver_amigo(amigo_t amigo, char amigo_devolver[MAX_NOMBRE], char ruta_archivo_dat[MAX_NOMBRE]){

    FILE * archivo_amigo = fopen(ruta_archivo_dat, "r+");
    int contador_posiciones = 0;
    int posicion = -1;

    if(archivo_amigo == NULL){
        printf("Error al leer el archvio %s.\n", ruta_archivo_dat);
        return -1;
    }

    long unsigned int leidos = fread(&amigo, sizeof(amigo_t), 1, archivo_amigo);

    while(leidos == 1){

        if(strcmp(amigo_devolver, amigo.nombre) == 0 && amigo.esta_en_mansion == false){
            
            printf("Se acaba de devolver a %s a la mansión, se actualizaran sus datos.\n", amigo.nombre);
            posicion = contador_posiciones;
        }

        leidos = fread(&amigo, sizeof(amigo_t), 1, archivo_amigo);
        contador_posiciones += 1;
    }

    if(posicion == -1 && amigo_devolver != amigo.nombre){
        printf("%s no se puede devolver.\n", amigo_devolver);
    }

    



    fseek(archivo_amigo, (long int)((posicion)*(int)sizeof(amigo_t)), SEEK_SET);
    fread(&amigo, sizeof(amigo_t), 1, archivo_amigo);

    amigo.esta_en_mansion = true;

    (long unsigned int)fseek(archivo_amigo, -1*((int)sizeof(amigo_t)), SEEK_CUR);

    fwrite(&amigo, sizeof(amigo_t), 1, archivo_amigo);


    fclose(archivo_amigo);


    return 0;


}

int escribir_amigos_mansion(char ruta_archivo_dat[MAX_NOMBRE]){
    
    amigo_t amigo;
    FILE * archivo_amigos = fopen(ruta_archivo_dat, "w");

    if(archivo_amigos == NULL){
        printf("Error al crear el archivo %s.\n", ruta_archivo_dat);
        return -1;
    }

    strcpy(amigo.nombre, "Amel");
    strcpy(amigo.color, "Blanco");
    amigo.altura = 140;
    amigo.esta_en_mansion = true;
    strcpy(amigo.virtudes[0].descripcion, "Divertido");
    strcpy(amigo.virtudes[1].descripcion, "Pacifico");
    strcpy(amigo.defectos[0].descripcion, "Irritable");
    amigo.tope_virtudes = 2;
    amigo.tope_defectos = 1;
    fwrite(&amigo, sizeof(amigo), 1, archivo_amigos);


    strcpy(amigo.nombre, "Blue");
    strcpy(amigo.color, "Azul");
    amigo.altura = 60;
    amigo.esta_en_mansion = true;
    strcpy(amigo.virtudes[0].descripcion, "Copado");
    strcpy(amigo.virtudes[1].descripcion, "Astuto");
    strcpy(amigo.defectos[0].descripcion, "Molesto");
    strcpy(amigo.defectos[1].descripcion, "Arrogante");
    strcpy(amigo.defectos[2].descripcion, "Antideportivo");
    amigo.tope_virtudes = 2;
    amigo.tope_defectos = 3;
    fwrite(&amigo, sizeof(amigo), 1, archivo_amigos);

    strcpy(amigo.nombre, "Coco");
    strcpy(amigo.color, "Amarillo");
    amigo.altura = 150;
    amigo.esta_en_mansion = true;
    strcpy(amigo.virtudes[0].descripcion, "Simpático");
    strcpy(amigo.virtudes[1].descripcion, "Astuto");
    strcpy(amigo.virtudes[2].descripcion, "Rápido");
    strcpy(amigo.defectos[0].descripcion, "Inetendible");
    strcpy(amigo.defectos[1].descripcion, "Raro");
    amigo.tope_virtudes = 3;
    amigo.tope_defectos = 2;
    fwrite(&amigo, sizeof(amigo), 1, archivo_amigos);

    strcpy(amigo.nombre, "Coraje");
    strcpy(amigo.color, "Rosa");
    amigo.altura = 50;
    amigo.esta_en_mansion = true;
    strcpy(amigo.virtudes[0].descripcion, "Valiente");
    strcpy(amigo.virtudes[1].descripcion, "Deportivo");
    strcpy(amigo.virtudes[2].descripcion, "Tierno");
    strcpy(amigo.defectos[0].descripcion, "No_es_imaginario");
    amigo.tope_virtudes = 3;
    amigo.tope_defectos = 1;
    fwrite(&amigo, sizeof(amigo), 1, archivo_amigos);

    strcpy(amigo.nombre, "Queso");
    strcpy(amigo.color, "Blanco");
    amigo.altura = 100;
    amigo.esta_en_mansion = true;
    strcpy(amigo.defectos[0].descripcion, "Insoportable");
    strcpy(amigo.defectos[1].descripcion, "Habla_mucho");
    strcpy(amigo.defectos[2].descripcion, "Raro");
    strcpy(amigo.defectos[3].descripcion, "Le_gusta_el_queso");
    amigo.tope_virtudes = 0;
    amigo.tope_defectos = 4;
    fwrite(&amigo, sizeof(amigo), 1, archivo_amigos);

    strcpy(amigo.nombre, "Willou");
    strcpy(amigo.color, "Rojo");
    amigo.altura = 200;
    amigo.esta_en_mansion = true;
    strcpy(amigo.virtudes[0].descripcion, "Deportivo");
    strcpy(amigo.virtudes[1].descripcion, "Confiable");
    strcpy(amigo.virtudes[2].descripcion, "Simpático");
    strcpy(amigo.defectos[0].descripcion, "Incompleto");
    amigo.tope_virtudes = 3;
    amigo.tope_defectos = 1;
    fwrite(&amigo, sizeof(amigo), 1, archivo_amigos);

    strcpy(amigo.nombre, "Zan");
    strcpy(amigo.color, "Rosa");
    amigo.altura = 200;
    amigo.esta_en_mansion = true;
    strcpy(amigo.virtudes[0].descripcion, "Deportivo");
    strcpy(amigo.defectos[0].descripcion, "Holgazan");
    amigo.tope_virtudes = 1;
    amigo.tope_defectos = 1;
    fwrite(&amigo, sizeof(amigo), 1, archivo_amigos);

    fclose(archivo_amigos);

    return 0;

}

int escribir_lista_ninio(char ruta_archivo_txt[MAX_NOMBRE]){

    lista_ninio_t ninio;
    FILE * archivo_ninios = fopen(ruta_archivo_txt, "w");
    char caracter;

    if(archivo_ninios == NULL){
        printf("Error al crear el archivo %s.\n", ruta_archivo_txt);
        return -1;
    }

    printf("Agregue las condiciones del niño:\n");

    printf("Color: \n");
    scanf(" %[^\n]", ninio.color);

    printf("Altura: \n");
    scanf("%i", &(ninio.altura));

    printf("Operador: (>, < o =)\n");
    scanf(" %c", &ninio.comparacion);

    printf("Virtud: \n");
    scanf(" %[^\n]", ninio.virtud);

    printf("Defecto: \n");
    scanf(" %[^\n]", ninio.defecto);
    
    fprintf(archivo_ninios, "%s; %c%i; %s; %s\n", ninio.color, ninio.comparacion, ninio.altura, ninio.virtud, ninio.defecto);

    printf("Agregue a los amigos imaginarios que tuvo el niño:\n");

     

    while(caracter != 'N'){
        

        scanf(" %[^\n]", ninio.ex_amigo->nombre);
        fprintf(archivo_ninios, "%s", ninio.ex_amigo->nombre);

        printf("Desea seguir agregando amigos? (S o N)\n");
        scanf(" %c", &caracter);
        fprintf(archivo_ninios, "\n");
    }

    fclose(archivo_ninios);
    
    return 0;

}

int listar_amigos(char ruta_archivo_dat[MAX_NOMBRE]){
    
    amigo_t amigo;

    FILE * archivo_amigo = fopen(ruta_archivo_dat, "r");

    if(archivo_amigo == NULL){
        printf("Error al leer el arvhivo %s.\n", ruta_archivo_dat);
        return -1;
    }

    long unsigned int leidos = fread(&amigo, sizeof(amigo_t), 1, archivo_amigo);

    printf("A continación se muetra una lista con todos los amigos que pertenecieron o estan en la mansión.\n");

    printf("Los campos de la misma son nombre del amigo, su color, su altura y si se encutrna en la mansión, en donde 1 indica si sigue estando y 0 si ya no esta, en este caso, este no se puede elegir y se descartara de sus opciones.\n");

    printf("\n");

    while(leidos == 1){

        printf("%s/ %s/ %i/ %i\n", amigo.nombre, amigo.color, amigo.altura, amigo.esta_en_mansion);
        for(int i = 0; i < amigo.tope_virtudes; i++){
            printf("Virtud: %s\n", amigo.virtudes[i].descripcion);
        }

        for(int i = 0; i < amigo.tope_defectos; i++){
            printf("Defecto: %s\n", amigo.defectos[i].descripcion);
        }
        
        printf("\n");
        leidos = fread(&amigo, sizeof(amigo_t), 1, archivo_amigo);
        
    }

    fclose(archivo_amigo);
    return 0;
}

int lista_ninio(char ruta_archivo_txt[MAX_NOMBRE]){

    FILE * archivo_ninio = fopen(ruta_archivo_txt, "r");
    char caracter;

    if(archivo_ninio == NULL){
        printf("Error al leer el archivo %s.\n", ruta_archivo_txt);
        return -1;
    }


    int leidos = fscanf(archivo_ninio, "%c", &caracter);

    while(leidos != EOF){

        printf("%c", caracter);
        leidos = fscanf(archivo_ninio, "%c", &caracter);
    }
    
    fclose(archivo_ninio);
    return 0;
}

int determinar_amigo(char ruta_archivo_dat[MAX_NOMBRE], char ruta_arhcivo_txt[MAX_NOMBRE]){

    
    lista_ninio_t ninio;
    los_elegidos_t amigos_seleccionados[MAX_AMIGOS];
    ninio.tope_examigo = 0;
    
    

    FILE * archivo_ninio = fopen(ruta_arhcivo_txt, "r");
    
    if(archivo_ninio == NULL){
        printf("Error al leer el archivo %s.\n", ruta_arhcivo_txt);
        return  -1;
    }
    

    fscanf(archivo_ninio, "%[^;]; %c%i; %[^;]; %s\n", ninio.color, &ninio.comparacion, &ninio.altura, ninio.virtud, ninio.defecto);
    
    int leidos_ninio = fscanf(archivo_ninio, "%s", ninio.ex_amigo[ninio.tope_examigo].nombre);
    
    while(leidos_ninio == 1){
      
        ninio.tope_examigo += 1;
        
        leidos_ninio = fscanf(archivo_ninio, "%s", ninio.ex_amigo[ninio.tope_examigo].nombre);
 
    }



    imprimir_seleccionados(ninio);

    comparacion_amigos(amigos_seleccionados, ninio, ruta_archivo_dat,  ruta_arhcivo_txt);

    fclose(archivo_ninio);
    return 0;
}