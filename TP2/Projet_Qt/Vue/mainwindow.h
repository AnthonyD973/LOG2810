#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "DispositionChoixLexique.h"
#include "DispositionEditeur.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


    QVBoxLayout*                _dispoEditeur;
    DispositionChoixLexique*    _dispoChoixLexique;

};

#endif // MAINWINDOW_H
