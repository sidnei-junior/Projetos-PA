#ifndef MAINSUDOKU2_H
#define MAINSUDOKU2_H

#include <QMainWindow>

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
    void on_tblSudoku_cellChanged(int row, int column);

    void on_tblSudoku_doubleClicked(const QModelIndex &index);

private:
    Ui::MainSudoku2 *ui;
};

#endif // MAINSUDOKU2_H
