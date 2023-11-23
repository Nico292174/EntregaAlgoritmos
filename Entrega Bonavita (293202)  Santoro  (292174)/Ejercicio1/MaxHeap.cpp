#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct nodoHeap
{
    int cant;
    string comida;
};

class MaxHeap
{
private:
    nodoHeap **vec;
    int largo;
    int primeroLibre;

    void swap(int a, int b)
    {
        string aux = this->vec[a]->comida;
        int numeroAux = this->vec[a]->cant;
        this->vec[a]->comida = this->vec[b]->comida;
        this->vec[a]->cant = this->vec[b]->cant;
        this->vec[b]->comida = aux;
        this->vec[b]->cant = numeroAux;
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
            int mayor;
            if (this->vec[hijoDer(pos)]->cant > this->vec[hijoIzq(pos)]->cant)
            {
                mayor = hijoDer(pos);
            }
            else
            {
                if (this->vec[hijoDer(pos)]->cant < this->vec[hijoIzq(pos)]->cant)
                {
                    mayor = hijoIzq(pos);
                }
                else
                {
                    if (this->vec[hijoDer(pos)]->cant == this->vec[hijoIzq(pos)]->cant)
                    {
                        if (this->estaEnOrdenAlfabetico(this->vec[hijoDer(pos)]->comida, this->vec[hijoIzq(pos)]->comida))
                        {
                            mayor = hijoDer(pos);
                        }
                        else
                        {
                            mayor = hijoIzq(pos);
                        }
                    }
                }
            }
            if (this->vec[mayor]->cant > this->vec[pos]->cant)
            {
                swap(pos, mayor);
                hundir(mayor);
            }
            else
            {
                if (this->vec[mayor]->cant == this->vec[pos]->cant)
                {
                    if (this->estaEnOrdenAlfabetico(this->vec[mayor]->comida, this->vec[pos]->comida))
                    {
                        swap(pos, mayor);
                        hundir(mayor);
                    }
                }
            }
        }
        else if(hijoIzq(pos) < this->primeroLibre)
        {
            if (this->vec[hijoIzq(pos)]->cant > this->vec[pos]->cant)
            {
                swap(pos, hijoIzq(pos));
                hundir(hijoIzq(pos));
            }
            else 
            {
                if (this->vec[hijoIzq(pos)]->cant == this->vec[pos]->cant && estaEnOrdenAlfabetico(this->vec[hijoIzq(pos)]->comida, this->vec[pos]->comida))
                {
                    swap(pos, hijoIzq(pos));
                    hundir(hijoIzq(pos));
                }
            }
        }
    }

    void flotar(int pos)
    {
        if (pos > 1)
        { // Para que no sea la raiz
            if (this->vec[pos]->cant > this->vec[padre(pos)]->cant)
            {
                swap(pos, padre(pos));
                flotar(padre(pos));
            }
            else if (this->vec[pos]->cant == this->vec[padre(pos)]->cant)
            {
                if (this->estaEnOrdenAlfabetico(this->vec[pos]->comida, this->vec[padre(pos)]->comida))
                {
                    swap(pos, padre(pos));
                    flotar(padre(pos));
                }
            }
        }
    }

public:
    // Constructor
    MaxHeap(int tamanio)
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
    void insertar(string plato, int cantidad)
    {
        nodoHeap *q = new nodoHeap();
        q->comida = plato;
        q->cant = cantidad;
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
        q->cant = vec[1]->cant;
        q->comida = vec[1]->comida;
        swap(1, this->primeroLibre - 1);
        this->primeroLibre--;
        delete this->vec[primeroLibre];
        hundir(1);
        return q;
    }

    void destruir()
    {
        delete this->vec;
    }
    int menor(int a, int b)
    {
        if (a < b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }
    bool estaEnOrdenAlfabetico(string palabra1, string palabra2)
    {
        int largo1 = palabra1.length();
        int largo2 = palabra2.length();
        int min = menor(largo1, largo2);
        for (int i = 0; i < min; i++)
        {
            if (palabra1[i] < palabra2[i])
            {
                return true;
            }
            else if (palabra1[i] > palabra2[i])
            {
                return false;
            }
        }
        return largo1 < largo2;
    }
};