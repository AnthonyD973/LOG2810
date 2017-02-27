#include "Vue/MainWindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>

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
    fenetre->setObjectName((QString)"Fenêtre");
    setCentralWidget(fenetre);
}

MainWindow::~MainWindow()
{
    delete _ui;
}
