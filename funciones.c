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
    //fgets se utiliza para leer una línea de texto y stdin es el flujo de entrada estándar y se utiliza como argumento para fgets

    productoN.nom[strcspn(productoN.nom, "\n")] = '\0';
    //Se utiliza para terminar la variable nuevoProducto.nombre con un caracter nulo y asi evitar problemas de manejo 
    // y la muestra de datos

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

    // Escribir o Guardar el nuevo producto en el archivo
    fprintf(archivo, "%s,%d,%.2f\n", productoN.nom, productoN.cant, productoN.pre);

    // Cerrar el archivo
    fclose(archivo);

    printf("Producto ingresado correctamente.\n");
}

void editarProducto()
{
    int indice;

    printf("Ingrese el numero de producto a editar (0-%d): ", MAXP - 1);
    scanf("%d", &indice);

    FILE *archivo = fopen("productos.txt", "r"); // se abre el archivo donde estan guardados los productos
    FILE *archivoTmp = fopen("productos_tmp.txt", "w");
    // se crea un nuevo archivo para otro producto y despues sobre escribirlo en el arcivo anterior

    if (archivo == NULL || archivoTmp == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Datos producto;
    int contador = 0;
    char linea[MAXL];

    while (fgets(linea, MAXL, archivo) != NULL)
    // se lee cada linea del archivo productos.txt y se almacena en la variable linea, hasta que alcance el final del archivo 
    {
        if (contador == indice)
        {
            sscanf(linea, "%[^,],%d,%f", producto.nom, &producto.cant, &producto.pre); // lee datos toma una cadena como entrada
            //%[^,] sirve para leer una cadena de texto hasta encontrar una coma
            printf("Ingrese el nuevo nombre del producto: \n");
            getchar();
            fgets(producto.nom, MAXN, stdin);
            producto.nom[strcspn(producto.nom, "\n")] = '\0';

            printf("Ingrese la nueva cantidad del producto: \n");
            scanf("%d", &producto.cant);

            printf("Ingrese el nuevo precio del producto: \n");
            scanf("%f", &producto.pre);

            fprintf(archivoTmp, "%s,%d,%.2f\n", producto.nom, producto.cant, producto.pre); 
            // se guarda los datos del producto editado en un archivo temporal

            printf("Producto editado correctamente.\n");
        }
        else
        {
            fprintf(archivoTmp, "%s", linea); //se guarda las lineas del archivo no editadas en archivoTmp
        }

        contador++;
    }

    fclose(archivo);
    fclose(archivoTmp);

    remove("productos.txt"); // Eliminar el archivo
    rename("productos_tmp.txt", "productos.txt"); // Renombrar el archivo temporal al archivo original
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