#include <stdio.h>
#include <string.h>
#include "prototipos.h"

int menu()
{
    int opc;
    do
    {
        printf("\n\n------------------------------------------------\n");
        printf("Seleccione una opcion.\n");
        printf("1. Ingresar componentes y stock.\n");
        printf("2. Ingresar productos a fabricar.\n");
        printf("3. Buscar un producto.\n");
        printf("4. Editar un producto registrado.\n");
        printf("5. Eliminar un producto registrado.\n");
        printf("6. Realizar un pedido.\n");
        printf("7. Salir.\n");
        printf("----------------------------------------------------\n");
        printf(">>>> ");
        scanf("%d", &opc);
        fflush(stdin);
        if (opc < 1 || opc > 7)
        {
            printf("\nIngrese un numero que se encuentre dentro del menu.\n");
        }
    } while (opc < 1 || opc > 7);
    return opc;
}

void ingresarcomponentes(float *numerocomponentes, char componentes[][30], int *contador)
{
    char entrada[10];
    int total, valido;
    printf("----------Registre componentes----------\n");
    do
    {
        printf("Cuantos componentes desea ingresar?: ");
        fgets(entrada, sizeof(entrada), stdin);
        valido = sscanf(entrada, "%d", &total);
        if (valido != 1)
        {
            printf("\nSolo puede ingresar numeros enteros positivos.\n");
            continue;
        }
        if (total < 1)
        {
            printf("\nNo puede ingresar numeros negativos por ende no puede registrar componentes menores a 1.\n");
            printf("\nDebe registrar al menos un componente.\n");
        }
        else if (total > 10)
        {
            printf("\nRecuerde el número maximo de productos es 10.\n");
        }
    } while (valido != 1 || total < 1);
    while (*contador < total)
    {
        printf("\n\nIngrese el nombre del componente %d que se tiene en el inventario: ", *contador + 1);
        getchar();
        fgets(componentes[*contador], 30, stdin);
        int len = strlen(componentes[*contador]) - 1;
        componentes[*contador][len] = '\0';
        printf("Ingrese la cantidad de %s que se tiene en stock: ", componentes[*contador]);
        scanf("%f", &numerocomponentes[*contador]);
        (*contador)++;
    }
}

int productosaFabricar(char productos[][30], float *tiempo, float cantidad[][10], int contador, char componentes[][30])
{
    char Entrada[10];
    int cantproductos, validez;
    printf("----------Registre la produccion de productos----------\n");
    do
    {
        printf("\nCuantos productos desea fabricar: ");
        fgets(Entrada, sizeof(Entrada), stdin);
        validez = sscanf(Entrada, "%d", &cantproductos);
        if (validez != 1)
        {
            printf("\nSolo puede ingresar numeros positivos.\n");
            continue;
        }
        if (cantproductos < 1)
        {
            printf("\nNo puede ingresar numeros menores a 1.\n");
            printf("\nDebe registrar al menos un producto.\n");
        }
        else if (cantproductos > 5)
        {
            printf("\nRecuerde el número maximo de productos es 5.\n");
        }
    } while ((cantproductos < 1 || cantproductos > 5) || validez != 1);

    printf("\n\nIngrese los %d productos:\n", cantproductos);
    for (int i = 0; i < cantproductos; i++)
    {
        printf("\n\nIngrese el producto numero %d: ", i + 1);
        fgets(productos[i], 30, stdin);
        productos[i][strcspn(productos[i], "\n")] = '\0';

        printf("Ingrese el tiempo necesario para la creacion de %s: ", productos[i]);
        scanf("%f", &tiempo[i]);
        fflush(stdin);
        for (int j = 0; j < contador; j++)
        {
            printf("Cuantos %s necesita para su fabricacion?: ", componentes[j]);
            scanf("%f", &cantidad[i][j]);
            fflush(stdin);
        }
    }
    return cantproductos;
}

void EncontrarProducto(char productos[][30], float tiempo[], float cantidad[][10], char componentes[][30], int contadorComponentes, int contadorProductos)
{
    char BuscarProducto[30];
    int encontrado = 0;
    printf("Ingrese el nombre del producto a ver el detalle: ");
    fgets(BuscarProducto, 30, stdin);
    int len = strlen(BuscarProducto);
    if (len > 0 && BuscarProducto[len - 1] == '\n')
    {
        BuscarProducto[len - 1] = '\0';
    }

    if (strlen(BuscarProducto) == 0)
    {
        printf("No ingresó ningún nombre de producto.\n");
        return;
    }

    for (int i = 0; i < contadorProductos; i++)
    {
        if (strcmp(productos[i], BuscarProducto) == 0)
        {
            encontrado = 1;
            printf("\n----------Producto Encontrado.----------\n");
            printf("El tiempo de elaboracion de %s es: %.2f minutos\n", productos[i], tiempo[i]);
            printf("Los componentes necesarios para la fabricacion del %s son:\n", productos[i]);
            for (int j = 0; j < contadorComponentes; j++)
            {
                printf("%s: %.1f unidades\n", componentes[j], cantidad[i][j]);
            }
            break;
        }
    }
    if (encontrado == 0)
    {
        printf("\nNo se encuentra dicho producto con ese nombre.\n");
    }
}
void editarProducto(char productos[][30], float tiempo[], float cantidad[][10], char componentes[][30], int contadorComponentes, int contadorProductos)
{
    char nombreBuscar[30];
    int encontrado = -1;
    printf("Ingrese el nombre del producto a editar: ");
    getchar();
    fgets(nombreBuscar, 30, stdin);
    int len = strlen(nombreBuscar);
    if (len > 0 && nombreBuscar[len - 1] == '\n')
    {
        nombreBuscar[len - 1] = '\0';
    }
    for (int i = 0; i < contadorProductos; i++)
    {
        if (strcmp(productos[i], nombreBuscar) == 0)
        {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1)
    {
        printf("Producto no encontrado.\n");
        return;
    }
    printf("\nProducto encontrado: %s\n", productos[encontrado]);
    printf("\nIngrese el nuevo nombre del producto: ");
    fgets(productos[encontrado], 30, stdin);
    len = strlen(productos[encontrado]);
    if (len > 0 && productos[encontrado][len - 1] == '\n')
    {
        productos[encontrado][len - 1] = '\0';
    }
    printf("Ingrese el nuevo tiempo de produccion: ");
    scanf("%f", &tiempo[encontrado]);
    for (int j = 0; j < contadorComponentes; j++)
    {
        printf("Ingrese la nueva cantidad de %s necesaria: ", componentes[j]);
        scanf("%f", &cantidad[encontrado][j]);
    }
    printf("Producto actualizado correctamente.\n");
}
void eliminarProducto(char productos[][30], float tiempo[], float cantidad[][10], int *contadorProductos, int contadorComponentes)
{
    char nombreEliminar[30];
    int encontrado = -1;
    printf("Ingrese el nombre del producto que desea eliminar: ");
    getchar();
    fgets(nombreEliminar, 30, stdin);
    int len = strlen(nombreEliminar);
    if (len > 0 && nombreEliminar[len - 1] == '\n')
    {
        nombreEliminar[len - 1] = '\0';
    }
    for (int i = 0; i < *contadorProductos; i++)
    {
        if (strcmp(productos[i], nombreEliminar) == 0)
        {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1)
    {
        printf("Producto no encontrado.\n");
        return;
    }
    for (int i = encontrado; i < *contadorProductos - 1; i++)
    {
        strcpy(productos[i], productos[i + 1]);
        tiempo[i] = tiempo[i + 1];
        for (int j = 0; j < contadorComponentes; j++)
        {
            cantidad[i][j] = cantidad[i + 1][j];
        }
    }
    (*contadorProductos)--;
    printf("\nProducto eliminado correctamente.\n");
}
void productosPedir(char productos[][30], float cantidadcom[][10], float numerocomp[], char componentes[][30], int contadorComponentes, int contadorProductos, float tiempo[])
{
    int n, cantidadPedido, validez;
    float tiempoPedido;
    char entrada[50];

    printf("\n¿Cuál producto desea de nuestro inventario?\n");
    for (int i = 0; i < contadorProductos; i++)
        printf("%d. %s\n", i + 1, productos[i]);

    do
    {
        printf("Ingrese el número del producto que desea: ");
        fgets(entrada, sizeof(entrada), stdin);
        validez = sscanf(entrada, "%d", &n);
        if (validez != 1 || n < 1 || n > contadorProductos)
            printf("Producto no válido.\n");
    } while (validez != 1 || n < 1 || n > contadorProductos);

    do
    {
        printf("\nPor favor ingrese cuántos %s desea fabricar: ", productos[n - 1]);
        fgets(entrada, sizeof(entrada), stdin);
        validez = sscanf(entrada, "%d", &cantidadPedido);
        if (validez != 1 || cantidadPedido < 1)
            printf("Error: Debe ingresar un número entero positivo.\n");
    } while (validez != 1 || cantidadPedido < 1);

    do
    {
        printf("Ingrese en cuánto tiempo (en minutos) desea que se complete la producción: ");
        fgets(entrada, sizeof(entrada), stdin);
        validez = sscanf(entrada, "%f", &tiempoPedido);
        if (validez != 1 || tiempoPedido <= 0.0f)
            printf("Error: Debe ingresar un número decimal positivo.\n");
    } while (validez != 1 || tiempoPedido <= 0.0f);

    float tiempoNecesario = tiempo[n - 1] * cantidadPedido;
    if (tiempoPedido < tiempoNecesario)
    {
        printf("\nNo es posible completar la producción en el tiempo solicitado.\n");
        printf("Tiempo necesario: %.2f minutos.\n", tiempoNecesario);
        printf("Tiempo establecido: %.2f minutos.\n", tiempoPedido);
        return;
    }

    int posible = 1;
    printf("\nVerificando la disponibilidad de los componentes para fabricar '%s':\n", productos[n - 1]);

    for (int i = 0; i < contadorComponentes; i++)
    {
        float componentesNecesarios = cantidadPedido * cantidadcom[n - 1][i];
        if (numerocomp[i] < componentesNecesarios)
        {
            printf("\nNo hay suficientes '%s'.\n", componentes[i]);
            printf("Necesita %.2f, pero solo hay %.2f.\n", componentesNecesarios, numerocomp[i]);
            posible = 0;
        }
        else
        {
            printf("%d. %s: Disponible (necesita %.2f, hay %.2f).\n", i + 1, componentes[i], componentesNecesarios, numerocomp[i]);
        }
    }

    if (posible == 1)
    {
        printf("\nEl pedido es posible. Procesando...\n");
        for (int i = 0; i < contadorComponentes; i++)
        {
            numerocomp[i] -= cantidadPedido * cantidadcom[n - 1][i];
        }
        printf("\nPedido procesado exitosamente.\n");
    }
    else
    {
        printf("\nNo es posible realizar el pedido debido a la falta de componentes.\n");
    }
}