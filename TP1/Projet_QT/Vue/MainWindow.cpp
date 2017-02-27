#include "Vue/MainWindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    QFrame* _ligneHorizontale = new QFrame(this);
    _ligneHorizontale->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    _ligneHorizontale->setLineWidth(2);

    _boitePrincipale = new QVBoxLayout();
    _boitePrincipale->addWidget(new SelectionOptimisation());
    _boitePrincipale->addWidget(_ligneHorizontale);
    _boitePrincipale->addWidget(new SolutionOptimisation());

    QWidget* fenetre = new QWidget(this);
    fenetre->setLayout(_boitePrincipale);
    setCentralWidget(fenetre);


    setWindowTitle((QString)"L'optimisateur Pokémon Go!");

    fenetre->show();
}

MainWindow::~MainWindow()
{
    delete _ui;
}
