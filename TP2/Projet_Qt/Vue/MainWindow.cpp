#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _choixLexique  = new ChoixLexique(parent);
    _editeur       = new Editeur     (parent);

    setCentralWidget(_choixLexique);
    setFixedSize(800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
