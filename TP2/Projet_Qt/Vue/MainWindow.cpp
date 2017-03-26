#include "MainWindow.h"
#include "ui_mainwindow.h"

// PUBLIC:

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _choixLexique = new ChoixLexique(parent);
    _editeur      = new Editeur(parent);

    _connecter();
    _montrerChoixLexique();
    setWindowTitle("Polypad");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// PRIVATE:

void MainWindow::_connecter() {
    connect(_choixLexique, SIGNAL(initialisationTerminee()), SLOT(montrerEditeur()));
}

void MainWindow::_montrerChoixLexique() {
    QWidget* cw = centralWidget();
    cw->setParent(Q_NULLPTR); // Ne pas supprimmer cw en changeant de widget central

    resize(300, 180);
    setCentralWidget(_choixLexique);
}

void MainWindow::_montrerEditeur() {
    QWidget* cw = centralWidget();
    cw->setParent(Q_NULLPTR); // Ne pas supprimmer cw en changeant de widget central

    connect(_editeur->getBtnRetour(), SIGNAL(clicked(bool)), SLOT(montrerChoixLexique()));
    resize(800, 600);
    setCentralWidget(_editeur);
}

// PUBLIC SLOTS:

void MainWindow::montrerChoixLexique() {
    _montrerChoixLexique();
}

void MainWindow::montrerEditeur() {
    _montrerEditeur();
}

