#include <iostream>
#include <string>
#include <cassert>
using namespace std;

#include "Ejercicio1\maxHeap.cpp"
#include "Ejercicio1\tablaHash.cpp"

int main()
{
    int ordenes;
    cin >> ordenes;
    TablaHash *tabla = new TablaHash(ordenes);
    MaxHeap *heap = new MaxHeap(ordenes);
    for (int i = 0; i < ordenes; i++)
    {
        string comida;
        cin >> comida;
        tabla->insertar(comida);
    }
    for (int i = 0; i < ordenes; i++)
    {
        bool seguir = true;
        while (seguir)
        {
            nodoLista *q = tabla->eliminar(i);

            if (q != NULL)
            {
                heap->insertar(q->comida, q->cant);
            }
            else
            {
                seguir = false;
            }
        }
    }
    while (!heap->vacio())
    {
        cout << heap->tope()->comida << endl;
    }
    
    tabla->destruir();
    heap->destruir();
    return 0;
};