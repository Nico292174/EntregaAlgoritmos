#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct nodoLista
{
    string comida;
    int cant;
    nodoLista *sig;
};

// Tabla de Hash
class TablaHash
{
private:
    nodoLista **vec;
    int tamanio;

public:
    TablaHash(int tam)
    {
        this->vec = new nodoLista *[tam]();
        this->tamanio = tam;
    }

    int funcionHash(string comida)
    {
        int retorno = 0;
        for (int i = 0; i < comida.length(); i++)
        {
            retorno = retorno + comida[i];
        }
        return (retorno % this->tamanio);
    }

    void insertar(string dato)
    {
        int pos = funcionHash(dato);
        if (this->vec[pos] == NULL)
        {
            nodoLista *q = new nodoLista();
            q->comida = dato;
            q->sig = NULL;
            q->cant = 1;
            this->vec[pos] = q;
        }
        else
        {
            if (this->vec[pos]->comida == dato)
            {
                this->vec[pos]->cant++;
            }
            else
            {
                nodoLista *ptr = this->vec[pos];
                bool bandera = false;
                while (ptr->sig != NULL)
                {
                    ptr = ptr->sig;
                    if (ptr->comida == dato)
                    {
                        ptr->cant++;
                        bandera = true;
                    }
                }
                if (!bandera)
                {
                    nodoLista *q = new nodoLista();
                    q->comida = dato;
                    q->sig = NULL;
                    q->cant = 1;
                    q->sig = this->vec[pos];
                    this->vec[pos] = q;
                }
            }
        }
    }

    nodoLista *eliminar(int pos)
    { // VERIFICAR QUE AL INSERTAR EN HEAP SEA DIFERENTE DE NULL
        if (this->vec[pos] != NULL)
        {
            nodoLista *q = this->vec[pos];
            this->vec[pos] = this->vec[pos]->sig;
            return q;
        }
        return NULL;
    }

    void destruir()
    {
        delete this->vec;
    }
};
