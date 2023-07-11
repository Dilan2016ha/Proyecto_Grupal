#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int main() {
    // Agregar productos establecidos al inicio
    FILE *archivo = fopen("productos.txt", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    fclose(archivo);

    int opcion;

    do {
        printf("\n----- MENU -----\n");
        printf("1. Ingresar viveres\n");
        printf("2. Editar \n");
        printf("3. Eliminar \n");
        printf("4. Ver lista de viveres\n");
        printf("5. Salir del programa\n");
        printf("Ingrese una opcion: \n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarProducto();
                break;
            case 2:
                editarProducto();
                break;
            case 3:
                eliminarProducto();
                break;
            case 4:
                listarProductos();
                break;
            case 5:
                printf("Gracias por usar nuestro programa\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}