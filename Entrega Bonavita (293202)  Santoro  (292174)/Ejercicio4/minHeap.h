#include <iostream>
#include <cassert>
#include <climits>
using namespace std;

struct nodoHeap
{
    string comida;
};

class MinHeap
{
private:
    nodoHeap **vec;
    int largo;
    int primeroLibre;

    void swap(int a, int b)
    {
        string aux = this->vec[a]->comida;
        this->vec[a]->comida = this->vec[b]->comida;
        this->vec[b]->comida = aux;
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
            if (this->vec[hijoDer(pos)]->comida.compare(this->vec[hijoIzq(pos)]->comida) <= 0)
            {
                menor = hijoDer(pos);
            }
            else
            {
                if (this->vec[hijoIzq(pos)]->comida.compare(this->vec[hijoDer(pos)]->comida) <= 0)
                {
                    menor = hijoIzq(pos);
                }
            }
            if (this->vec[menor]->comida.compare(this->vec[pos]->comida) <= 0)
            {
                swap(pos, menor);
                hundir(menor);
            }
        }
        else if (hijoIzq(pos) < this->primeroLibre)
        {
            if (this->vec[hijoIzq(pos)]->comida.compare(this->vec[pos]->comida) <= 0)
            {
                swap(pos, hijoIzq(pos));
                hundir(hijoIzq(pos));
            }
        }
    }

    void flotar(int pos)
    {
        if (pos > 1)
        { // Para que no sea la raiz
            if (this->vec[pos]->comida.compare(this->vec[padre(pos)]->comida) <= 0)
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

    void insertar(string plato)
    {
        if (this->primeroLibre <= this->largo - 1)
        {
            nodoHeap *q = new nodoHeap();
            q->comida = plato;

            int posInsertar = this->primeroLibre;
            this->vec[posInsertar] = q;
            flotar(posInsertar);
            this->primeroLibre++;
        }
        else
        {
            cout << "El heap está lleno" << endl;
        }
    }

    nodoHeap *tope()
    {
        if (this->primeroLibre > 1)
        {
            nodoHeap *q = new nodoHeap();
            q->comida = vec[1]->comida;

            swap(1, this->primeroLibre - 1);
            this->primeroLibre--;
            delete this->vec[primeroLibre];
            hundir(1);
            return q;
        }
        else
        {
            cout << "El heap esta vacio" << endl;
            return NULL;
        }
    }

    void destruir()
    {
        delete[] this->vec;
    }
};