/*F.2 Una Empresa de la ciudad de Tilcara, que comercializa productos regionales, cuenta con un archivo secuencial
stock.dat con los saldos de sus casi 2000 productos, al �ltimo d�a del mes de junio de 2019. Cada registro tiene
los siguientes datos:

    � Nro. de Articulo (4 d�gitos)
    � Rubro (A, B, C o D)
    � Descripci�n (25 caracteres)
    � Precio Unitario.
    � Stock

Al finalizar el mes de Julio de este mismo a�o, se nos entrega, otro archivo, movim.dat, que contiene los
movimientos de ventas, con los siguientes datos, ordenados por Nro. de Vendedor:

    � Nro. de Vendedor (3 d�gitos)
    � Nro. de Articulo (4 d�gitos)
    � D�a (1 a 31)
    � Cantidad Vendida (int)

Desarrollar el diagrama de L�gica y su correspondiente codificaci�n en C, cumpliendo los siguientes puntos:
    a. Informar por Nro. de Vendedor, cantidad de Art�culos Vendidos y Monto, por Rubro.

    b. Informar el vendedor que realiz� el menor monto de venta, tomando en cuenta todos los rubros.

    c. Si la venta es rechazada por falta de stock, guardar el registro. Al finalizar el proceso, informar los mismos,
    si no existieron, rechazados, imprimir mensaje �No Hay Rechazados�. (almacenar en estructura igual de
    movimientos, no hay m�s de 100).

    d. Al finalizar, grabar la actualizaci�n de las ventas registradas en el mes de Julio, en otro archivo
    Stock_con_Julio.dat.

    e. Emitir un informe de las ventas realizadas por d�a de todos los vendedores:

        Listado de Ventas Julio 2018
        D�a     Importe Vendido
        1       xxx
        1       xxx
        2       xxx
        ---     -----
        31      xxx

Funciones
    1) Utilizar la funci�n NUEVOARCH (), para generar el archivo Stock_con_Julio.dat.
    2) Utilizar la funci�n Listado () para mostrar el punto e.
    3) Utilizar la funci�n BUSCAR ().
    4) grabaci�n de Archivo Actualizado.*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef struct
{
    int nroarticulo;
    char rubro;
    char descripcion[26];
    float preciou;
    int stock;
}T_Stock;

typedef struct
{
    int nrovendedor,nroarticulo,dia,cantvendida;
}T_Movi;

int CargaStock(T_Stock[],int);
void NUEVOARCH(T_Stock[],int);

int main()
{
    T_Stock VStock[2000];
    int cant=CargaStock(VStock,2000);
}

int CargaStock(T_Stock v[],int ce)
{
    FILE *pf;
    T_Stock aux;
    int i=0;
    pf=fopen("stock.dat","rb");
    if(pf==NULL)
    {
        printf("\nNo abrio el archivo...\n");
        system("pause");
        exit(1);
    }
    fread(&aux,sizeof(T_Stock),1,pf);
    while(!feof(pf)&&i<ce)
    {
        v[i]=aux;
        i++;
        fread(&aux,sizeof(T_Stock),1,pf);
    }
    fclose(pf);
    return i;
}

void NUEVOARCH(T_Stock v[],int ce)
{
    FILE *pf;
    int i;
    pf=fopen("Stock_con_Julio.dat","wb");
    if(pf==NULL)
    {
        printf("\nNo abrio el archivo...\n");
        system("pause");
        exit(1);
    }
    for(i=0;i<=ce-1;i++)
        fwrite(&v[i],sizeof(T_Stock),1,pf);
    fclose(pf);
}

void Listado(T_Stock v[],int ce)
{
    int i;
    printf("\n\tListado de Ventas Julio 2018\n");
    printf("\nDia\tImporte Vendido\n");
    for(i=0;i<=ce-1;i++)
        printf("\n%d\t%.2f",v[i].stock*v[i].cantvendida);
}

