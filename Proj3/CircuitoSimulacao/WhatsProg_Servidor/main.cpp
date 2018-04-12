#include <iostream>
#include <string.h>
#include <cstdio>
#include <vector>
#include <algorithm>

#include "winsocket.h"
#include "mensageiro.h"
#include "dados_whatsprog.h"
#include "WhatsProg_Servidor.h"

using namespace std;

typedef vector<Usuario> vetor_Usuario;
typedef vetor_Usuario::iterator iter_Usuario;

#define NUM_MAX_CONEX 30
#define TIMEOUT_WHATSPROG 30 // Tempo máximo de espera em segundos

// O socket de conexoes
tcp_winsocket_server c;
//Lista contendo todos os usuários do servidor
vetor_Usuario LU;
// O flag que indica que o software deve encerrar todas as threads
bool fim = false;

DWORD WINAPI servidor(LPVOID lpParameter)
{
    //socket temporário: usado para adicionar no Usuário depois de testado
    tcp_winsocket t;
    // fila de sockets
    winsocket_queue f;
    //Pra que mesmo??? WINSOCKET_STATUS é o tipo inteiro???
    WINSOCKET_STATUS iResult;

    // Usuário generico para guardar algum usuário do vector quando quisermos testar
    iter_Usuario i;

    int valor;
    string login, senha, msg; //concerta a estrutura das leituras, pois ele recebe login e senha...

    while(!fim)
    {
        //limpa a fila
        f.clean();
        // testa se o socket de conexão está conectado <Não estar implica em um erro grave!!!!>
        fim = !c.accepting();
        cout << "=LOOP-INFINITO=\n";
        if(!fim)
        {
            f.include(c);
            ////////////////////////////////
            cout << "Começar a adicionar sockets na fila\n";
            for (i=LU.begin(); i!=LU.end(); i++)
            {
                cout << "for (i=LU.begin(); i!=LU.end(); i++)\n";
                if (i->getSocket().connected())
                {
                    cout << "if (i->getSocket().connected())\n";
                    f.include(i->getSocket());
                }
            }
            //////////////////////////////////

            //Fica esperando algum dos sockets da fila conter alguma informação para ler
            iResult = f.wait_read(TIMEOUT_WHATSPROG*1000);
            if (iResult==SOCKET_ERROR)
            {
                if (!fim) cerr << "Erro na espera por alguma atividade oi\n";
                fim = true;
            }
            if(!fim)
            {
                if(iResult != 0)
                {
                    // Não saiu por timeout: houve atividade em algum socket da fila
                    // Testa em qual socket houve atividade.

                    //Primeiro testar o sockets dos clientes ==>
                    //////////////////////
                    for(i=LU.begin(); i!=LU.end(); i++)
                    {
                        //Testa se está conectado && se tem atividade
                        if (i->getSocket().connected() && f.had_activity(i->getSocket()))
                        {
                            iResult = i->getSocket().read_int(valor);
                            switch(valor)
                            {
                            case CMD_LOGOUT_USER:
                                i->getSocket().shutdown();
                                break;
                            }
                            /*
                            iResult = i->getSocket().read_string(login);
                            if (iResult == SOCKET_ERROR)
                            {
                                cerr << "Destinatario invalido (" << login << ") recebido do cliente " << i->getLogin() << ". Desconectando\n";
                                i->getSocket().shutdown();
                            }
                            if (i->getSocket().connected())
                            {
                                iResult = i->getSocket().read_string(msg);
                                if (iResult == SOCKET_ERROR)
                                {
                                    cerr << "Mensagem invalida recebida do cliente " << i->login << ". Desconectando\n";
                                    i->getSocket().shutdown();
                                }
                            }
                            if (i->s.connected())
                            {
                                cout << i->login << "->" << usuario << ": " << msg << endl;
                                envie_msg(i->login,usuario,msg); // Falta essa função para enviar a mensagem
                            }
                            */
                        }
                    }
                    //////////////////////
                    // Depois, testa se houve atividade no socket de conexao
                    if (f.had_activity(c))
                    {
                        if (c.accept(t) != SOCKET_OK)
                        {
                            cerr << "Não foi possível estabelecer uma conexao\n";
                            fim = true;
                        }
                        iResult = t.read_int(valor, TIMEOUT_WHATSPROG*1000);
                        if(iResult == SOCKET_ERROR)
                        {
                            cerr <<"Erro no valor do código.\n";
                            t.write_int(CMD_LOGIN_INVALIDO);
                            t.close();
                            fim = true;
                        }
                        switch (valor)
                        {
                        case CMD_NEW_USER:
                            if (!fim)
                            {
                                // Leh o nome de usuario do cliente
                                iResult = t.read_string(login,TIMEOUT_WHATSPROG*1000);
                                if (iResult == SOCKET_ERROR)
                                {
                                    cerr << "Erro na leitura do nome de login de um cliente que se conectou.\n";
                                    t.write_int(CMD_LOGIN_INVALIDO);
                                    t.close();
                                }
                                else
                                {
                                    if (login.size()<6 || login.size()>12)
                                    {
                                        cerr << "Nome de login (" << login << ") invalido.\n";
                                        t.write_int(CMD_LOGIN_INVALIDO);
                                        t.close();
                                    }
                                    else
                                    {
                                        // Procura se jah existe um cliente conectado com o mesmo login
                                        //i = find(LU.begin(), LU.end(), login);
                                        //if (i != LU.end())
                                        if(buscar(LU,login))
                                        {
                                            cerr << "Nome de login (" << login << ") jah utilizado.\n";
                                            t.write_int(CMD_LOGIN_INVALIDO);
                                            t.close();
                                        }
                                        else
                                        {
                                            iResult = t.read_string(senha,TIMEOUT_WHATSPROG*1000);
                                            if(iResult == SOCKET_ERROR)
                                            {
                                                cerr << "Erro na leitura da senha de um cliente que se conectou.\n";
                                                t.write_int(CMD_LOGIN_INVALIDO);
                                                t.close();
                                            }
                                            else
                                            {
                                                if (senha.size()<6 || senha.size()>12)
                                                {
                                                    cerr << "Tamanho de Senha invalido.\n";
                                                    t.write_int(CMD_LOGIN_INVALIDO);
                                                    t.close();
                                                }
                                                else
                                                {
                                                    Usuario novo(login,senha,t); // criar esse construtor.
                                                    LU.push_back(novo);
                                                    // falta conectar
                                                    //t.connect(login,)
                                                    t.write_int(CMD_LOGIN_OK);
                                                    cout << "Usuário <" << login << "> cadastrado com sucesso!!!\n";
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            break;
                        case CMD_LOGIN_USER:
                            iResult = t.read_string(login, TIMEOUT_WHATSPROG*1000);
                            if (iResult == SOCKET_ERROR)
                            {
                                cerr << "Erro na leitura do login.\n";
                                t.write_int(CMD_LOGIN_INVALIDO);
                                t.close();
                            }
                            else
                            {
                                int index = buscarIndex(LU, login);
                                if(index == -1)
                                {
                                    cerr << "Usuário não cadastrado.\n";
                                    t.write_int(CMD_LOGIN_INVALIDO);
                                    t.close();
                                }
                                else
                                {

                                    //Falta testar se o usuário num já está conectado...
                                    if(LU[index].getSocket().connected())
                                    {
                                       //já está conectado
                                        t.write_int(CMD_LOGIN_INVALIDO);
                                        t.close();
                                    }
                                    else
                                    {
                                    //Conferir se a senha está okay!!!
                                        iResult = t.read_string(senha,TIMEOUT_WHATSPROG*1000);
                                        if(iResult == SOCKET_ERROR)
                                        {
                                            cerr << "Erro na leitura da senha.\n";
                                            t.write_int(CMD_LOGIN_INVALIDO);
                                            t.close();
                                        }
                                        else
                                        {
                                            // testar se a senha enviada é igual a senha
                                            if(senha != LU[index].getSenha())
                                            {
                                                //diferente
                                                cerr << "Senha incorreta.\n";
                                                t.write_int(CMD_LOGIN_INVALIDO);
                                                t.close();
                                            }
                                            else
                                            {
                                                //igual
                                                //tudo já foi testado, agora conecta o usuário!!!

                                                LU[index].setSocket(t);
                                                t.write_int(CMD_LOGIN_OK);
                                                ///////////
                                                // Falta a parte de encontrar as mensagens destinadas a esse usuário que estão no buffer
                                                ///////////
                                            }
                                        }
                                    }
                                }
                            }

                            break;
                        }

                    }
                }
            }
            else // apenas para testar.
            {
                cout << "Testando kk\n";
            }
        }
    }
    cout << "saiu do while da thread do servidor\n";

    return 0;
}

int main(void)
{
  WSADATA wsaData;
  string msg;

  // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
  // before making other Winsock functions calls
  // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
  WINSOCKET_STATUS iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0) {
    cerr << "WSAStartup failed: " << iResult << endl;
    exit(1);
  }

  if (c.listen(PORTA_TESTE) != SOCKET_OK) {
    cerr << "Não foi possível abrir o socket de controle\n";
    exit(1);
  }

  // Cria a thread que recebe e reenvia as mensagens
  HANDLE tHandle = CreateThread(NULL, 0, servidor, NULL , 0, NULL);
  if (tHandle == NULL)
  {
    cerr << "Problema na criação da thread: " << GetLastError() << endl;
    exit(1);
  }



  while (!fim)
  {
     cout << "=LOOP-1NFINITO=\n";
    do
    {
        cout << "=LOOP-2NFINITO=\n";
      cout << "Mensagem para todos os clientes [max " << TAM_MAX_MSG_STRING << " caracteres, FIM para terminar]: ";
      cin >> ws;
      getline(cin,msg);
    } while (msg.size()==0 || msg.size()>TAM_MAX_MSG_STRING);
    if (!fim) fim = (msg=="FIM");
    if (!fim)
    {
      //envie_msg("SERVIDOR","ALL",msg); // falta essa função envia_msg;
    }
  }

  // Desliga os sockets
  cout << "Encerrando o socket de conexoes\n";
  c.shutdown();
  for (iter_Usuario i=LU.begin(); i!=LU.end(); i++)
  {
    cout << "Encerrando o socket do cliente " << i->getLogin() << endl;
    i->getSocket().shutdown();
  }
  // Espera pelo fim da thread do servidor (máximo de 5 segundos)
  cout << "Aguardando o encerramento da outra thread...\n";
  WaitForSingleObject(tHandle, 5000);
  // Encerra na "força bruta" a thread do servidor caso ela não tenha terminado sozinha
  // (ou seja, a função WaitForSingleObject tenha saído por timeout)
  TerminateThread(tHandle,0);
  // Encerra o handle da thread
  CloseHandle(tHandle);
  // Enderra o socket
  c.close();
  for (iter_Usuario i=LU.begin(); i!=LU.end(); i++) i->getSocket().close();

  cout << "Tem LOOP\n";
  /* call WSACleanup when done using the Winsock dll */
  WSACleanup();
}
