#ifndef MAINSUDOKU2_H
#define MAINSUDOKU2_H

#include <QMainWindow>
#include "Sudoku.h"
#include <QLabel>
#include <Qpixmap>

namespace Ui {
class MainSudoku2;
}

class MainSudoku2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainSudoku2(QWidget *parent = 0);
    ~MainSudoku2();

private slots:

    void on_tblSudoku_doubleClicked(const QModelIndex &index);

    void on_btnJogar_clicked();

    void on_actionResolver_triggered();

private:
    Ui::MainSudoku2 *ui;
    QPixmap Img;
};

extern Sudoku S;

#endif // MAINSUDOKU2_H
