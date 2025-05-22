#include <stdio.h>
#include <string.h>
#include "prototipos.h"

void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}


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
        printf("7. Reabastecer stock\n");
        printf("8. Salir.\n");
        printf("----------------------------------------------------\n");
        printf(">>>> ");
        scanf("%d", &opc);
        limpiarBuffer();
        if (opc < 1 || opc > 8)

            printf("\nIngrese un numero que se encuentre dentro del menu.\n");
    
        } while (opc < 1 || opc > 8);
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
            printf("\nSolo puede ingresar numeros enteros positivos.\n");
        else if (total < 1)
            printf("\nDebe registrar al menos un componente.\n");
        else if (total > 10)
            printf("\nRecuerde el número maximo de productos es 10.\n");
    } while (valido != 1 || total < 1 || total > 10);

    while (*contador < total)
    {
        printf("\n\nIngrese el nombre del componente %d que se tiene en el inventario: ", *contador + 1);
        fgets(componentes[*contador], 30, stdin);
        componentes[*contador][strcspn(componentes[*contador], "\n")] = 0;
        printf("Ingrese la cantidad de %s que se tiene en stock: ", componentes[*contador]);
        scanf("%f", &numerocomponentes[*contador]);
        limpiarBuffer();
        (*contador)++;
    }

    printf("\n----------Componentes y Stock----------\n");
    printf("______________________________\n");
    printf("Componentes\tStock\n");
    printf("______________________________\n");
    for (int i = 0; i < *contador; i++)
    
        printf("%s\t\t%.2f\n", componentes[i], numerocomponentes[i]);
    
        printf("______________________________\n");
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

            printf("\nSolo puede ingresar numeros positivos.\n");
        else if (cantproductos < 1)
            printf("\nDebe registrar al menos un producto.\n");
        
            else if (cantproductos > 5)
            printf("\nRecuerde el número maximo de productos es 5.\n");
    } while (validez != 1 || cantproductos < 1 || cantproductos > 5);

    printf("\n\nIngrese los %d productos:\n", cantproductos);
    for (int i = 0; i < cantproductos; i++)
    {
        printf("\n\nIngrese el producto numero %d: ", i + 1);
        fgets(productos[i], 30, stdin);
        productos[i][strcspn(productos[i], "\n")] = 0;

        printf("Ingrese el tiempo necesario para la creacion de %s: ", productos[i]);
        scanf("%f", &tiempo[i]);
        limpiarBuffer();
        for (int j = 0; j < contador; j++)
        {
            printf("Cuantos %s necesita para su fabricacion?: ", componentes[j]);
            scanf("%f", &cantidad[i][j]);
            limpiarBuffer();
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
    BuscarProducto[strcspn(BuscarProducto, "\n")] = 0;

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
        
            printf("%s: %.1f unidades\n", componentes[j], cantidad[i][j]);
            break;
        }
    }
    if (!encontrado)
        printf("\nNo se encuentra dicho producto con ese nombre.\n");
}

void editarProducto(char productos[][30], float tiempo[], float cantidad[][10], char componentes[][30], int contadorComponentes, int contadorProductos)
{
    char nombreBuscar[30];
    int encontrado = -1;


    printf("Ingrese el nombre del producto a editar: ");
    limpiarBuffer();
    fgets(nombreBuscar, sizeof(nombreBuscar), stdin);
    nombreBuscar[strcspn(nombreBuscar, "\n")] = 0;

    if (strlen(nombreBuscar) == 0)
    {
        printf("No se ingresó ningún nombre.\n");
        return;
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
    printf("Ingrese el nuevo nombre del producto: ");
    fgets(productos[encontrado], sizeof(productos[encontrado]), stdin);
    productos[encontrado][strcspn(productos[encontrado], "\n")] = 0;

    printf("Ingrese el nuevo tiempo de produccion: ");
    scanf("%f", &tiempo[encontrado]);
    limpiarBuffer();

    for (int j = 0; j < contadorComponentes; j++)
    {
        printf("Ingrese la nueva cantidad de %s necesaria: ", componentes[j]);
        scanf("%f", &cantidad[encontrado][j]);
        limpiarBuffer();
    }
    
    printf("Producto actualizado correctamente.\n");
}

void eliminarProducto(char productos[][30], float tiempo[], float cantidad[][10], int *contadorProductos, int contadorComponentes)
{
    char nombreEliminar[30];
    int encontrado = -1;


    printf("Ingrese el nombre del producto que desea eliminar: ");
    limpiarBuffer();
    fgets(nombreEliminar, sizeof(nombreEliminar), stdin);
    nombreEliminar[strcspn(nombreEliminar, "\n")] = 0;

    if (strlen(nombreEliminar) == 0)
    {
        printf("No se ingresó ningún nombre.\n");
        return;
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
    
        cantidad[i][j] = cantidad[i + 1][j];
    }
    (*contadorProductos)--;
    
    printf("\nProducto eliminado correctamente.\n");
}

void productosPedir(char productos[][30], float cantidadcom[][10], float numerocomp[], char componentes[][30], int contadorComponentes, int contadorProductos, float tiempo[])
{
    int n, cantidadPedido, validez;
    float tiempoPedido;
    char entrada[50];

    printf("\nCual producto desea de nuestro inventario?\n");
    for (int i = 0; i < contadorProductos; i++)
        printf("%d. %s\n", i + 1, productos[i]);

    do
    {
        printf("Ingrese el numero del producto que desea: ");
        fgets(entrada, sizeof(entrada), stdin);
        validez = sscanf(entrada, "%d", &n);
        if (validez != 1 || n < 1 || n > contadorProductos)
            printf("Producto no valido.\n");
    } while (validez != 1 || n < 1 || n > contadorProductos);

    do
    {
        printf("\nPor favor ingrese cuantos %s desea fabricar: ", productos[n - 1]);
        fgets(entrada, sizeof(entrada), stdin);
        validez = sscanf(entrada, "%d", &cantidadPedido);
        if (validez != 1 || cantidadPedido < 1)
            printf("Error: Debe ingresar un número entero positivo.\n");
    } while (validez != 1 || cantidadPedido < 1);

    do
    {
        printf("Ingrese en cuanto tiempo (en minutos) desea que se complete la produccion: ");
        fgets(entrada, sizeof(entrada), stdin);
        validez = sscanf(entrada, "%f", &tiempoPedido);
        if (validez != 1 || tiempoPedido <= 0.0f)
            printf("Error: Debe ingresar un número decimal positivo.\n");
    } while (validez != 1 || tiempoPedido <= 0.0f);

    float tiempoNecesario = tiempo[n - 1] * cantidadPedido;
    if (tiempoPedido < tiempoNecesario)
    {
        printf("\nNo es posible completar la produccion en el tiempo solicitado.\n");
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
        printf("\n\nStock actualizado de componentes\n");
        printf("_________________________________\n");
        printf("Componente\tStock\n");
        printf("_________________________________\n");
        for (int i = 0; i < contadorComponentes; i++)
        {
            printf("%s\t\t%.2f\n", componentes[i], numerocomp[i]);
        }
        printf("_________________________________\n");
    }
    else
    {
        printf("\nNo es posible realizar el pedido debido a la falta de componentes.\n");
    }
}
void restablecerStock(float numerocomp[], char componentes[][30], int contadorComponentes)
{
    char entrada[20];
    int validez, cantidadAgregar, i;
    printf("\n---- Reabastecer Stock de Componentes ----\n");
    printf("Componentes actuales:\n");
    printf("_________________________________\n");
    printf("Componente\tStock\n");
    printf("_________________________________\n");
    for (i = 0; i < contadorComponentes; i++)
    {
        printf("%d. %s\t\t%.2f\n", i + 1, componentes[i], numerocomp[i]);
    }
    printf("_________________________________\n");

    do
    {
        printf("Ingrese el número del componente que desea reabastecer: ");
        fgets(entrada, sizeof(entrada), stdin);
        validez = sscanf(entrada, "%d", &i);
        if (validez != 1 || i < 1 || i > contadorComponentes)
        {
            printf("Número de componente inválido.\n");
        }
    } while (validez != 1 || i < 1 || i > contadorComponentes);

    do
    {
        printf("Ingrese la cantidad a agregar al stock de %s: ", componentes[i - 1]);
        fgets(entrada, sizeof(entrada), stdin);
        validez = sscanf(entrada, "%d", &cantidadAgregar);
        if (validez != 1 || cantidadAgregar < 1)
        {
            printf("Cantidad inválida, debe ser un entero positivo.\n");
        }
    } while (validez != 1 || cantidadAgregar < 1);

    numerocomp[i - 1] += cantidadAgregar;

    printf("\nStock actualizado:\n");
    printf("_________________________________\n");
    printf("Componente\tStock\n");
    printf("_________________________________\n");
    for (i = 0; i < contadorComponentes; i++)
    {
        printf("%d. %s\t\t%.2f\n", i + 1, componentes[i], numerocomp[i]);
    }
    printf("_________________________________\n");
}