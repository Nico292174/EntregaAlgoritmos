#include <iostream>
#include <string>
#include <cassert>
#include <limits.h>
using namespace std;

struct nodoHeap
{
    int vertice;
    int costo;
};



class MinHeap
{
private:
    nodoHeap **vec;
    int largo;
    int primeroLibre;

    void swap(int a, int b)
    {
        nodoHeap* aux = this->vec[a];
        this->vec[a] = this->vec[b];
        this->vec[b] = aux;
    }

    int padre(int pos)
    {
        return (pos / 2);
    }

    int hijoDer(int pos)
    {
        return (pos * 2 + 1);
    }

    int hijoIzq(int pos)
    {
        return (pos * 2);
    }

    void hundir(int pos)
    {
        if (hijoDer(pos) < this->primeroLibre && hijoIzq(pos) < this->primeroLibre)
        {
            int menor;
            if (this->vec[hijoDer(pos)]->costo < this->vec[hijoIzq(pos)]->costo)
            {
                menor = hijoDer(pos);
            }
            else
            {
                menor = hijoIzq(pos);
            }
            if (this->vec[menor]->costo < this->vec[pos]->costo)
            {
                swap(pos, menor);
                hundir(menor);
            }
        }
        else if (hijoIzq(pos)<this->primeroLibre &&this->vec[hijoIzq(pos)]->costo< this->vec[pos]->costo)
        {
            swap(pos, hijoIzq(pos));
            hundir(hijoIzq(pos));
        }
    }
    void flotar(int pos)
    {
        if (pos > 1)
        { // Para que no sea la raiz
            if (this->vec[pos]->costo < this->vec[padre(pos)]->costo)
            {
                swap(pos, padre(pos));
                flotar(padre(pos));
            }
        }
    }

public:
    // Constructor
    MinHeap(int tamanio)
    {
        this->vec = new nodoHeap *[tamanio + 1]();
        this->largo = tamanio + 1;
        this->primeroLibre = 1;
    }
    bool vacio()
    {
        if (this->primeroLibre == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool lleno()
    {
        if (this->primeroLibre >= this->largo + 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void insertar(int unVertice, int unCosto)
    {
        nodoHeap *q = new nodoHeap();
        q->vertice = unVertice;
        q->costo = unCosto;
        int posInsertar = this->primeroLibre;
        if (posInsertar <= this->largo)
        {
            this->vec[posInsertar] = q;
            flotar(posInsertar);
            this->primeroLibre++;
        }
    }

    nodoHeap *tope()
    {
        nodoHeap *q = new nodoHeap();
        q->vertice = vec[1]->vertice;
        q->costo = vec[1]->costo;
        if(this->primeroLibre > 2){
            this->vec[1] = this->vec[primeroLibre-1];
            hundir(1);
        }
        this->primeroLibre--;
        return q;
    }

    void destruir()
    {
        delete[] this->vec;
    }
};