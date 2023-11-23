#include <iostream>
#include <string>
#include <cassert>
#include <limits.h>
#include <math.h>
#include "Ejercicio7/minHeap.cpp"
using namespace std;



int main()
{
    string numero;
    cin >> numero;
    int largo = numero.length();

    MinHeap* heap = new MinHeap(largo);

    for(int i=0; i<largo; i++){
        heap->insertar(numero[i]);
    }

    

    bool esPar = largo%2 == 0;

    if(esPar){
        string primerNum = "";
        string segundoNum = "";
        for(int i=largo/2 ; i>=1; i--){
            primerNum += heap->tope();
            segundoNum += heap->tope();
        } 
        int suma = stoi(primerNum) + stoi(segundoNum);
        cout << suma;
    }else{
        string primerNum = "";
        string segundoNum = "";
        segundoNum+= heap->tope();
        
        for(int i=largo/2 ; i>=1; i--){
            primerNum += heap->tope();
            segundoNum += heap->tope();
        }   
        

        int suma = stoi(primerNum) + stoi(segundoNum);

        cout << suma;
    }
    heap->destruir();
    return 0;
};