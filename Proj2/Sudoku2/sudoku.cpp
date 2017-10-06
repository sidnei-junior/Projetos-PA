#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <stack> // quando incluo sudoku.h também incluo a chamada a <stack> que está lá?
#include "sudoku.h"

using namespace std;

// Construtor (por default, cria Jogada que termina o jogo)
Jogada::Jogada(int I, int J, int V)
{
  if (I<0 || I>8) I=-1;
  if (J<0 || J>8) J=-1;
  if (V<0 || V>9) V=-1;
  i = I;
  j = J;
  v = V;
}

// Leh uma jogada do teclado
void Jogada::ler()
{
  char tecla;


  //cout << "Linha [A-I; R=Resolver; S=Sair]? ";
  do
  {
    tecla = toupper(getch());
  } while ((tecla<'A' || tecla>'I') && tecla!='R' && tecla!='S');
  cout << tecla << endl;
  if (tecla=='R')
  {
    // Resolver o problema
    i = j = v = 10;
    return;
  }
  if (tecla=='S')
  {
    // Sair do programa
    i = j = v = -1;
    return;
  }
  i = tecla-'A';  // De 0 a 8

    //cout << tecla;



  cout << "Coluna [1-9]? ";
  do
  {
    tecla = toupper(getch());
  } while (tecla<'1' || tecla>'9');
  cout << tecla << endl;
  j = tecla-'1';  // De 0 a 8
  cout << tecla;


  cout << "Valor [1-9; 0=apagar]? ";
  do
  {
    tecla = toupper(getch());
    //aceitar_valor_zero_para_apagar();
  } while (tecla<'0' || tecla>'9');
  cout << tecla << endl;
  v = tecla-'0';  // De 0 a 9

  // Restaura as etiquetas normais
  cout << char('A'+i);
  cout << j+1;

}

// Testa se a jogada indica que o uruario quer resolver o jogo automaticamente
bool Jogada::resolver_jogo() const
{
  return (i>8 || j>8 || v>9);
}

// Testa se a jogada indica que o uruario quer encerrar o jogo
bool Jogada::fim_de_jogo() const
{
  return (i<0 || j<0 || v<0);
}

// Cria um tabuleiro com o conteudo do arquivo nome_arq
// Caso nao consiga ler do arquivo, cria tabuleiro vazip
Sudoku::Sudoku(const char *nome_arq)
{
  for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
  {
    x[i][j] = 0;
  }
  // Le o tabuleiro inicial de arquivo
  ifstream arq(nome_arq);
  if (!arq.is_open()) return;

  string prov;
  int valor;

  arq >> prov;
  if (prov != "SUDOKU") return;
  for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
  {
    arq >> valor;
    if (valor != 0)
    {
      Jogada J(i,j,valor);
      if (jogada_valida(J)) x[i][j] = valor;
    }
  }
  arq.close();
}



// Testa se a jogada J eh possivel para o tabuleiro
bool Sudoku::jogada_valida(Jogada J) const
{
  unsigned i,j;
  // Testar a jogada
  if (J.i<0 || J.i>8) return false;
  if (J.j<0 || J.j>8) return false;
  if (J.v<0 || J.v>9) return false;

  // Testar se a casa nao estah vazia
  if (x[J.i][J.j] != 0)
  {
    // Soh pode apagar
    return (J.v == 0);
  }

  // Se chegou aqui, eh pq a casa estah vazia.
  // Portanto, nao pode apagar
  if (J.v == 0) return false;

  // Testar a linha
  for (i=0; i<9; i++)
  {
    if (x[i][J.j] == J.v) return false;
  }
  // Testar a coluna
  for (j=0; j<9; j++)
  {
    if (x[J.i][j] == J.v) return false;
  }
  // Testar o bloco
  unsigned iIni = 3*(J.i/3);
  unsigned jIni = 3*(J.j/3);
  for (i=0; i<3; i++) for (j=0; j<3; j++)
  {
    if (x[iIni+i][jIni+j] == J.v) return false;
  }
  return true;
}

// Testa se o tabuleiro estah completo (fim de jogo)
bool Sudoku::fim_de_jogo() const
{
  for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
  {
    if (x[i][j] == 0) return false;
  }
  return true;
}

// Retorna o numero de casas vazias no tabuleiro
unsigned Sudoku::num_casas_vazias() const
{
  unsigned N(0);
  for (unsigned i=0; i<9; i++) for (unsigned j=0; j<9; j++)
  {
    if (x[i][j] == 0) N++;
  }
  return N;
}

// Determina automaticamente a solucao do tabuleiro (preenche as casas vazias)
void Sudoku::resolver(void)
{
  //cout << "O resolvedor automatico ainda nao estah pronto!";

// escrito por Sidnei >>>>

    int num_testados = 0;
    stack <Sudoku> Aberto;
    bool encontrou_solucao  = false;

    // Aberto tem de receber o valor do tabuleiro que está chamando a função resolver
    // Tem de ver a forma certa de fazer isso (parece está certo!!!)
    Aberto.push(*this);
    //Fazer um do while que ficara fazendo a repetição
    do
    {
        Sudoku tab = Aberto.top();
        Aberto.pop();
        num_testados++;

        if(tab.fim_de_jogo())
        {
            encontrou_solucao = true;
        }
        else
        {
            Jogada J;
            //código de busca de casa vazia
            bool achou = false;
            for(int i = 0; i < 9;  i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    if(tab.x[i][j] == 0){J.i = i;J.j = j; achou = true; break;}
                }
                if(achou)break;
            }

            for(int i = 1; i <= 9; i++)
            {
                J.v = i;
                Sudoku suc = tab;
                if(tab.jogada_valida(J))
                {
                    suc.fazer_jogada(J);
                    //cout << J.v << endl;
                    Aberto.push(suc);
                }
            }
        }
        if(num_testados % 250 == 0)
        {
            cout << "1" << endl;
            //tab.imprimir();
            cout << "\n" << num_testados << "       " << Aberto.size() << endl;
        }
        if(!(!encontrou_solucao && !Aberto.empty()))
        {
            cout << "2" << endl;
            //tab.imprimir();
            cout << "\n" << num_testados << "       " << Aberto.size() << endl;
            *this = tab;
        }
        //espera_tecla();
    }while(!encontrou_solucao && !Aberto.empty());//Conferir se alguma forma melhor de fazer esse teste // Conferido!!!!

// escrito por Sidnei <<<<
}
