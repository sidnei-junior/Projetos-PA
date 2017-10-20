#ifndef _LOJA_H_
#define _LOJA_H_

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

class Produto
{
private:
    string nome;
    unsigned preco;

    void copiar(const Produto &Pr);
    void limpar();

public:
    inline explicit Produto(const char *N="", unsigned P=0): nome(N), preco(P) {}
    //inline Produto(string N="", unsigned P=0): nome(N), preco(P) {}
    inline Produto(const Produto &Pr){copiar(Pr);}
    inline ~Produto(){limpar();}

    inline string getNome(){return nome;}//Realmente necessário ?????????????????
    inline void setNome(string n){nome = n;}
    inline unsigned getPreco(){return preco;}
    inline void setPreco(unsigned p){preco = p;}


    istream &digitar(istream &I);
    ostream &imprimir(ostream &O) const;
    istream &ler(istream &I);
    inline ostream &salvar(ostream &O) const {return imprimir(O);}
};

inline istream &operator>>(istream &I, Produto &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, Produto &X) {return X.imprimir(O);}

// =========================================
// Inclua aqui as classes Livro, CD e DVD
// =========================================

class Livro: public Produto
{
private:
    string autor;
    void limpar();
public:
    inline explicit Livro(const char *n="", unsigned p=0, const char *a=""): Produto(n,p), autor(a){}
    inline Livro(const Livro &L):Produto(L) {if(autor != L.autor) autor = L.autor;}

    ~Livro();
    istream &digitar(istream &I);
    ostream &imprimir(ostream &O) const;
    istream &ler(istream &I);

    inline ostream &salvar(ostream &O) const {return imprimir(O);}
};

inline istream &operator>>(istream &I, Livro &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, Livro &X) {return X.imprimir(O);}


class CD: public Produto
{
private:
    unsigned numero_faixa;

public:
    inline explicit CD(const char *n="", unsigned p=0, unsigned nf=0): Produto(n,p), numero_faixa(nf){}
    inline CD(const CD &C):Produto(C) {if(numero_faixa != C.numero_faixa) numero_faixa = C.numero_faixa;}

    ~CD();

    istream &digitar(istream &I);
    ostream &imprimir(ostream &O) const;
    istream &ler(istream &I);

    inline ostream &salvar(ostream &O) const {return imprimir(O);}
};

inline istream &operator>>(istream &I, CD &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, CD &X) {return X.salvar(O);}

class DVD: public Produto
{
    unsigned duracao;
public:
    inline explicit DVD(const char *n="", unsigned p=0, unsigned dr=0): Produto(n,p), duracao(dr){}
    inline DVD(const DVD &D):Produto(D) {if(duracao != D.duracao) duracao = D.duracao;}

    ~DVD();

    istream &digitar(istream &I);
    ostream &imprimir(ostream &O) const;
    istream &ler(istream &I);

    inline ostream &salvar(ostream &O) const {return imprimir(O);}
};

inline istream &operator>>(istream &I, DVD &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, DVD &X) {return X.salvar(O);}

//Ainda tenho de aprender a por a herança



class ListaLivro
{
private:
    Livro *x;
    unsigned N;

    void criar(unsigned t);
    void copiar(const ListaLivro &LL);
    void limpar();
public:
    // Inclua os construtores, destrutor e operadores necessarios
    //construtores
    inline ListaLivro(): x(NULL), N(0){}
    inline ListaLivro(const ListaLivro &LL){copiar(LL);}
    inline explicit ListaLivro(unsigned t){criar(t);}

    inline ~ListaLivro(){limpar();}
    inline void cleanLista(){limpar();}

    //inline void operator=(const ListaLivro &LL){limpar();copiar(LL);}

    inline unsigned getN(){return N;}

    //métodos de manipulação de dados
    void incluir(const Livro &L);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    /*/my>>>>

    ostream &imprimir(ostream &O) const;
    inline ostream &salvar()

    //my <<<<*/
    void salvar(ostream &O) const;
    //inline void operator=(const ListaLivro &LL){if(x != LL.x){limpar(); copiar(LL);}}

};

//ajeitar, o salvar não retorna nada, será que funciona assim.


// =========================================
// Inclua aqui as classes ListaCD e ListaDVD
// =========================================

class ListaCD
{
private:
    CD *x;
    unsigned N;

    void criar(unsigned t);
    void copiar(const ListaCD &LC);
    void limpar();
public:
    // Inclua os construtores, destrutor e operadores necessarios
    //construtores
    inline ListaCD(): x(NULL), N(0){}
    inline ListaCD(const ListaCD &LC){copiar(LC);}
    inline explicit ListaCD(unsigned t){criar(t);}

    inline ~ListaCD(){limpar();}
    inline void cleanLista(){limpar();}

    inline unsigned getN(){return N;}

    //métodos de manipulação de dados
    void incluir(const CD &C);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    void salvar(ostream &O) const;

    //inline void operator=(const ListaCD &LC){if(x != LC.x){limpar(); copiar(LC);}}
};



class ListaDVD
{
private:
    DVD *x;
    unsigned N;

    void criar(unsigned t);
    void copiar(const ListaDVD &LD);
    void limpar();
public:
    // Inclua os construtores, destrutor e operadores necessarios
    //construtores
    inline ListaDVD(): x(NULL), N(0){}
    inline ListaDVD(const ListaDVD &LD){copiar(LD);}
    inline explicit ListaDVD(unsigned t){criar(t);}

    inline ~ListaDVD(){limpar();}
    inline void cleanLista(){limpar();}

    inline unsigned getN(){return N;}

    //métodos de manipulação de dados
    void incluir(const DVD &D);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    void salvar(ostream &O) const;

   // inline void operator=(const ListaDVD &LD){if(x != LD.x){limpar(); copiar(LD);}}
};

//inline ostream &operator<<(ostream &O, ListaDVD &X) {return X.salvar(O);}

class Loja
{
private:
    ListaLivro LL;
    ListaCD LC;
    ListaDVD LD;

    void limpar();
public:
    inline Loja(): LL(), LC(), LD() {}
    inline ~Loja() {limpar();}

    inline void incluirLivro(const Livro &X) {LL.incluir(X);}
    inline void excluirLivro(unsigned id) {LL.excluir(id);}
    inline void incluirDVD(const DVD &X) {LD.incluir(X);}
    inline void excluirDVD(unsigned id) {LD.excluir(id);}
    inline void incluirCD(const CD &X) {LC.incluir(X);}
    inline void excluirCD(unsigned id) {LC.excluir(id);}
    void imprimir() const;
    void ler(const char* arq);
    void salvar(const char* arq) const;

};
#endif // _LOJA_H_

// Dúvidas

//É necessário criar uma variável id para a classe Produto contendo o índice onde o prduto foi armazenado?
