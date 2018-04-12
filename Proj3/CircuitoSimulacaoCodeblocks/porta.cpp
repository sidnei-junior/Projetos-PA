#include "circuito.h"

Porta::Porta(unsigned NI=2) //construtor default
{
    Nin = NI;

    for(int i = 0; i < NI; i++)
    {
        id_in[i] = -1;
    }

    saida = -1;
}

Porta::Porta(const Porta &p)
{
    Nin = p.Nin

    for(int i = 0; i < Nin; i++)
    {
        id_in[i] = p.id_in[i];
    }

    saida = p.saida;
}


int Porta::getId_in(unsigned i) const
{

    if(i < 4 && i >=0)
    {
        return id_in[i];
    }else{
        return 2; // retornando dois imprime uma mensagem de erro, pois as portas só podem ser -1, 0 e 1.
    }
}

bool Porta::setId_in(unsigned i, int N)
{
    if(i < 4 && i >=0)
    {
        id_in[i] = N;
        return true; //
    }else{
        return false;
    }
}
void Porta::digitar()
{
    cout << "Digite o número de portas: ";
    cin >> Nin;
    while(Nin < 1 || Nin > 4)
    {
        cout << "Número de entradas incorreto, REDIGITE: ";
        cin >> Nin;
    }

    for(int i = 0; i < Nin; i++)
    {
        cout << "Digite o valor da entrada " << i << " da porta: ";
        cin >> id_in[i];

        while(false) // Falta a condição para caso o usuário coloque uma entrada ou saida que não sejam válidos.
        {
            cout << "Valor inválido. REDIGITE: ";
            cin >> id_in[i];
        }
    }

}
virtual bool Porta::ler(istream &I);
virtual ostream &Porta::imprimir(ostream &O) const;
