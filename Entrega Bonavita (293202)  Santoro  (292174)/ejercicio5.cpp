#include <iostream>
#include <string>
#include <cassert>
#include <limits.h>
#include "Ejercicio5/GrafoListaAdyacencia.cpp"
#include "Ejercicio5/MinHeap.cpp"
using namespace std;

int main()
{
    int cantVertices;
    int cantAristas;
    cin >> cantVertices >> cantAristas;
    grafoLista *grafo = new grafoLista(cantVertices);
    for (int i = 0; i < cantAristas; i++)
    {
        int elOrigen;
        int elDestino;
        int elPeso;

        cin >> elOrigen >> elDestino >> elPeso;
        grafo->agregarArista(elOrigen, elDestino, elPeso);
    }

    int *vectorCostos = new int[cantVertices + 1]();
    for (int i = 0; i < cantVertices; i++)
    {
        vectorCostos[i] = INT_MAX;
    }
    bool *visitados = new bool[cantVertices + 1]();
    MinHeap *heap = new MinHeap(cantVertices*cantVertices);
    int origenFijado;
    int destinoDeseado;
    cin >> origenFijado >> destinoDeseado;

    vectorCostos[origenFijado] = 0;
    heap->insertar(origenFijado, 0);
    while (!heap->vacio())
    {
        nodoHeap *actual = heap->tope();
        int verticeActual = actual->vertice;
        if (!visitados[verticeActual])
        {
            visitados[verticeActual] = true;
            nodoAdyacente *adyacentesActuales = grafo->obtenerAdyacentes(verticeActual);

            while (adyacentesActuales != NULL)
            {
                int verticeAdyacente = adyacentesActuales->destino;
                int costoAdyacente = adyacentesActuales->peso;

                if (!visitados[verticeAdyacente] && vectorCostos[verticeAdyacente] > (vectorCostos[verticeActual] + costoAdyacente))
                {
                    vectorCostos[verticeAdyacente] = vectorCostos[verticeActual] + costoAdyacente;
                    heap->insertar(verticeAdyacente, vectorCostos[verticeAdyacente]);
                }
                adyacentesActuales = adyacentesActuales->sig;
            }
        }
    }
    if(vectorCostos[destinoDeseado] == INT_MAX){
        cout << -1;
    }else{
        cout << vectorCostos[destinoDeseado];
    }
    grafo->destruir();
    delete[] visitados;
    delete[] vectorCostos;
    heap->destruir();
        
    return 0;
}