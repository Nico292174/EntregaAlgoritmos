#include <iostream>
#include <cassert>
#include <climits>
using namespace std;

#include "minHeap.h"
#include "mfset.h"

struct nodoGrafo
{
    int vertice;
    int peso;
    nodoGrafo *sig;
};

struct nodoAdyacente
{
    int origen;
    int destino;
    int peso;
    nodoAdyacente *sig;
};

class grafoLista
{
private:
    nodoAdyacente **vec;
    int tamanio;
    int aristas;

public:
    grafoLista(int tamanio)
    {
        this->vec = new nodoAdyacente *[tamanio + 1]();

        for (int i = 0; i < tamanio; i++)
        {
            vec[i] = NULL;
        }

        this->tamanio = tamanio + 1;
    }

    void agregarCantAristas(int ari)
    {
        this->aristas = ari;
    }

    void agregarArista(int unOrigen, int unDestino, int unPeso)
    {
        nodoAdyacente *nuevo = new nodoAdyacente();
        nuevo->origen = unOrigen;
        nuevo->destino = unDestino;
        nuevo->peso = unPeso;
        nuevo->sig = this->vec[unOrigen];
        this->vec[unOrigen] = nuevo;
    }

    nodoAdyacente *obtenerAdyacentes(int unOrigen)
    {
        nodoAdyacente *aux = this->vec[unOrigen];
        nodoAdyacente *ret = NULL;
        while (aux != NULL)
        {
            nodoAdyacente *nuevo = new nodoAdyacente();
            nuevo->origen = aux->origen;
            nuevo->destino = aux->destino;
            nuevo->peso = aux->peso;

            nuevo->sig = ret;
            ret = nuevo;

            aux = aux->sig;
        }
        return ret;
    }

    void destruir()
    {
        for (int i = 0; i < this->tamanio; i++)
        {
            nodoAdyacente *l = this->vec[i];
            while (l != NULL)
            {
                nodoAdyacente *aBorrar = l;
                l = l->sig;
                delete aBorrar;
            }
        }
        delete[] vec;
    }

    nodoAdyacente *kruskal()
    {
        MinHeap *heap = new MinHeap(this->aristas * 2 + 1);

        for (int i = 0; i < tamanio; i++)
        {
            nodoAdyacente *adyacentes = this->obtenerAdyacentes(i);
            while (adyacentes != NULL)
            {
                nodoHeap *q = new nodoHeap();
                q->origen = adyacentes->origen;
                q->destino = adyacentes->destino;
                q->peso = adyacentes->peso;
                heap->insertar(q);

                adyacentes = adyacentes->sig;
            }
        }

        nodoAdyacente *solucion = NULL;
        MFSet *mfset = new MFSet(tamanio + 1);
        int aristasAceptadas = 0;

        while (!heap->vacio() && aristasAceptadas < this->tamanio - 1)
        {
            nodoHeap *aristaMenor = heap->tope();

            if (mfset->find(aristaMenor->origen) != mfset->find(aristaMenor->destino))
            {
                mfset->merge(aristaMenor->origen, aristaMenor->destino);

                nodoAdyacente *q = new nodoAdyacente();
                q->destino = aristaMenor->destino;
                q->origen = aristaMenor->origen;
                q->peso = aristaMenor->peso;
                q->sig = solucion;
                solucion = q;
                aristasAceptadas++;
            }
        }

        mfset->destruir();
        heap->destruir();

        return solucion;
    }
};