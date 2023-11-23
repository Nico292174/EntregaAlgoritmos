#include <iostream>
#include <string>
#include <cassert>
#include <limits.h>
using namespace std;


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

    void agregarArista(int unOrigen, int unDestino, int unPeso)
    {
        nodoAdyacente *nuevo = new nodoAdyacente();
        nuevo->origen = unOrigen;
        nuevo->destino = unDestino;
        nuevo->peso = unPeso;

        nuevo->sig = this->vec[unOrigen];
        this->vec[unOrigen] = nuevo;
    }

    nodoAdyacente *eliminarPrimerAdyacente(int unOrigen)
    {
        nodoAdyacente *ret = this->vec[unOrigen];
        this->vec[unOrigen] = this->vec[unOrigen]->sig;
        return ret;
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
        delete[] this->vec;
    }

    
};