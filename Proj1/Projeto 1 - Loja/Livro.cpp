#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include "loja_heranca_incompleto.h"

using namespace std;

Livro::~Livro()
{
    setNome("");
    setPreco(0);
    //nome.clear();
    //Produto::preco = 0;
    autor = "";
}

istream &Livro::digitar(istream &I)
{

    Produto::digitar(I);

    cout << "Nome do autor: ";
    do
    {
        I.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(I,autor,'\n');
        //cout << "autor = " << autor << endl;
        if(autor == "")
        {
            cerr << "Autor invalido. Redigite: ";
        }

    }while(autor == "");
    return I;
}
ostream &Livro::imprimir(ostream &O) const
{
    O << "L: ";
    Produto::imprimir(O);
    //cout << "autor = " << autor << endl;
    O << ";" << '"' << autor << '"';
    return O;
}
istream &Livro::ler(istream &I)
{
    //Lendo nome e produto
    Produto::ler(I);

    //Lendo o autor
    I.ignore(numeric_limits<streamsize>::max(), '"');
    getline(I, autor, '"');

    return I;
}
