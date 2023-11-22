#include <iostream>
#include <climits>
using namespace std;

// Me indica la fila del proximo cero
int proximaFila(int cantFilas, int cantColumnas, int **matriz)
{
    for (int i = 0; i < cantFilas; i++)
    {
        for (int j = 0; j < cantColumnas; j++)
        {
            if (matriz[i][j] == 0)
            {
                return i;
            }
        }
    }
    return -1;
}

// Me indica la columna del proximo cero
int proximaColumna(int cantFilas, int cantColumnas, int **matriz)
{
    for (int i = 0; i < cantFilas; i++)
    {
        for (int j = 0; j < cantColumnas; j++)
        {
            if (matriz[i][j] == 0)
            {
                return j;
            }
        }
    }
    return -1;
}

void marcar(int filActual, int colActual, int num, int **&matriz)
{
    matriz[filActual][colActual] = num;
}

void desmarcar(int filActual, int colActual, int **&matriz)
{
    matriz[filActual][colActual] = 0;
}

// Para saber en que subBloque de la matriz estoy
int enQueBloqueEstoy(int fil, int col, int cantidadFil, int cantidadCol)
{
    int filasPorBloque = cantidadFil / 3;
    int colsPorBloque = cantidadCol / 3;

    int bloqueFila = fil / filasPorBloque;
    int bloqueCol = col / colsPorBloque;

    int bloque = bloqueFila * 3 + bloqueCol + 1;

    return bloque;
}

bool esValida(int fila, int columna, int num, int **matriz, int cantFil, int cantCol)
{
    // Revisar fila y columna
    for (int i = 0; i < cantCol; i++)
    {
        if (matriz[fila][i] == num)
            return false;
    }
    for (int i = 0; i < cantFil; i++)
    {
        if (matriz[i][columna] == num)
            return false;
    }

    // Revisar bloque
    int filasPorBloque = cantFil / 3;
    int colsPorBloque = cantCol / 3;
    int inicioFila = fila - fila % filasPorBloque;
    int inicioColumna = columna - columna % colsPorBloque;

    for (int i = 0; i < filasPorBloque; i++)
    {
        for (int j = 0; j < colsPorBloque; j++)
        {
            if (matriz[i + inicioFila][j + inicioColumna] == num)
            {
                return false;
            }
        }
    }

    return true;
}

// Recorro toda la matriz y no hay ceros
bool esSolucion(int cantFilas, int cantColumnas, int **matriz)
{
    if (proximaColumna(cantFilas, cantColumnas, matriz) == -1 && proximaFila(cantFilas, cantColumnas, matriz) == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Imprimo matriz
bool procesarSolucion(int cantFilas, int cantColumnas, int **matriz)
{
    for (int i = 0; i < cantFilas; i++)
    {
        for (int j = 0; j < cantColumnas; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << "" << endl;
    }
}

int max(int num1, int num2)
{
    if (num1 > num2)
    {
        return num1;
    }
    else
    {
        return num2;
    }
}

// Backtracking
void sudoku(int cantFilas, int cantCol, int **matriz)
{
    int filActual = proximaFila(cantFilas, cantCol, matriz);
    int colActual = proximaColumna(cantFilas, cantCol, matriz);

    if (filActual == -1)
    {
        procesarSolucion(cantFilas, cantCol, matriz);
        return;
    }

    // i toma el valor maximo de columnas y filas (en el caso de una matriz 12x9 -> 12)
    for (int num = 1; num <= max(cantFilas, cantCol); num++)
    {
        if (esValida(filActual, colActual, num, matriz, cantFilas, cantCol))
        {
            marcar(filActual, colActual, num, matriz);
            sudoku(cantFilas, cantCol, matriz);
            desmarcar(filActual, colActual, matriz);
        }
    }
}

int main()
{
    int cantFilas;
    int cantColumnas;
    cin >> cantFilas;
    cin >> cantColumnas;

    int **matriz = new int *[cantFilas]();
    for (int i = 0; i < cantFilas; i++)
    {
        matriz[i] = new int[cantColumnas]();
    }
    for (int i = 0; i < cantFilas; i++)
    {
        for (int j = 0; j < cantColumnas; j++)
        {
            int num;
            cin >> num;
            matriz[i][j] = num;
        }
    }

    sudoku(cantFilas, cantColumnas, matriz);

    for (int i = 0; i < cantFilas; i++)
    {
        delete matriz[i];
    }
    delete[] matriz;

    return 0;
}
