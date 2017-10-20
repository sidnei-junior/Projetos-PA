#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include "loja_heranca_incompleto.h"

using namespace std;

void ListaLivro::criar(unsigned t)
{
    N = t;
    x = (N == 0 ? NULL : new Livro[N]);
}
void ListaLivro::copiar(const ListaLivro &LL)
{
    criar(LL.N);
    for (unsigned i = 0;i < N ;i++) x[i] = LL.x[i];
}
void ListaLivro::limpar()
{
    N = 0;
    delete[] x;
    x = NULL;
}


void ListaLivro::incluir(const Livro &L)
{
    ListaLivro LL;
    LL.criar(N+1);

    for(unsigned i = 0; i < N; i++) LL.x[i] = x[i];
    LL.x[N] = L;

    limpar();
    copiar(LL);
}

void ListaLivro::excluir(unsigned id)
{
    if(id < N){
        ListaLivro LL;
        LL.criar(N-1);

        for(unsigned i = 0; i < id; i++)LL.x[i] = x[i];
        for(unsigned i = id; i < N; i++)LL.x[i] = x[i+1];

        limpar();
        copiar(LL);


    } else {
        cerr << "Índice inválido!!!";
    }
}
void ListaLivro::imprimir() const
{
    cout << "LISTALIVRO " << N << endl;
    for(unsigned i = 0; i < N; i++) cout <<i << ") " << x[i] << endl;
}
void ListaLivro::ler(istream &I)
{
    char M;
    unsigned tam;

    //Tratar o caso em que não existe lista livro
    Livro L;
    I >> tam;

    for(unsigned i = 0; i < tam; i++)
    {

        I>>M;
        I.ignore(numeric_limits<streamsize>::max(),':');

        if(M == 'L')
        {
            L.ler(I);//criar L por causa da alocação
            incluir(L);
        }else{
            cerr << "Arquivo com erros estruturais!!!";
        }
    }
}
void ListaLivro::salvar(ostream &O) const
{
    O << "LISTALIVRO " << N << endl;
    for(unsigned i = 0; i < N; i++) O << x[i] << endl;// aqui tem de chamar o salvar.
}
