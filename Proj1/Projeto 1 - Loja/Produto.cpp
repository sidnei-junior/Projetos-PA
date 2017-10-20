#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include "loja_heranca_incompleto.h"
void Produto::copiar(const Produto &Pr)
{
    nome = Pr.nome;
    preco = Pr.preco;
}
void Produto::limpar()
{
    nome = "";
    preco = 0;
}

istream &Produto::digitar(istream &I)
{
    cout << "Nome do produto: ";
    do
    {
        I.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(I,nome,'\n');
        //cout << "Nome = " << nome << endl;
        if(nome == "")
        {
            cerr << "Nome invalido. Redigite: ";
        }

    }while(nome == "");

    cout << "Preco do produto: ";
    double prov;
    do
    {
        I >> prov;
        preco = prov * 100;
        //cout << "preco = " << preco << endl;
        if(preco < 0)
        {
            cerr << "Preço inválido. Redigite: ";
        }
    }while(preco < 0);
    return I;

}

    ostream &Produto::imprimir(ostream &O) const
    {
        // Para Fixar quantas casas decimais deve aparecer
        O.precision(2);
        O.setf( ios::fixed,ios::floatfield );

        // Formato do Ostream de Produto
        O << '"' << nome << '"' << ";$" << preco/100.0;

        return O;
    }

istream &Produto::ler(istream &I)
{
    //cout << "Entrou em Produto::ler" << endl;
    double prov;
    I.ignore(numeric_limits<streamsize>::max(), '"');
    //cout << "ignore" << endl;
    getline(I, nome, '"');
    //getline(I, nome);
    //cout << "nome = " << nome << endl;
    I.ignore(numeric_limits<streamsize>::max(), '$');
    I >> prov;
    preco = prov *100;
    return I;
}
