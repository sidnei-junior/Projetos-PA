#include "mainsudoku2.h"
#include "ui_mainsudoku2.h"
#include "sudoku.h"

MainSudoku2::MainSudoku2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSudoku2)
{
    ui->setupUi(this);
}

MainSudoku2::~MainSudoku2()
{
    delete ui;
}

/*void MainSudoku2::on_tblSudoku_cellChanged(int row, int column)
{    
    QString str = ui->tblSudoku->item(row, column)->text();
    //int value = (int)str;
    Jogada jog(row, column, value);
    J = jog;
}*/

void MainSudoku2::on_tblSudoku_doubleClicked(const QModelIndex &index)
{
    QString str = 'Linha: ' + index.row;
    ui->labelLinha->setText(str);

}
