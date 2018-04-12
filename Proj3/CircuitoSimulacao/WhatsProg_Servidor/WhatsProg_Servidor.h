#define PORTA_TESTE "23456"
#include "dados_whatsprog.h"
#include <list>
#include <vector>
#include "winsocket.h"

class Usuario
{
private:
    string login;
    string senha;
    list<Mensagem> LM;//organizar por remetente
    tcp_winsocket s;
    void limpar();
public:
    Usuario(string log, string sen, tcp_winsocket ss);
    inline ~Usuario(){limpar();}

    inline tcp_winsocket getSocket(){return s;}
    inline string getLogin(){return login;}
    inline string getSenha(){return senha;}

    void setSocket(tcp_winsocket t){s = t;}

    friend bool buscar(vector<Usuario> LU, string referencia);
    friend int buscarIndex(vector<Usuario> LU, string referencia);


};



/* por enquanto não estou usando
class Servidor
{
private:
    vector<Usuario> LU;// fazer essa estrutura direto no main do servidor???
public:

};*/
