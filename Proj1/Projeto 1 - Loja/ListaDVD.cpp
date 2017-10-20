#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include "loja_heranca_incompleto.h"

using namespace std;

void ListaDVD::criar(unsigned t)
{
    N = t;
    x = (N == 0 ? NULL : new DVD[N]);
}
void ListaDVD::copiar(const ListaDVD &LD)
{
    criar(LD.N);
    for (unsigned i = 0;i < N ;i++) x[i] = LD.x[i];
}
void ListaDVD::limpar()
{
    N = 0;
    delete[] x;
    x = NULL;
}


void ListaDVD::incluir(const DVD &D)
{
    ListaDVD LD;
    LD.criar(N+1);
    for(unsigned i = 0; i < N; i++) LD.x[i] = x[i];
    LD.x[N] = D;
    //delete[] this->x;
    //copiar(LL);
    //this = LD;
    limpar();
    copiar(LD);
}

void ListaDVD::excluir(unsigned id)
{
    if(id < N){
        ListaDVD LD;
        LD.criar(N-1);

        for(unsigned i = 0; i < id; i++)LD.x[i] = x[i];
        for(unsigned i = id; i < N; i++)LD.x[i] = x[i+1];
        /*limpar();
        copiar(LL);*///pode ser criado um operator= aqui;
        //this = LD;
        limpar();
        copiar(LD);
    } else {
        cerr << "Índice inválido!!!";
    }
}
void ListaDVD::imprimir() const
{
    cout << "LISTADVD " << N << endl;
    for(unsigned i = 0; i < N; i++) cout <<i << ") " << x[i] << endl;
}
void ListaDVD::ler(istream &I)
{
    char M;
    unsigned tam;
    DVD D;


    I >> tam;
    // Preciso chamar a função criar aqui??
    for(unsigned i = 0; i < tam; i++)
    {

        I>>M;
        I.ignore(numeric_limits<streamsize>::max(),':');
        if(M == 'D')
        {
            D.ler(I);//criar L por causa da alocação
            incluir(D);

        }else{
            cerr << "Arquivo com erros estruturais!!!";
        }
    }
}
void ListaDVD::salvar(ostream &O) const
{
    O << "LISTADVD " << N << endl;
    for(unsigned i = 0; i < N; i++) O << x[i] << endl;
}

