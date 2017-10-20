#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include "loja_heranca_incompleto.h"

using namespace std;

void ListaCD::criar(unsigned t)
{
    N = t;
    x = (N == 0 ? NULL : new CD[N]);
}
void ListaCD::copiar(const ListaCD &LC)
{
    criar(LC.N);
    for (unsigned i = 0;i < N ;i++) x[i] = LC.x[i];
}
void ListaCD::limpar()
{
    N = 0;
    delete[] x;
    x = NULL;
}


void ListaCD::incluir(const CD &C)
{
    ListaCD LC;
    LC.criar(N+1);
    for(unsigned i = 0; i < N; i++) LC.x[i] = x[i];
    LC.x[N] = C;
    //delete[] this->x;
    //copiar(LL);
    //this = LC
    limpar();
    copiar(LC);
}

void ListaCD::excluir(unsigned id)
{
    if(id < N){
        ListaCD LC;
        LC.criar(N-1);

        for(unsigned i = 0; i < id; i++)LC.x[i] = x[i];
        for(unsigned i = id; i < N-1; i++)LC.x[i] = x[i+1];
        /*limpar();
        copiar(LL);*///pode ser criado um operator= aqui;
        //this = LC;
        limpar();
        copiar(LC);
    } else {
        cerr << "Índice inválido!!!";
    }
}
void ListaCD::imprimir() const
{
    cout << "LISTACD " << N << endl;
    for(unsigned i = 0; i < N; i++) cout<<i << ") "  << x[i] << endl;
}
void ListaCD::ler(istream &I)
{
    char M;
    unsigned tam;

    CD C;

    //I.ignore(numeric_limits<streamsize>::max, ' ');
    I >> tam;
    // Preciso chamar a função criar aqui??
    for(unsigned i = 0; i < tam; i++)
    {
        I>>M;
        I.ignore(numeric_limits<streamsize>::max(),':');
        if(M == 'C')
        {
            C.ler(I);//criar C por causa da alocação
            incluir(C);
        }else{
            cerr << "Arquivo com erros estruturais!!!";
        }
    }
}
void ListaCD::salvar(ostream &O) const
{
    O << "LISTACD " << N << endl;
    for(unsigned i = 0; i < N; i++) O << x[i] << endl;
}
