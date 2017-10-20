#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>

#include "loja_heranca_incompleto.h"

using namespace std;

void Loja::limpar()
{
    LL.cleanLista();
    LC.cleanLista();
    LD.cleanLista();
}

void Loja::imprimir() const
{
    cout << endl << "===============================" << endl << endl;
    LL.imprimir();
    LC.imprimir();
    LD.imprimir();
    cout << endl << "===============================" << endl << endl;
}

void Loja::ler(const char* arq)
{
    ifstream date_arq(arq);
    string ListaDe;
    date_arq >> ListaDe;

    //Testando se não há nada salvo já;
    if(LL.getN() != 0 || LC.getN() != 0 || LD.getN() != 0)
    {
        char r;
        cout << "Alteraçoes realizadas serao perdidas, continuar?<s/n> ";
        cin >> r;
        if(r == 's')
        {
            limpar();
            if(date_arq.is_open())
            {
                if(ListaDe == "LISTALIVRO")
                {
                    LL.ler(date_arq);
                    date_arq.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(date_arq,ListaDe,' ');
                }
                if(ListaDe == "LISTACD")
                {
                    LC.ler(date_arq);
                    date_arq.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(date_arq,ListaDe,' ');
                }
                if(ListaDe == "LISTADVD")
                {
                    LD.ler(date_arq);
                }
            }
        }
        if(true)// o certo era que aqui dentro tivesse um testepara saber se abriu o arquivo certo
        {
            cout << endl << "===============================" << endl << endl;
            cout << "Os dados da loja foram upados" << endl;
            cout << endl << "===============================" << endl << endl;
        }
    } else {
    //Leitura para quando estiver com arquivo vazio.
        if(date_arq.is_open())
        {
            if(ListaDe == "LISTALIVRO")
            {
                LL.ler(date_arq);
                date_arq.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(date_arq,ListaDe,' ');
            }
            if(ListaDe == "LISTACD")
            {
                LC.ler(date_arq);
                date_arq.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(date_arq,ListaDe,' ');
            }
            if(ListaDe == "LISTADVD")
            {
                LD.ler(date_arq);
            }
        }
    //==================
    if(true)// o certo era que aqui dentro tivesse um testepara saber se abriu o arquivo certo
        {
            cout << endl << "===============================" << endl << endl;
            cout << "Os dados da loja foram upados" << endl;
            cout << endl << "===============================" << endl << endl;
        }
    }


    date_arq.close();
}

void Loja::salvar(const char* arq) const
{
    ofstream date_arq(arq);//rever as funlçoes out e app?????????????????
    LL.salvar(date_arq);
    LC.salvar(date_arq);
    LD.salvar(date_arq);
    date_arq.close();
}
