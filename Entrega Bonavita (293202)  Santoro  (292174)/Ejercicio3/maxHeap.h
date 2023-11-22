
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct nodoHeap
{
    int ordenDellegada;
    int nroPaciente;
    int tiempoLlegada;
    int urgencia;
};

class MaxHeap
{
private:
    nodoHeap **vec;
    int largo;
    int primeroLibre;

    void swap(int a, int b)
    {
        nodoHeap *ptr = this->vec[a];
        this->vec[a] = this->vec[b];
        this->vec[b] = ptr;
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

    bool mayorPrioridad(int pos1, int pos2)
    {
        if (this->vec[pos1]->urgencia > this->vec[pos2]->urgencia)
        {
            return true;
        }
        else
        {
            if (this->vec[pos1]->urgencia == this->vec[pos2]->urgencia)
            {
                if (this->vec[pos1]->tiempoLlegada < this->vec[pos2]->tiempoLlegada)
                {
                    return true;
                }
                else
                {
                    if (this->vec[pos1]->tiempoLlegada == this->vec[pos2]->tiempoLlegada)
                    {
                        if (this->vec[pos1]->ordenDellegada < this->vec[pos2]->ordenDellegada)
                        {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    void hundir(int pos)
    {
        if (hijoDer(pos) < this->primeroLibre && hijoIzq(pos) < this->primeroLibre)
        {
            int mayor;
            if (mayorPrioridad(hijoIzq(pos), hijoDer(pos)))
            {
                mayor = hijoIzq(pos);
            }
            else
            {
                mayor = hijoDer(pos);
            }
            if (mayorPrioridad(mayor, pos))
            {
                swap(pos, mayor);
                hundir(mayor);
            }
        }
        else
        {
            // Solo tengo hijo izq
            if (hijoIzq(pos) < this->primeroLibre && mayorPrioridad(hijoIzq(pos), pos))
            {
                swap(pos, hijoIzq(pos));
                hundir(hijoIzq(pos));
            }
        }
    }

    void flotar(int pos)
    {
        if (pos > 1)
        { // No es la raiz
            if (mayorPrioridad(pos, padre(pos)))
            {
                swap(pos, padre(pos));
                flotar(padre(pos));
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

    void insertar(int nro, int orden, int tiempo, int urg)
    {
        nodoHeap *q = new nodoHeap();
        q->nroPaciente = nro;
        q->ordenDellegada = orden;
        q->tiempoLlegada = tiempo;
        q->urgencia = urg;

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
        q->nroPaciente = vec[1]->nroPaciente;
        q->ordenDellegada = vec[1]->ordenDellegada;
        q->tiempoLlegada = vec[1]->tiempoLlegada;
        q->urgencia = vec[1]->urgencia;

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
};
