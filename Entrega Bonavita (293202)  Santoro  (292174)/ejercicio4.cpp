#include <iostream>
#include <cassert>
#include <climits>
using namespace std;

#include "Ejercicio4\grafoLista.h"

int main()
{
    int platos;
    cin >> platos;

    int dependencias;
    cin >> dependencias;

    grafo *g = new grafo(platos);

    for (int i = 0; i < platos; i++)
    {
        string vertice;
        cin >> vertice;

        g->insertar(vertice);
    }

    for (int i = 0; i < dependencias; i++)
    {
        string origen;
        cin >> origen;

        string destino;
        cin >> destino;

        g->insertarArista(origen, destino);
    }

    nodoLista *resultado = g->ordenTopologico();

    g->destruir();

    if (resultado != NULL)
    {
        while (resultado != NULL)
        {
            cout << resultado->comida << endl;
            resultado = resultado->sig;
        }
    }
    return 0;
}