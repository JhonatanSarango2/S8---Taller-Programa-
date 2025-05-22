#include <stdio.h>
#include <string.h>
#include "prototipos.h"

int main()
{
    char componentes[10][30];
    float numerocomp[10] = {0};
    int contadorComponentes = 0;
    char productos[5][30];
    float tiempo[5] = {0};
    float cantidadcom[5][10] = {{0}};
    int contadorProductos = 0;
    int opc1;

    do
    {
        opc1 = menu();
        switch (opc1)
        {
        case 1:
            ingresarcomponentes(numerocomp, componentes, &contadorComponentes);
            break;
        case 2:
            if (contadorComponentes == 0)
                printf("Primero debe ingresar componentes antes de agregar productos.\n");
            else

                contadorProductos = productosaFabricar(productos, tiempo, cantidadcom, contadorComponentes, componentes);

            break;
        case 3:

            if (contadorProductos == 0)

                printf("No hay productos ingresados para buscar.\n");

            else

                EncontrarProducto(productos, tiempo, cantidadcom, componentes, contadorComponentes, contadorProductos);
            
            break;
        case 4:
            if (contadorProductos == 0)

                printf("No hay productos ingresados para editar.\n");
            
            else

                editarProducto(productos, tiempo, cantidadcom, componentes, contadorComponentes, contadorProductos);
            
            break;
        case 5:
            if (contadorProductos == 0)

                printf("No hay productos ingresados para eliminar.\n");
                else
                eliminarProducto(productos, tiempo, cantidadcom, &contadorProductos, contadorComponentes);

            break;
        case 6:

            if (contadorProductos == 0)

    
            printf("No hay productos ingresados para pedir.\n");
            else

    
            productosPedir(productos, cantidadcom, numerocomp, componentes, contadorComponentes, contadorProductos, tiempo);
            break;
        case 7:
        void restablecerStock(numerocomp, componentes, contadorComponentes);
            break;

            case 8:
            printf("Fin del programa.\n");
            break;
        default:
            printf("Opción inválida.\n");
            break;
        }
    } while (opc1 != 8);

    return 0;
}
