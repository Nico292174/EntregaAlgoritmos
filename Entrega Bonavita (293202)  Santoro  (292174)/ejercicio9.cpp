#include <iostream>
#include <climits>
using namespace std;

int mochila(int *pesos, int *popularidad, int capacidadPlay, int cantidadJuegos)
{
    int **matriz = new int *[cantidadJuegos + 1]();
    for (int i = 0; i <= cantidadJuegos; i++)
    {
        matriz[i] = new int[capacidadPlay + 1]();
    }

    for (int fila = 1; fila <= cantidadJuegos; fila++)
    {
        for (int columna = 0; columna <= capacidadPlay; columna++)
        {
            int pesoActual = pesos[fila - 1];
            int popularidadActual = popularidad[fila - 1];

            if (pesoActual > columna)
            {
                matriz[fila][columna] = matriz[fila - 1][columna];
            }
            else
            {
                int popularidadUsando = popularidadActual + matriz[fila - 1][columna - pesoActual];
                int popularidadNoUsando = matriz[fila - 1][columna];
                if (popularidadNoUsando > popularidadUsando)
                {
                    matriz[fila][columna] = popularidadNoUsando;
                }
                else
                {
                    matriz[fila][columna] = popularidadUsando;
                }
            }
        }
    }
    int resp = matriz[cantidadJuegos][capacidadPlay];
    for (int i = 0; i <= cantidadJuegos; i++)
    {
        delete matriz[i];
    }
    delete[] matriz;
    return resp;
}

int main()
{
    int capacidadTotal;
    int anioActual;
    int cantidadJuegos;

    cin >> capacidadTotal;
    cin >> anioActual;
    cin >> cantidadJuegos;

    int *pesos = new int[cantidadJuegos + 1]();
    int *popularidades = new int[cantidadJuegos + 1]();

    for (int i = 1; i <= cantidadJuegos; i++)
    {
        string nombre;
        int peso;
        int popularidad;
        int anioLanzamiento;

        cin >> nombre;
        cin >> peso;
        cin >> popularidad;
        cin >> anioLanzamiento;

        pesos[i] = peso;

        int popularidadActual = popularidad - ((anioActual - anioLanzamiento) * 5);
        if (popularidadActual > 0)
        {
            popularidades[i] = popularidadActual;
        }
        else
        {
            popularidades[i] = 0;
        }
    }

    cout << "Resultado: " << mochila(pesos, popularidades, capacidadTotal, cantidadJuegos);

    delete[] pesos;
    delete[] popularidades;

    return 0;
}