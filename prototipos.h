int menu();
void ingresarcomponentes(float *numerocomponentes, char componentes[][30], int *contador);
int productosaFabricar(char productos[][30], float *tiempo, float cantidad[][10], int contador, char componentes[][30]);
void EncontrarProducto(char productos[][30], float tiempo[], float cantidad[][10], char componentes[][30], int contadorComponentes, int contadorProductos);
void editarProducto(char productos[][30], float tiempo[], float cantidad[][10], char componentes[][30], int contadorComponentes, int contadorProductos);
void eliminarProducto(char productos[][30], float tiempo[], float cantidad[][10], int *contadorProductos, int contadorComponentes);
void productosPedir(char productos[][30], float cantidadcom[][10], float numerocomp[], char componentes[][30], int contadorComponentes, int contadorProductos, float tiempo[]);




