/*2. Saldos
La empresa Disco Mundo dispone del archivo secuencial SALDOS.dat conteniendo los siguientes datos de casi 1200 clientes.
� Nro. de Cliente (entero - entre 100 y 11900)
� Raz�n Social (25 caracteres)
� Importe Total Facturado (real)
� Total de Pagos Efectuados (real)
� Saldo Deudor (real)
� C�digo de Estado (�A� � es Activo, �B� � es Baja)
Nos suministran, adem�s, todas las operaciones de ventas y cobranzas del d�a que efectu� la empresa que no est�n ordenadas. Para cada operaci�n se informa:
� Nro. de Cliente (entero - entre 100 y 11900)
� Zona (1 a 100)
� C�digo de Operaci�n (�V� � Venta, �P� - Pago)
� Importe (> 0 y < 20.000)
Las operaciones finalizan con una operaci�n ficticia que tiene Nro. de Cliente CERO:
Confeccionar el diagrama de l�gica y la respectiva codificaci�n para:
a) Generar el array de estructuras llamado Clie_Activos, con solamente los datos de los clientes activos (C�digo de Estado �A�) del archivo SALDOS. Utilizar funci�n LECTURA_CLIENTE.
b) Ingresar y controlar las operaciones del d�a. Para controlar la validez se debe confeccionar una funci�n CONTROL que pueda validar los 4 datos que se ingresaron para cada operaci�n respondiendo si son o no correctos. Utilizarla para aceptar o rechazar cada operaci�n. Cuando la operaci�n se rechaza, grabar todos los datos de la operaci�n en un archivo ERROR.dat y pasar al ingreso de otra operaci�n.
Utilizar funci�n ENTRADA para verificar la existencia del Cliente, si no existe indicar mediante un mensaje CLIENTE INEXISTENTE , pasando a ingresar otra operaci�n.
c) Actualizar el array Clie_Activos con las operaciones exitosas.
Con las operaciones de Ventas actualizar los campos Importe Total Facturado (sumando) y Saldo Deudor (Importe Total Facturado actualizado - Total de Pagos Efectuados)
Con las operaciones de Pagos actualizar Total de Pagos Efectuados (sumando) y calcular el nuevo Saldo Deudor.
d) Informar los datos grabados en el archivo ERROR.dat. Mediante la funci�n LECTURA_ERROR.
e) Actualizar el archivo SALDOS. Mediante la funci�n GRABAR.
f) Al finalizar el proceso, confeccionar una lista con aquellos clientes, que han quedado con saldo
deudor mayor de 1500 pesos. Mediante la funci�n LISTAR.*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct
{
    int nrocliente;
    char razonsocial[26],codestado;
    float imptotal,tpe,saldodeudor;
}T_Sal;

void Grabacion();
void Lectura();

int main()
{
    int opcion;
    do
    {
        printf("\n1 - Grabacion\n2 - Lectura\n3 - Fin\n");
        do
        {
            printf("\nIngrese una opcion: ");
            scanf("%d",&opcion);
        }while(!(opcion>=1&&opcion<=3));
        switch(opcion)
        {
            case 1:Grabacion();break;
            case 2:Lectura();break;
        }
    }while(opcion!=3);
}

void Grabacion()
{
    FILE *pf;
    T_Sal sal;
    pf=fopen("SALDOS.dat","wb");
    if(pf==NULL)
    {
        printf("\nNo abrio el archivo...\n");
        getch();
        exit(1);
    }
    do
    {
        printf("\nIngrese numero de cliente: ");
        scanf("%d",&sal.nrocliente);
    }while(!(sal.nrocliente>=100&&sal.nrocliente<=11900||sal.nrocliente==0));
    while(sal.nrocliente!=0)
    {
        printf("\nIngrese razon social: ");
        fflush(stdin);
        gets(sal.razonsocial);
        do
        {
            printf("\nIngrese importe total facturado: ");
            scanf("%f",&sal.imptotal);
        }while(!(sal.imptotal>0));
        do
        {
            printf("\nIngrese total de pagos efectuados: ");
            scanf("%f",&sal.tpe);
        }while(!(sal.tpe>0));
        do
        {
            printf("\nIngrese saldo deudor: ");
            scanf("%f",&sal.saldodeudor);
        }while(!(sal.saldodeudor>0));
        do
        {
            printf("\nIngrese codigo de estado ('A' - es Activo, 'B' - es Baja): ");
            fflush(stdin);
            scanf("%c",&sal.codestado);
        }while(!(sal.codestado=='A'||sal.codestado=='B'));
        fwrite(&sal,sizeof(T_Sal),1,pf);
        do
        {
            printf("\nIngrese numero de cliente: ");
            scanf("%d",&sal.nrocliente);
        }while(!(sal.nrocliente>=100&&sal.nrocliente<=11900||sal.nrocliente==0));
    }
    fclose(pf);
}

void Lectura()
{
    FILE *pf;
    T_Sal sal;
    pf=fopen("SALDOS.dat","rb");
    if(pf==NULL)
    {
        printf("\nNo abrio el archivo...\n");
        getch();
        exit(1);
    }
    printf("\nNRO CLIENTE\tRAZON SOCIAL\tIMP. TOTAL FACTURADO\tTOTAL DE PAGOS EFECTUADOS\tSALDO DEUDOR\tCOD. DE ESTADO\n");
    fread(&sal,sizeof(T_Sal),1,pf);
    while(!feof(pf))
    {
        printf("\n%d\t\t%s\t\t%.2f\t\t%.2f\t\t%.2f\t\t\t%c\n",sal.nrocliente,sal.razonsocial,sal.imptotal,sal.tpe,sal.saldodeudor,sal.codestado);
        fread(&sal,sizeof(T_Sal),1,pf);
    }
    fclose(pf);
}
