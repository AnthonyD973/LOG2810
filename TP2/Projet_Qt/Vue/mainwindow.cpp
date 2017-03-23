#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _dispoChoixLexique  = new DispositionChoixLexique(parent);

    _dispoEditeur       = new QVBoxLayout (parent);

}

MainWindow::~MainWindow()
{
    delete ui;
}
