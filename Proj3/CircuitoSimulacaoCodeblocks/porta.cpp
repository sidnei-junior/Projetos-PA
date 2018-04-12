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
        return 2; // retornando dois imprime uma mensagem de erro, pois as portas s� podem ser -1, 0 e 1.
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
    cout << "Digite o n�mero de portas: ";
    cin >> Nin;
    while(Nin < 1 || Nin > 4)
    {
        cout << "N�mero de entradas incorreto, REDIGITE: ";
        cin >> Nin;
    }

    for(int i = 0; i < Nin; i++)
    {
        cout << "Digite o valor da entrada " << i << " da porta: ";
        cin >> id_in[i];

        while(false) // Falta a condi��o para caso o usu�rio coloque uma entrada ou saida que n�o sejam v�lidos.
        {
            cout << "Valor inv�lido. REDIGITE: ";
            cin >> id_in[i];
        }
    }

}
virtual bool Porta::ler(istream &I);
virtual ostream &Porta::imprimir(ostream &O) const;
