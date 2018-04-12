#include "WhatsProg_Servidor.h"

#include <iostream>
#include <string.h>
#include <cstdio>

#include "winsocket.h"
#include "mensageiro.h"

using namespace std;

#define NUM_MAX_CONEX 30
#define TIMEOUT_WHATSPROG 30 // Tempo máximo de espera em segundos

Usuario::Usuario(string log, string sen, tcp_winsocket ss)
{
    login = log;
    senha = sen;
    s = ss;
}

void Usuario::limpar()
{
    login = "";
    senha = "";
    s.close();
}

bool buscar(const vector<Usuario> LU, const string referencia)
{
    for(int i = 0; i < LU.size(); i++)
    {
        if(LU[i].login == referencia) return true;
    }
    return false;
}

// quando retornar -1 é que não existe o usuário na lista.
int buscarIndex(vector<Usuario> LU, string referencia)
{
    for(int i = 0; i < LU.size(); i++)
    {
        if(LU[i].login == referencia) return i;
    }
    return (-1);
}
