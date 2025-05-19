#include <stdio.h>
#include <string.h>

void ingresocomponentes(float *numerocomp, char componentes[3][50], int *contador);
void ingresoProductos(char productos[5][60], float *tiempo, float cantidadcom[5][3], int contador, char componentes[3][50]);
void buscarProducto(char productos[5][60], float tiempo[5], float cantidadcom[5][3], char componentes[3][50], int contador);
void editarProducto(char productos[5][60], float tiempo[5], float cantidadcom[5][3], char componentes[3][50], int contador);
void eliminarProducto(char productos[5][60], float tiempo[5], float cantidadcom[5][3], int *contadorProductos);
void productosPedir(char productos[5][60], float cantidadcom[5][3], float numerocomp[3], char componentes[3][50], int contador);

int main (int argc, char *argv[]) {
    char componentes[3][50];
    float numerocomp[3] = {0};
    int contadorComponentes = 0;

    char productos[5][60] = {0};
    float tiempo[5] = {0};
    float cantidadcom[5][3] = {{0}};
    int contadorProductos = 0;

    int opcion;

    do {
        printf("\n\n------------------------------------------------\n");
        printf("Seleccione una opcion.\n");
        printf("1. Ingresar componentes y stock.\n");
        printf("2. Ingresar productos a fabricar.\n");
        printf("3. Buscar un producto.\n");
        printf("4. Editar un producto registrado.\n");
        printf("5. Eliminar un producto registrado.\n");
        printf("6. Pedir \n");
        printf("7. Salir\n");
        printf("----------------------------------------------------\n");
        printf(">>>> ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresocomponentes(numerocomp, componentes, &contadorComponentes);
                break;

            case 2:
                if (contadorComponentes == 0) {
                    printf("Primero debe ingresar componentes antes de agregar productos.\n");
                } else {
                    ingresoProductos(productos, tiempo, cantidadcom, contadorComponentes, componentes);
                    contadorProductos = 5; // Consideramos que se ingresan los 5 productos
                }
                break;

            case 3:
                if (contadorProductos == 0) {
                    printf("No hay productos ingresados para buscar.\n");
                } else {
                    buscarProducto(productos, tiempo, cantidadcom, componentes, contadorComponentes);
                }
                break;

            case 4:
                if (contadorProductos == 0) {
                    printf("No hay productos ingresados para editar.\n");
                } else {
                    editarProducto(productos, tiempo, cantidadcom, componentes, contadorComponentes);
                }
                break;

            case 5:
                if (contadorProductos == 0) {
                    printf("No hay productos ingresados para eliminar.\n");
                } else {
                    eliminarProducto(productos, tiempo, cantidadcom, &contadorProductos);
                }
                break;
            case 6:
                productosPedir(productos, cantidadcom, numerocomp, componentes, contadorComponentes);
            break;
            case 7:
                printf("\nSaliendo del programa......\n");
                break;

            default:
                printf("Opcion no Valida.....\n");
        }
    } while (opcion != 7);
    return 0;
}

void ingresocomponentes(float *numerocomp, char componentes[][50], int *contador) {
    int total;

    printf("¿Cuántos componentes desea ingresar? (máximo 3): ");
    scanf("%d", &total);
    while (getchar() != '\n'); // limpiar buffer
    for (int i = 0; i < total; i++) {
        printf("Ingrese el nombre del componente número %d: ", i + 1);
        fgets(componentes[i], 50, stdin);
        componentes[i][strcspn(componentes[i], "\n")] = '\0';

        printf("Ingrese la cantidad de %s que se tiene en stock: ", componentes[i]);
        scanf("%f", &numerocomp[i]);
        while (getchar() != '\n');
    }
    *contador = total;
}


void ingresoProductos(char productos[][60], float *tiempo, float cantidadcom[5][3], int contador, char componentes[3][50]) {
    printf("Por favor, ingrese los 5 productos:\n");
    for (int i = 0; i < 5; i++) {
        printf("Ingrese el producto numero %d: ", i + 1);
        getchar(); 
        fgets(productos[i], 60, stdin);
        productos[i][strcspn(productos[i], "\n")] = '\0'; 

        printf("Ingrese el tiempo necesario para la creacion de %s: ", productos[i]);
        scanf("%f", &tiempo[i]);

        for (int j = 0; j < contador; j++) {
            printf("Cuantos %s necesita para su fabricacion?: ", componentes[j]);
            scanf("%f", &cantidadcom[i][j]);
        }
    }
}

void buscarProducto(char productos[][60], float tiempo[5], float cantidadcom[5][3], char componentes[3][50], int contador) {
    char productoBuscado[60];
    int encontrado = 0;

    printf("Que producto desea buscar? Ingrese el nombre: ");
    getchar(); 
    fgets(productoBuscado, 60, stdin);
    productoBuscado[strcspn(productoBuscado, "\n")] = '\0'; 

    for (int i = 0; i < 5; i++) {
        if (strcmp(productos[i], productoBuscado) == 0) {
            encontrado = 1;
            printf("El tiempo de elaboracion del producto %s es: %.2f horas\n", productos[i], tiempo[i]);
            printf("Los componentes necesarios para %s son:\n", productos[i]);
            for (int j = 0; j < contador; j++) {
                printf("- %s: %.2f unidades\n", componentes[j], cantidadcom[i][j]);
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}
void editarProducto(char productos[][60], float tiempo[5], float cantidadcom[5][3], char componentes[3][50], int contador) {
    char productoBuscado[60];
    int encontrado = -1;

    printf("Ingrese el nombre del producto a editar: ");
    getchar();
    fgets(productoBuscado, 60, stdin);
    productoBuscado[strcspn(productoBuscado, "\n")] = '\0'; 

    for (int i = 0; i < 5; i++) {
        if (strcmp(productos[i], productoBuscado) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        printf("Producto encontrado: %s\n", productos[encontrado]);

        printf("Ingrese el nuevo nombre del producto: ");
        fgets(productos[encontrado], 60, stdin);
        productos[encontrado][strcspn(productos[encontrado], "\n")] = '\0';

        printf("Ingrese el nuevo tiempo de produccion: ");
        scanf("%f", &tiempo[encontrado]);

        for (int j = 0; j < contador; j++) {
            printf("Ingrese la nueva cantidad de %s necesaria: ", componentes[j]);
            scanf("%f", &cantidadcom[encontrado][j]);
        }

        printf("Producto actualizado correctamente.\n");
    } else {
        printf("Producto no encontrado.\n");
    }
}

void eliminarProducto(char productos[][60], float tiempo[5], float cantidadcom[5][3], int *contadorProductos) {
    char productoEliminar[60];
    int encontrado = -1;

    printf("Ingrese el nombre del producto que desea eliminar: ");
    getchar();
    fgets(productoEliminar, 60, stdin);
    
    // Eliminar salto de línea manualmente
    int len = 0;
    while (productoEliminar[len] != '\n' && productoEliminar[len] != '\0') {
        len++;
    }
    productoEliminar[len] = '\0';

    // Buscar producto comparando carácter por carácter
    for (int i = 0; i < *contadorProductos; i++) {
        int j = 0;
        int igual = 1;
        while (productos[i][j] != '\0' || productoEliminar[j] != '\0') {
            if (productos[i][j] != productoEliminar[j]) {
                igual = 0;
                break;
            }
            j++;
        }
        if (igual) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        for (int i = encontrado; i < *contadorProductos - 1; i++) {
            int j = 0;
            while ((productos[i + 1][j] != '\0') && j < 60) {
                productos[i][j] = productos[i + 1][j];
                j++;
            }
            productos[i][j] = '\0'; 
            tiempo[i] = tiempo[i + 1];

            for (int k = 0; k < 3; k++) {
                cantidadcom[i][k] = cantidadcom[i + 1][k];
            }
        }
        (*contadorProductos)--;
        printf("Producto eliminado correctamente.\n");
    } else {
        printf("Producto no encontrado.\n");
    }
}

void productosPedir(char productos[][60], float cantidadcom[5][3], float numerocomp[3], char componentes[3][50], int contador) {
    int n, cantidadPedido;

    printf("\n¿Qué producto desea de nuestro inventario?\n");
    for (int i = 0; i < 5; i++) {
        if (strlen(productos[i]) > 0) {
            printf("%d - %s\n", i + 1, productos[i]);
        }
    }

    printf("Ingrese el número del producto que desea: ");
    scanf("%d", &n);

    if (n < 1 || n > 5 || strlen(productos[n - 1]) == 0) {
        printf("Producto no válido.\n");
        return;
    }

    printf("\nIngrese cuántos '%s' desea: ", productos[n - 1]);
    scanf("%d", &cantidadPedido);

    int posible = 1;
    printf("\nVerificando disponibilidad de componentes para '%s':\n", productos[n - 1]);

    for (int i = 0; i < contador; i++) {
        float componentesNecesarios = cantidadPedido * cantidadcom[n - 1][i];

        if (numerocomp[i] < componentesNecesarios) {
            printf("- No hay suficientes '%s'. Necesita %.2f, pero solo hay %.2f.\n",
                   componentes[i], componentesNecesarios, numerocomp[i]);
            posible = 0;
        } else {
            printf("- '%s': Disponible (necesita %.2f, hay %.2f).\n",
                   componentes[i], componentesNecesarios, numerocomp[i]);
        }
    }

    if (posible) {
        printf("\nEl pedido es posible. Procesando...\n");
        for (int i = 0; i < contador; i++) {
            numerocomp[i] -= cantidadPedido * cantidadcom[n - 1][i];
        }
        printf("Pedido procesado exitosamente.\n");
    } else {
        printf("\nNo es posible realizar el pedido debido a la falta de componentes.\n");
    }
}