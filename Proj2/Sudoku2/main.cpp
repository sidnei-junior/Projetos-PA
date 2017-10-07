#include "mainsudoku2.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainSudoku2 w;

    /*/>>>>>>>>>>>>>>>


    Jogada J;


      do
      {
        //S.imprimir();
        do
        {
          J.ler();
        } while(!J.resolver_jogo() && !J.fim_de_jogo() && !S.jogada_valida(J));
        if (J.resolver_jogo())
        {
          //S.imprimir(true);
          S.resolver();

        }
        else
        {
          if (!J.fim_de_jogo()) S.fazer_jogada(J);
        }
      } while(!J.fim_de_jogo() && !S.fim_de_jogo());




    //<<<<<<<<<<<<<<<*/


    w.show();

    return a.exec();
}
