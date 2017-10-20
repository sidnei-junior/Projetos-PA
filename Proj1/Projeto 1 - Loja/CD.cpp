#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include "loja_heranca_incompleto.h"

using namespace std;

CD::~CD()
{
    setNome("");
    setPreco(0);
    numero_faixa = 0;
}

istream &CD::digitar(istream &I)
{

    Produto::digitar(I);

    cout << "Numero de faixas: ";
    do
    {
        I >> numero_faixa;
        if(numero_faixa <= 0)
        {
            cerr << "Preço inválido. Redigite: ";
        }
    }while(numero_faixa <= 0);
    return I;
}
ostream &CD::imprimir(ostream &O) const
{
    O << "C: ";
    Produto::imprimir(O);
    //O << (const Produto&)*this;
    O << ';' << numero_faixa;
    return O;
}
istream &CD::ler(istream &I)
{
    //Lendo nome e preço
    Produto::ler(I);

    //Lendo o número de faixas
    I.ignore(numeric_limits<streamsize>::max(), ';');
    I >> numero_faixa;

    return I;
}
