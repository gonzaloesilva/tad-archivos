#include <stdio.h>
#include <stdlib.h>

struct s_habitaciones
{
    int NH,TC,TCO;
    char *n;
    struct s_habitaciones *pSig;
};
typedef struct s_habitaciones *t_nodoPtr;
typedef struct s_habitaciones t_nodo;

void funcion();
void armar(t_nodoPtr *pLista);
void buscar(char *nombre,t_nodoPtr *ptrNodo);
void agregar_al_final(t_nodoPtr *ptrNodo, int NH, int TC, int TCO, char *n);
void archivo(t_nodoPtr *ptrNodo);
void recorrer(t_nodoPtr ptrNodo);
t_nodoPtr crear_nodo(int NH, int TC, int TCO, char *n);

int main()
{

    funcion();
    return 0;
}
void funcion()
{
    t_nodoPtr pLista=NULL;
    int i,car;
    FILE *pArch;
    char *nombre=NULL;
    pArch=fopen("pacientes2.txt","r");
    if(pArch==NULL)
        printf("Error");
    nombre=malloc(sizeof(char));
    armar(&pLista);
    car=fgetc(pArch);

    while(!feof(pArch))
    {
        if(car==',')
        {
            *(nombre+i)=car;
            i++;
            nombre=realloc(nombre,(i+1)*sizeof(char));
        }
        else if(car==',')
        {
            *(nombre+i)='\0';
            buscar(nombre,&pLista);
            i=0;
        }
    }
    recorrer(pLista);
    archivo(&pLista);

}
void archivo(t_nodoPtr *ptrNodo)
{
    FILE *pArch;
    pArch=fopen("habitaciones2.csv","w+b");
    if(pArch==NULL)
    {
        printf("Error");
    }
    while((*ptrNodo)->pSig!=NULL)
    {
        fprintf(pArch,"%d;%d;%d;%s\n",(*ptrNodo)->NH,(*ptrNodo)->TC,(*ptrNodo)->TCO,(*ptrNodo)->n);

        (*ptrNodo)=(*ptrNodo)->pSig;
    }
}
void armar(t_nodoPtr *pLista)
{
    int i,car,NH,TC,TCO;
    FILE *pArch;
    char *n=NULL;
    pArch=fopen("habitaciones2.csv","r+b");
    if(pArch==NULL)
        printf("Error");
    n=malloc(sizeof(char));

    while(!feof(pArch))
    {
        fscanf(pArch,"%d;%d;%d;",&NH,&TC,&TCO);

        car=fgetc(pArch);
        while(car!='\n')
        {
            *(n+i)=car;
            i++;
            n=realloc(n,(i+1)*sizeof(char));
            car=fgetc(pArch);
        }

       *(n+i)='\0';
       i=0;
       agregar_al_final(pLista,NH,TC,TCO,n);


    }

}
void buscar(char *nombre,t_nodoPtr *ptrNodo)
{
        int i=0,j=0;
        if(((*ptrNodo)->TC)-((*ptrNodo)->TCO)>0)
        {
            while((*ptrNodo)->n[i]!='\0')
            {
                i++;
            }
            (*ptrNodo)->n[i]=' ';
            i++;
            while(nombre[j]!='\0')
            {
                (*ptrNodo)->n=realloc((*ptrNodo)->n,(i+1)*sizeof(char));
                (*ptrNodo)->n[i]=nombre[j];
                i++;
                j++;
            }
            (*ptrNodo)->n[i]='\0';
            ((*ptrNodo)->TCO)++;
        }
        else
        {
            buscar(nombre,&(*ptrNodo)->pSig);
        }
}
void agregar_al_final(t_nodoPtr *ptrNodo, int NH, int TC, int TCO, char *n)
{
    if(*ptrNodo==NULL)
    {
        *ptrNodo=crear_nodo(NH,TC,TCO,n);
    }
    else
        agregar_al_final(&(*ptrNodo)->pSig,NH,TC,TCO,n);
}
void recorrer(t_nodoPtr ptrNodo)
{
    if(ptrNodo==NULL)
        printf("Fin de la lista");
    else
    {
        printf("%d %d %d %s\n",(ptrNodo)->NH,(ptrNodo)->TC,(ptrNodo)->TCO,(ptrNodo)->n);
    }

}
t_nodoPtr crear_nodo(int NH, int TC, int TCO, char *n)
{
    t_nodoPtr ptrNuevo=malloc(sizeof(t_nodo));
    if(ptrNuevo!=NULL)
    {
        ptrNuevo->NH=NH;
        ptrNuevo->TC=TC;
        ptrNuevo->TCO=TCO;
        ptrNuevo->n=n;
        ptrNuevo->pSig=NULL;
    }
    return ptrNuevo;
}

