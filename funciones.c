#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define MAXP 100 
#define MAXN 100 
#define MAXL 250 

typedef struct 
{
    char nom[MAXN];
    int cant;
    float pre;
} Datos;

void ingresarProducto()
{
    Datos productoN; 

    printf("Ingrese el nombre del producto: \n");
    getchar();
    fgets(productoN.nom, MAXN, stdin);

    productoN.nom[strcspn(productoN.nom, "\n")] = '\0';

    printf("Ingrese la cantidad del producto: \n");
    scanf("%d", &productoN.cant);

    printf("Ingrese el precio del producto: \n");
    scanf("%f", &productoN.pre);


    FILE *archivo = fopen("productos.txt", "a");

    if (archivo == NULL)
    {
        printf("No hay productos \n");
        return;
    }

    fprintf(archivo, "%s,%d,%.2f\n", productoN.nom, productoN.cant, productoN.pre);

    fclose(archivo);

    printf("Producto ingresado correctamente.\n");
}

void editarProducto()
{
    int indice;

    printf("Ingrese el numero de producto a editar (0-%d): ", MAXP - 1);
    scanf("%d", &indice);

    FILE *archivo = fopen("productos.txt", "r"); 
    FILE *archivoTmp = fopen("productos_tmp.txt", "w");

    if (archivo == NULL || archivoTmp == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Datos producto;
    int contador = 0;
    char linea[MAXL];

    while (fgets(linea, MAXL, archivo) != NULL)

    {
        if (contador == indice)
        {
            sscanf(linea, "%[^,],%d,%f", producto.nom, &producto.cant, &producto.pre); 

            printf("Ingrese el nuevo nombre del producto: \n");
            getchar();
            fgets(producto.nom, MAXN, stdin);
            producto.nom[strcspn(producto.nom, "\n")] = '\0';

            printf("Ingrese la nueva cantidad del producto: \n");
            scanf("%d", &producto.cant);

            printf("Ingrese el nuevo precio del producto: \n");
            scanf("%f", &producto.pre);

            fprintf(archivoTmp, "%s,%d,%.2f\n", producto.nom, producto.cant, producto.pre); 


            printf("Producto editado correctamente.\n");
        }
        else
        {
            fprintf(archivoTmp, "%s", linea); 
        }

        contador++;
    }

    fclose(archivo);
    fclose(archivoTmp);

    remove("productos.txt");
    rename("productos_tmp.txt", "productos.txt"); 
}

void eliminarProducto()
{
    int indice;

    printf("Ingrese el numero de producto a eliminar (0-%d): ", MAXP - 1);
    scanf("%d", &indice);

    FILE *archivo = fopen("productos.txt", "r");
    FILE *archivoTmp = fopen("productos_tmp.txt", "w");

    if (archivo == NULL || archivoTmp == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Datos prod;
    int contador = 0;
    char linea[MAXL];

    while (fgets(linea, MAXL, archivo) != NULL)
    {
        if (contador != indice)
        {
            fprintf(archivoTmp, "%s", linea);
        }
        else
        {
            sscanf(linea, "%[^,],%d,%f", prod.nom, &prod.cant, &prod.pre);
            printf("Producto eliminado correctamente.\n");
        }

        contador++;
    }

    fclose(archivo);
    fclose(archivoTmp);

    remove("productos.txt");
    rename("productos_tmp.txt", "productos.txt");
}

void listarProductos()
{
    FILE *archivo = fopen("productos.txt", "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    printf("----- LISTA DE PRODUCTOS -----\n");
    Datos prod1;
    char linea[MAXL];
    int cont = 0;

    while (fgets(linea, MAXL, archivo) != NULL)
    {
        sscanf(linea, "%[^,],%d,%f", prod1.nom, &prod1.cant, &prod1.pre);
        printf("Producto %d:\n", cont);
        printf("Nombre: %s\n", prod1.nom);
        printf("Cantidad: %d\n", prod1.cant);
        printf("Precio: $%.2f\n", prod1.pre);
        printf("-----------------------------\n");
        cont++;
    }

    fclose(archivo);
}