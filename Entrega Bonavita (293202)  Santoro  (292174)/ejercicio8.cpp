#include <iostream>
#include <climits>
#include <string>
using namespace std;

bool esSolucionTrivial(int inicio, int fin){
    if(fin - inicio + 1 <= 3){
        return true;
    }else{
        return false;
    }
}

bool esPico(int inicioReal, int finReal, int izq, int centro, int der, int posIzq, int posDer){
    if(posIzq >= inicioReal && posDer <= finReal){ //tengo montaña a la izquierda y a la derecha
        if(centro > izq && centro > der){
            return true;
        }else{
            return false;
        }
    }
    else if(posIzq >= inicioReal){ // tengo solo montaña a la izquierda /estoy en el final
        if(centro > izq){
            return true;
        }else{
            return false;
        }
    }
    else if(posDer <= finReal){ // tengo solo montaña a la derecha /estoy en el principio
        if(centro > der){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

void divideAndConquer(int inicioReal, int finReal, int inicio, int fin, int*& vectorMontanas, bool*& vectorPicos){
    if(esSolucionTrivial(inicio,fin)){
        int largoSolTrivial = fin-inicio +1;
        if(largoSolTrivial == 2){
            if(inicio == inicioReal && vectorMontanas[inicio] > vectorMontanas[fin]){
                vectorPicos[inicio] = true;
            }
            if(fin == finReal && vectorMontanas[fin] > vectorMontanas[inicio]){
                
                vectorPicos[fin] = true;
            }
        }
        else if(largoSolTrivial == 3){
            if(inicio == inicioReal && vectorMontanas[inicio] > vectorMontanas[fin-1]){
                vectorPicos[inicio] = true;
            }
            if(fin == finReal && vectorMontanas[fin] > vectorMontanas[inicio+1]){
                vectorPicos[fin] = true;
            }
            if(vectorMontanas[inicio+1] > vectorMontanas[inicio] && vectorMontanas[inicio+1] > vectorMontanas[fin]){
                vectorPicos[inicio+1] = true;
            }
        }
    }else{
        int medio = inicio + (fin - inicio)/2;

        if(esPico(inicioReal, finReal, vectorMontanas[medio-1], vectorMontanas[medio], vectorMontanas[medio+1], medio-1, medio+1)){
            vectorPicos[medio] = true;
            
            divideAndConquer(inicioReal, finReal, inicio, medio-1, vectorMontanas, vectorPicos);
        }else{
            divideAndConquer(inicioReal, finReal, inicio, medio, vectorMontanas, vectorPicos);
        }

        if(esPico(inicioReal, finReal, vectorMontanas[medio], vectorMontanas[medio+1], vectorMontanas[medio+2], medio, medio+2)){
            vectorPicos[medio+1] = true;
            divideAndConquer(inicioReal, finReal, medio+2, fin, vectorMontanas, vectorPicos);
        }else{
            divideAndConquer(inicioReal, finReal, medio+1, fin, vectorMontanas, vectorPicos);
        }
    }
}

int main(){
    int largo;
    cin >> largo; 

    int* vectorMontanas = new int[largo]();
    bool* vectorPicos = new bool[largo]();
    for(int i=0; i<largo; i++){
        int leoNumero = 0;
        cin >> leoNumero;

        vectorMontanas[i] = leoNumero;
    }

    divideAndConquer(0, largo-1, 0, largo-1, vectorMontanas, vectorPicos);
    for(int i=0; i<largo; i++){
        if(vectorPicos[i] == true){
            cout << vectorMontanas[i] << endl;
        }
    }
    delete[] vectorMontanas;
    delete[] vectorPicos;
    return 0;
}