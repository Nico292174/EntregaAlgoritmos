#include <iostream>
#include <string>
#include <cassert>
#include "Ejercicio2/TablaHash.cpp"
using namespace std;

struct nodoArrayGenero{
    string genero;
    int puntuacionMaxima;
    int idMaxima;
};

int main(){
    int cantidadGeneros;
    cin >> cantidadGeneros;
    nodoArrayGenero** arrayGeneros = new nodoArrayGenero*[cantidadGeneros];
    for (int i=0; i<cantidadGeneros; i++){
        string generoActual;
        cin >> generoActual;
        arrayGeneros[i] = new nodoArrayGenero();
        arrayGeneros[i]->genero = generoActual; 
        arrayGeneros[i]->idMaxima = 0;
        arrayGeneros[i]->puntuacionMaxima = 0;
    }

    int cantidadPelis;
    cin >> cantidadPelis;
    TablaHashPelis* tablaPelis = new TablaHashPelis(cantidadPelis);
    for(int i=0; i<cantidadPelis; i++){
        int idPeliAgregar;
        string generoPeliAgregar;
        cin >> idPeliAgregar >> generoPeliAgregar;
        tablaPelis->insertar(generoPeliAgregar, idPeliAgregar, 0);
        
    }
    
    int cantPuntuaciones;
    cin >> cantPuntuaciones;
    for(int i=0; i<cantPuntuaciones; i++){
        int idPeliPuntuacion;
        int puntuacionPeli;
        cin >> idPeliPuntuacion >> puntuacionPeli;
        tablaPelis->insertar("",idPeliPuntuacion,puntuacionPeli);
    }

    for(int i=0; i<cantidadPelis; i++){
        nodoListaPelicula* aux = tablaPelis->vec[i];
        while(aux!=NULL){
            string genero = aux->genero;
            bool encontrePosGenero = false;
            for(int j=0; j<cantidadGeneros && !encontrePosGenero; j++){
                if(arrayGeneros[j]->genero == genero){
                    int promedioPos = aux->sumaPuntuacion/aux->cant;
                    if(promedioPos  > arrayGeneros[j]->puntuacionMaxima){
                        arrayGeneros[j]->puntuacionMaxima = promedioPos;
                        arrayGeneros[j]->idMaxima = aux->id;
                    }else if(promedioPos == arrayGeneros[j]->puntuacionMaxima){
                        if(aux->id < arrayGeneros[j]->idMaxima){
                            arrayGeneros[j]->puntuacionMaxima = promedioPos;
                            arrayGeneros[j]->idMaxima = aux->id;
                        }
                    }
                    encontrePosGenero = true;
                }
            }
            aux = aux->sig;
        }
    }

    for(int i=0; i<cantidadGeneros; i++){
        cout << arrayGeneros[i]->idMaxima << endl;
    }
    
    tablaPelis->destruir();
    delete[] arrayGeneros;
}