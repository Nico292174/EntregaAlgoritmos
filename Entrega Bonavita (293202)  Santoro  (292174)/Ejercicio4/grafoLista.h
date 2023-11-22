#include <iostream>
#include <cassert>
#include <climits>
using namespace std;

#include "minHeap.h"

struct nodoLista
{
    string comida;
    nodoLista *sig;
};

struct nodoGrafo
{
    string plato;
    nodoGrafo *sig;
};

class grafo
{
private:
    nodoGrafo **vector;
    int cantVertices;

    int fHash(string plato)
    {
        int suma = 0;
        for (int i = 0; i < plato.length(); i++)
        {
            suma = suma + int(plato[i]);
        }
        return (suma % this->cantVertices);
    }

    nodoGrafo *copiarLista(nodoGrafo *l)
    {
        if (l != NULL)
        {
            nodoGrafo *ret = new nodoGrafo();
            ret->plato = l->plato;
            ret->sig = copiarLista(l->sig);
            return ret;
        }
        else
        {
            return NULL;
        }
    }

public:
    grafo(int tam)
    {
        this->cantVertices = tam;
        this->vector = new nodoGrafo *[tam]();
        for (int i = 0; i < tam; i++)
        {
            this->vector[i] = NULL;
        }
    }

    int cantidadVertices()
    {
        return this->cantVertices;
    }

    void insertar(string plato)
    {
        nodoGrafo *aInsertar = new nodoGrafo();
        aInsertar->plato = plato;
        aInsertar->sig = NULL;

        int pos = fHash(plato);
        int i = 1;

        while (this->vector[pos] != NULL)
        {
            pos = abs(fHash(plato) + i) % this->cantVertices;
            i++;
        }
        vector[pos] = aInsertar;
    }

    void insertarArista(string plato, string arista)
    {
        nodoGrafo *aInsertar = new nodoGrafo();
        aInsertar->plato = arista;
        aInsertar->sig = NULL;

        int pos = fHash(plato);
        int i = 1;
        bool bandera = false;
        while (!bandera)
        {
            if (this->vector[pos] != NULL && vector[pos]->plato == plato)
            {
                aInsertar->sig = vector[pos]->sig;
                vector[pos]->sig = aInsertar;
                bandera = true;
            }
            else
            {
                pos = (abs(fHash(plato) + i) % this->cantVertices);
                i++;
            }
        }
    }

    // Recibe un plato y devuelve la posicion de ese plato en la tabla de hash
    int encontrarPos(string s)
    {
        int pos = this->fHash(s);
        int i = 1;
        bool bandera = false;
        while (!bandera)
        {
            if (this->vector[pos]->plato == s)
            {
                bandera = true;
                return pos;
            }
            else
            {
                pos = abs(fHash(s) + i) % this->cantVertices;
                i++;
            }
        }
        return pos;
    }

    nodoGrafo *adyacentes(string s)
    {
        return this->copiarLista(this->vector[this->encontrarPos(s)]);
    }

    nodoGrafo *adyacentes(int i)
    {
        return this->copiarLista(this->vector[i]);
    }

    void destruir()
    {
        for (int i = 0; i < this->cantVertices; i++)
        {
            nodoGrafo *l = this->vector[i];
            while (l != NULL)
            {
                nodoGrafo *aBorrar = l;
                l = l->sig;
                delete aBorrar;
            }
        }
        delete[] this->vector;
    }

    nodoLista *ordenTopologico()
    {
        nodoLista *l = NULL;
        nodoLista *ultimo = l;

        int *gradoEntrada = new int[cantVertices]();

        for (int i = 0; i < this->cantVertices; i++)
        {
            if (adyacentes(i) != NULL)
            {
                nodoGrafo *q = this->adyacentes(i)->sig;
                while (q != NULL)
                {
                    gradoEntrada[this->encontrarPos(q->plato)]++;
                    q = q->sig;
                }
            }
        }

        MinHeap *heap = new MinHeap(this->cantVertices);

        int cont = 0;
        for (int i = 0; i < this->cantVertices; i++)
        {
            // Cuando ya inserte todos los datos en la tabla de hash, las posiciones i van a corresponder a una sola comida (ya no se mueven)
            if (gradoEntrada[i] == 0 && this->vector[i] != NULL)
            {
                heap->insertar(this->vector[i]->plato);
            }
        }

        while (!heap->vacio())
        {
            cont++;
            string plato = heap->tope()->comida;

            nodoGrafo *adyacentes = this->adyacentes(plato);

            while (adyacentes != NULL)
            {
                int n = this->encontrarPos(adyacentes->plato);
                gradoEntrada[n]--;
                if (gradoEntrada[n] == 0)
                {
                    heap->insertar(vector[n]->plato);
                }
                adyacentes = adyacentes->sig;
            }

            nodoLista *q = new nodoLista();
            q->comida = plato;
            q->sig = NULL;

            if (l == NULL)
            {
                l = q;
                ultimo = q;
            }
            else
            {
                ultimo->sig = q;
                ultimo = q;
            }
        }

        delete[] gradoEntrada;
        heap->destruir();

        if (cont < this->cantVertices)
        {
            cout << "CICLO DETECTADO" << endl;
            return NULL;
        }
        else
        {
            return l;
        }
    }
};