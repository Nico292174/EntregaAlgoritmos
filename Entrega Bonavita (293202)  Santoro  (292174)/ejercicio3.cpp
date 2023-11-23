#include <iostream>
#include <string>
#include <cassert>
using namespace std;

#include "Ejercicio3\maxHeap.h"

int main()
{
    int nroPacientes;
    cin >> nroPacientes;

    MaxHeap *heap = new MaxHeap(nroPacientes);

    for (int i = 0; i < nroPacientes; i++)
    {
        int nro;
        int orden;
        int tiempo;
        int urg;

        cin >> nro;
        cin >> tiempo;
        cin >> urg;

        heap->insertar(nro, i, tiempo, urg);
    }

    while (!heap->vacio())
    {
        cout << heap->tope()->nroPaciente << endl;
    }

    heap->destruir();

    return 0;
}
