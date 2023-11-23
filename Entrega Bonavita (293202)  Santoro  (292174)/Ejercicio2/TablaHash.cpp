#include <iostream>
#include <string>
#include <cassert>
using namespace std;


struct nodoListaPelicula
{
    int id;
    string genero;
    int sumaPuntuacion;
    int cant;
    nodoListaPelicula *sig;
};

// Tabla de Hash Pelis
class TablaHashPelis
{
private:
    int tamanio;

    int funcionHash(int id)
    {
        return (id % this->tamanio);
    }

public:
    nodoListaPelicula **vec;
    TablaHashPelis(int tam)
    {
        this->vec = new nodoListaPelicula *[tam]();
        this->tamanio = tam;
    }

    void insertar(string generoNuevo,int idNuevo, int puntuacion)
    {
        //cout << idNuevo << endl;
        //cout << puntuacion << endl;
        //cout << "eso fue lo q entro" << endl;
        int posHash = funcionHash(idNuevo);
        if (this->vec[posHash] == NULL)
        {
            nodoListaPelicula *q = new nodoListaPelicula();
            q->id = idNuevo;
            q->genero = generoNuevo;
            q->sumaPuntuacion = puntuacion;
            q->cant = 1;
            q->sig = NULL;
            this->vec[posHash] = q;
        }
        else
        {
            nodoListaPelicula* recorrer =this->vec[posHash];
            bool encontre = false;
            while(recorrer != NULL && !encontre){ 
                if(recorrer->id == idNuevo){
                    recorrer->sumaPuntuacion = recorrer->sumaPuntuacion + puntuacion; //si lo encontre no tengo que recorrer mas
                    recorrer->cant++;
                    encontre = true;
                }else{
                    recorrer = recorrer->sig; //sino sigo recorriendo
                }
               
            }
            if(!encontre){ //recorri hasta el final y no lo encontre
                nodoListaPelicula *q = new nodoListaPelicula();
                q->id = idNuevo;
                q->genero = generoNuevo;
                q->sumaPuntuacion = puntuacion;
                q->cant = 1;
                q->sig = this->vec[posHash];

                this->vec[posHash]= q;
            }
        }
    }

    nodoListaPelicula *eliminar(int pos)
    { // VERIFICAR QUE AL INSERTAR EN HEAP SEA DIFERENTE DE NULL
        if (this->vec[pos] != NULL)
        {
            nodoListaPelicula *q = this->vec[pos];
            this->vec[pos] = this->vec[pos]->sig;
            return q;
        }
        return NULL;
    }

    void destruir()
    {
        delete[] this->vec;
    }

    string obtenerGenero(int idPeli) 
    {
        cout << "aca toy";
        int key = funcionHash(idPeli);
        if (this->vec[key]->id == idPeli) {
            return this->vec[key]->genero;
        }
        else {
            nodoListaPelicula* aux = this->vec[key];
            while (this->vec[key] != NULL) {
                if(this->vec[key]->id == idPeli){
                    return aux->genero;
                }else{
                    aux = aux->sig;
                }
            }
        }
        return "no encontre";
    }
};