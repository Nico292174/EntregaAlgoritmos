#include <iostream>
#include <cassert>
#include <climits>
using namespace std;

struct nodoHeap
{
    int origen;
    int destino;
    int peso;
};

class MinHeap
{
private:
    nodoHeap **vec;
    int largo;
    int primeroLibre;

    void swap(int a, int b)
    {
        nodoHeap *aux = vec[a];
        vec[a] = vec[b];
        vec[b] = aux;
    }

    int padre(int pos)
    {
        return pos / 2;
    }

    int hijoDer(int pos)
    {
        return (pos * 2) + 1;
    }

    int hijoIzq(int pos)
    {
        return pos * 2;
    }

    void hundir(int pos)
    {
        if (pos < primeroLibre)
        {
            int izq = hijoIzq(pos);
            int der = hijoDer(pos);
            int menor = pos;

            if (izq < primeroLibre && vec[izq]->peso < vec[menor]->peso)
            {
                menor = izq;
            }

            if (der < primeroLibre && vec[der]->peso < vec[menor]->peso)
            {
                menor = der;
            }

            if (menor != pos)
            {
                swap(pos, menor);
                hundir(menor);
            }
        }
    }

    void flotar(int pos)
    {
        while (pos > 1 && vec[padre(pos)]->peso > vec[pos]->peso)
        {
            swap(pos, padre(pos));
            pos = padre(pos);
        }
    }

public:
    // Constructor
    MinHeap(int tamanio)
    {
        this->vec = new nodoHeap *[tamanio + 1];
        this->largo = tamanio + 1;
        this->primeroLibre = 1;
    }

    bool vacio()
    {
        return primeroLibre == 1;
    }

    bool lleno()
    {
        return this->primeroLibre == largo;
    }

    void insertar(nodoHeap *vertice)
    {
        if (!lleno())
        {
            vec[primeroLibre] = vertice;
            flotar(primeroLibre);
            primeroLibre++;
        }
        else
        {
            cout << "El heap esta lleno" << endl;
        }
    }

    nodoHeap *tope()
    {
        if (!vacio())
        {
            nodoHeap *minimo = vec[1];
            vec[1] = vec[primeroLibre - 1];
            primeroLibre--;
            hundir(1);
            return minimo;
        }
        else
        {
            return NULL;
        }
    }

    void destruir()
    {
        for (int i = 1; i < primeroLibre; ++i)
        {
            delete vec[i];
        }
        delete[] vec;
    }
};
