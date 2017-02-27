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

    SelectionOptimisation* selectionOptimisation = new SelectionOptimisation();
    SolutionOptimisation*  solutionOptimisation  = new SolutionOptimisation();

    _boitePrincipale = new QVBoxLayout();
    _boitePrincipale->addWidget(selectionOptimisation);
    _boitePrincipale->addWidget(_ligneHorizontale);
    _boitePrincipale->addWidget(solutionOptimisation);

    connect(selectionOptimisation,SIGNAL(optimisationTerminee(const Chemin&, std::time_t)),
            solutionOptimisation, SLOT(afficherResultatsOptimisation(const Chemin& cheminOptimal, std::time tempsPris)));

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
