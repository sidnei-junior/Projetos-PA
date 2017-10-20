#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include "loja_heranca_incompleto.h"

DVD::~DVD()
{
    setNome("");
    setPreco(0);
    duracao = 0;
}

istream &DVD::digitar(istream &I)
{

    Produto::digitar(I);

    cout << "Duração do filme: ";
    do
    {
        I >> duracao;
        if(duracao <= 0)
        {
            cerr << "Duração inválido. Redigite: ";
        }
    }while(duracao <= 0);
    return I;
}
ostream &DVD::imprimir(ostream &O) const
{
    O << "D: ";
    Produto::imprimir(O);
    O << ';' << duracao;
    return O;
}
istream &DVD::ler(istream &I)
{
    Produto::ler(I);
    I.ignore(numeric_limits<streamsize>::max(), ';');
    I >> duracao;

    return I;
}

