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
        printf("\n========== MENU PRINCIPAL==========\n");
        printf("1. Ingresar componentes\n");
        printf("2. Ingresar productos\n");
        printf("3. Buscar un producto\n");
        printf("4. Editar un producto\n");
        printf("5. Eliminar un producto\n");
        printf("6. Pedir Producto\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
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


void ingresocomponentes(float *numerocomp, char componentes[3][50], int *contador) {
    int continuar = 1;

    while (*contador < 3 && continuar) {
        printf("Ingrese el nombre del componente numero %d que tenemos en stock: ", *contador + 1);
        getchar();
        fgets(componentes[*contador], 50, stdin);
        componentes[*contador][strcspn(componentes[*contador], "\n")] = '\0'; // Eliminar salto de lÃ­nea

        printf("Ingrese la cantidad de %s que se tiene en stock: ", componentes[*contador]);
        scanf("%f", &numerocomp[*contador]);

        (*contador)++; 

        if (*contador < 3) {
            printf("Desea ingresar otro componente? (0 = No, 1 = Si): ");
            scanf("%d", &continuar);
            if (continuar != 1 && continuar != 0) {
                do {
                    printf("Valor ingresado incorrecto. Ingrese 0 o 1: ");
                    scanf("%d", &continuar);
                } while (continuar != 1 && continuar != 0);
            }
        }
    }
}

void ingresoProductos(char productos[5][60], float *tiempo, float cantidadcom[5][3], int contador, char componentes[3][50]) {
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

void buscarProducto(char productos[5][60], float tiempo[5], float cantidadcom[5][3], char componentes[3][50], int contador) {
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

void editarProducto(char productos[5][60], float tiempo[5], float cantidadcom[5][3], char componentes[3][50], int contador) {
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

void eliminarProducto(char productos[5][60], float tiempo[5], float cantidadcom[5][3], int *contadorProductos) {
    char productoEliminar[60];
    int encontrado = -1;

    printf("Ingrese el nombre del producto que desea eliminar: ");
    getchar(); 
    fgets(productoEliminar, 60, stdin);
    productoEliminar[strcspn(productoEliminar, "\n")] = '\0'; 

    for (int i = 0; i < *contadorProductos; i++) {
        if (strcmp(productos[i], productoEliminar) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        for (int i = encontrado; i < *contadorProductos - 1; i++) {
            strcpy(productos[i], productos[i + 1]);
            tiempo[i] = tiempo[i + 1];
            for (int j = 0; j < 3; j++) {
                cantidadcom[i][j] = cantidadcom[i + 1][j];
            }
        }
        (*contadorProductos)--; 
        printf("Producto eliminado correctamente.\n");
    } else {
        printf("Producto no encontrado.\n");
    }
}

//

void productosPedir(char productos[5][60], float cantidadcom[5][3], float numerocomp[3], char componentes[3][50], int contador) {
    int n, cantidadPedido;
    printf("\nCual producto desea de nuestro inventario?\n");
    for (int i = 0; i < 5; i++) {
        printf("%d- %s\n", i + 1, productos[i]);
    }

    printf("Ingrese el numero del producto que desea: ");
    scanf("%d", &n);

    if (n < 1 || n > 5) {
        printf("Producto no valido.\n");
        return;
    }

    printf("\nPor favor ingrese cuantos '%s' desea: ", productos[n - 1]);
    scanf("%d", &cantidadPedido);

    int posible = 1;
    printf("\nVerificando disponibilidad de componentes para '%s':\n", productos[n - 1]);

    switch (n) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            for (int i = 0; i < contador; i++) {
                
                float componentesNecesarios = cantidadPedido * cantidadcom[n - 1][i];
                if (numerocomp[i] < componentesNecesarios) {
                    printf("- No hay suficientes '%s'. Necesita %.2f, pero solo hay %.2f.\n", componentes[i], componentesNecesarios, numerocomp[i]);
                    posible = 0;
                } else {
                    printf("- '%s': Disponible (necesita %.2f, hay %.2f).\n", componentes[i], componentesNecesarios, numerocomp[i]);
                }
            }

            if (posible == 1) {
                printf("\nEl pedido es posible. Procesando...\n");
                printf("Pedido procesado exitosamente.\n");
            } else {
                printf("\nNo es posible realizar el pedido debido a la falta de componentes.\n");
            }
            break;

        default:
            printf("Producto no valido.\n");
            break;
    }
}