#include "mainsudoku2.h"
#include "ui_mainsudoku2.h"
#include "sudoku.h"
#include <iostream>
using namespace std;

// biblioteca cor
#include <QPainter>
#include <QPen>

Sudoku S;


MainSudoku2::MainSudoku2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSudoku2),
    Img(131,51)
{

    ui->setupUi(this);
    /////////////// deixar inicialmente invisível os campos com as informações das jogadas
    ui->btnJogar->setVisible(false);
    ui->labelColuna->setVisible(false);
    ui->labelLinha->setVisible(false);
    ui->spinBox->setVisible(false);
    ui->labelValor->setVisible(false);
    //ui->tblSudoku->cellWidget(1,2)->setEnabled(false);

    /////////////// Tela de fundo
    QColor corDeFundo(245,245,220);
    Img.fill(corDeFundo);
    //ui->label_19->setPixmap(Img);

    /////////////// inserir as jogadas que já temos no tabulerio par o usuário
    int aux; // variável para armazenar cada valor sovbre o Sudoku.
    for(int i = 0; i <9;i++)
    {
        for(int j = 0; j <9;j++)
        {
            aux = S.getJogada(i,j);

            if(aux != 0)
            {
                QTableWidgetItem *theItem = new QTableWidgetItem();
                theItem->setData(Qt::EditRole, aux);
                ui->tblSudoku->setItem(i,j,theItem);
                //ui->tblSudoku->cellWidget(i,j)->setEnabled(false);
            }
        }
    }




}

MainSudoku2::~MainSudoku2()
{
    delete ui;
}


void MainSudoku2::on_tblSudoku_doubleClicked(const QModelIndex &index)
{
    ui->btnJogar->setVisible(true);
    ui->labelColuna->setVisible(true);
    ui->labelLinha->setVisible(true);
    ui->spinBox->setVisible(true);
    ui->labelValor->setVisible(true);
    ///////////////// Label Linha
    QString strL = "Linha: ";
    QString ind;

    //QString str = "Linha: " + index.row;
    switch(index.row()){
        case 0:
            ind = "A";
        break;
        case 1:
            ind = "B";
            break;
        case 2:
            ind = "C";
            break;
        case 3:
            ind = "D";
            break;
        case 4:
            ind = "E";
            break;
        case 5:
            ind = "F";
            break;
        case 6:
            ind = "G";
            break;
        case 7:
            ind = "H";
            break;
        case 8:
            ind = "I";
            break;
        default:
            break;
    }
    strL.insert(strL.size(),ind);
    ui->labelLinha->setText(strL);

    ///////////////// Label Coluna

    QString strC = "Coluna: ";
    ind = QString::number(index.column()+1);
    strC.insert(strC.size(),ind);
    ui->labelColuna->setText(strC);



}

void MainSudoku2::on_btnJogar_clicked()
{
    ui->btnJogar->setVisible(false);
    ui->labelColuna->setVisible(false);
    ui->labelLinha->setVisible(false);
    ui->spinBox->setVisible(false);
    ui->labelValor->setVisible(false);
    ///////////////// Obtendo Linha
    QString linha = ui->labelLinha->text();
    linha.remove(0,7);
    int indL;
    bool ok;
    //int indL = linha.toInt(&ok, 10);
    //QString strIndL = QString::number(indL);
    if(linha == "A"){
        indL = 0;
    }else if(linha == "B"){
        indL = 1;
    }else if(linha == "C"){
        indL = 2;
    }else if(linha == "D"){
        indL = 3;
    }else if(linha == "E"){
        indL = 4;
    }else if(linha == "F"){
        indL = 5;
    }else if(linha == "G"){
        indL = 6;
    }else if(linha == "H"){
        indL = 7;
    }else if(linha == "I"){
        indL = 8;
    }

   // QString strIndL = QString::number(indL);
   //     ui->labelLinha->setText(strIndL);

    ///////////////// Obtendo Coluna

    QString coluna = ui->labelColuna->text();
    coluna.remove(0,8);

    int indC = coluna.toInt(&ok, 10);
    //QString strIndC = QString::number(indC);

    //ui->labelColuna->setText(strIndC);

    /////////////////Obtendo valor

    int valor = ui->spinBox->value();

    ///////////////// Criando Jogada

    Jogada newJ(indL,indC-1,valor);


    ///////////////// Inserir a jogada no tabuleiro

    if(S.jogada_valida(newJ))
    {
        cout << "??";
        S.fazer_jogada(newJ);
        QTableWidgetItem *theItem = new QTableWidgetItem();
        theItem->setData(Qt::EditRole, valor);
        ui->tblSudoku->setItem(indL,indC-1,theItem);
    }



}

void MainSudoku2::on_actionResolver_triggered()
{
    S.resolver();

    /////////////// inserir as jogadas que já temos no tabulerio par o usuário
    int aux; // variável para armazenar cada valor sovbre o Sudoku.
    for(int i = 0; i <9;i++)
    {
        for(int j = 0; j <9;j++)
        {
            aux = S.getJogada(i,j);

            if(aux != 0)
            {
                QTableWidgetItem *theItem = new QTableWidgetItem();
                theItem->setData(Qt::EditRole, aux);
                ui->tblSudoku->setItem(i,j,theItem);
                //ui->tblSudoku->cellWidget(i,j)->setEnabled(false);
            }
        }
    }

}
