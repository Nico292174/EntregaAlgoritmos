#include <iostream>
#include <cassert>
#include <climits>
using namespace std;

#include "Ejercicio6\grafoLista.h"

int main()
{
    int vertices;
    cin >> vertices;

    int aristas;
    cin >> aristas;

    grafoLista *g = new grafoLista(vertices);

    g->agregarCantAristas(aristas);

    for (int i = 0; i < aristas; i++)
    {
        int origen;
        int destino;
        int peso;

        cin >> origen;
        cin >> destino;
        cin >> peso;

        g->agregarArista(origen, destino, peso);
    }

    nodoAdyacente *l = g->kruskal();

    int sol = 0;

    while (l != NULL)
    {
        sol = sol + l->peso;
        l = l->sig;
    }

    cout << "Solucion: " << sol;

    g->destruir();

    return 0;
}
