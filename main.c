#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 4

struct Estudiante{

    int legajo;
    char nombre[20];
    float prom;
    char apellido[20];
};

typedef struct Estudiante * EstudiantePtr;

struct Materia{

    char nmat[20];
    int codigo;
    char turno[20];

    EstudiantePtr listaE[TAM];
};

typedef struct Materia * MateriaPtr;

void mostrarMat(MateriaPtr m);
MateriaPtr cargarMatTec();

void agregarEst(EstudiantePtr e[], int t);

void mostrarEst(EstudiantePtr est);
EstudiantePtr cargarEstTec();
EstudiantePtr cargarEst(int l, float p, char n[20], char a[20]);

///arreglo struct
void cargarEstudiantes(EstudiantePtr e[], int t);
void mostrarEstudiantes(EstudiantePtr e[], int t);

///ordenamiento de estudiantes
void ordenarLegajo(EstudiantePtr e[], int t);
void ordenarApellido(EstudiantePtr e[], int t);

///buscar estudiante
int buscarEst(EstudiantePtr e[], int t, int l);

///anidar struct
EstudiantePtr cargarEstNulo();
void cargarEstNulos(EstudiantePtr e[], int t);

void liberarEst(EstudiantePtr e[]);
void liberarEMat(MateriaPtr m[]);

void leerArchivo(MateriaPtr m);
void guardarDatos(MateriaPtr m);

int main(){

    printf("-----------------\n");

    MateriaPtr m1 = cargarMatTec();
    cargarEstNulos(m1->listaE, TAM);
    leerArchivo(m1);
    mostrarMat(m1);
    agregarEst(m1->listaE, TAM);
    mostrarMat(m1);
    guardarDatos(m1);

    return 0;
}

void mostrarMat(MateriaPtr m){

    printf("------------\n");
    printf("\nNombre: %s", m->nmat);
    printf("\nCodigo: %d", m->codigo);
    printf("\nTurno: %s", m->turno);

    mostrarEstudiantes(m->listaE,TAM);
};

MateriaPtr cargarMatTec(){

    MateriaPtr aux = (MateriaPtr) malloc(sizeof(struct Materia));

    printf("\nNombre de la materia: ");
    fflush(stdin);
    gets(aux->nmat);

    printf("\nCodigo de la materia: ");
    scanf("%d", &aux->codigo);

    printf("\nTurno: ");
    fflush(stdin);
    scanf("%c", aux->turno);

    cargarEstNulos(aux->listaE, TAM);

    return aux;
};

void agregarEst(EstudiantePtr e[], int t){

    int posVacia = -1;

    EstudiantePtr eAgregar = cargarEstTec();

    posVacia = buscarEst(e, TAM, -1);

    if (posVacia != -1){

        e[posVacia] = eAgregar;
    }
    else{

        printf("Ups! no hay mas cupos");
    }
};

///--------------------------

void mostrarEst(EstudiantePtr est){

    if(est->legajo != -1){

        printf("----------------\n");
        printf("\nNombre: %s", est->nombre);
        printf("\nApellido: %s", est->apellido);
        printf("\nLegajo: %d", est->legajo);
        printf("\nPromedio: %f", est->prom);
    }
};

EstudiantePtr cargarEstTec(){

    EstudiantePtr e = (EstudiantePtr) malloc(sizeof(struct Estudiante));

    printf("\nIngrese su nombre: ");
    fflush(stdin);
    gets(e->nombre);

    printf("\nIngrese su apellido: ");
    fflush(stdin);
    gets(e->apellido);

    printf("\nIngrese su n de legajo: ");
    scanf("%d", &e->legajo);

    printf("\nIngrese su promedio: ");
    scanf("%f", &e->prom);

    return e;
};

EstudiantePtr cargarEst(int l, float p, char n[20], char a[20]){

    EstudiantePtr e = (EstudiantePtr) malloc(sizeof(struct Estudiante));

    e->legajo = l;
    e->prom= p;
    strcpy(e->nombre, n);
    strcpy(e->apellido, a);

    return e;
};

///arreglo struct
void cargarEstudiantes(EstudiantePtr e[], int t){

    for(int i=0; i<t; i++){

        e[i] = cargarEstTec();
    }
};

void mostrarEstudiantes(EstudiantePtr e[], int t){

    for(int i=0; i<t; i++){

        mostrarEst(e[i]);
    }
};

///ordenamiento de estudiantes
void ordenarLegajo(EstudiantePtr e[], int t){

    EstudiantePtr aux;

    for(int i=0; i<t; i++){

        for(int j=0; j<t-1; j++){

            if(e[j]->legajo > e[j+1]->legajo){

                aux = e[j];
                e[j] = e[j+1];
                e[j+1] = aux;
            }
        }
    }
};

void ordenarApellido(EstudiantePtr e[], int t){

    EstudiantePtr aux;

    for(int i=0; i<t; i++){

        for(int j=0; j<t-1; j++){

            if( strcmp (e[j]->apellido , e[j+1]->apellido) ==1 ){

                aux = e[j];
                e[j] = e[j+1];
                e[j+1] = aux;
            }
        }
    }
};

///buscar estudiante
int buscarEst(EstudiantePtr e[], int t, int l){

    int res = -1;

    for(int i=0; i<t; i++){

        if( e[i]->legajo == 1){

            res = i;
        }
    }
    return res;
};

///anidar struct
EstudiantePtr cargarEstNulo(){

    EstudiantePtr e = (EstudiantePtr) malloc(sizeof(struct Estudiante));

    e->legajo = 1;
    e->prom= -1;
    strcpy(e->nombre, "VACIO");
    strcpy(e->apellido, "VACIO");

    return e;
};

void cargarEstNulos(EstudiantePtr e[], int t){

    for(int i=0; i<t; i++){

        e[i] = cargarEstNulo();
    }
};
/*
void liberarEst(EstudiantePtr e[]){

    free(e);
};

void liberarMat(MateriaPtr m[]){

    free(m->listaE);
    free(m);
}; */

void leerArchivo(MateriaPtr m) {
    FILE *archivo;
    archivo = fopen("estudiantes.txt", "r");

    if (archivo == NULL) {
        printf("No se puede abrir el archivo.\n");
        exit(1);
    }

    int pos = 0;

    while (fscanf(archivo, "%d,%19s %f %19s\n",
                  &(m->listaE[pos]->legajo),
                  m->listaE[pos]->nombre,
                  &(m->listaE[pos]->prom),
                  m->listaE[pos]->apellido) == 4) {
        pos++;
    }

    fclose(archivo);
}

void guardarDatos(MateriaPtr m){

    FILE *archivo = fopen("estudiantes.txt", "w");

    for(int i=0; i<TAM; i++){
        if(m->listaE[i]->legajo != -1){

            fprintf(archivo, "%s %s %d %f", m->listaE[i]->nombre, m->listaE[i]->apellido, m->listaE[i]->legajo, m->listaE[i]->prom);
        }
    }

    fclose(archivo);
};
