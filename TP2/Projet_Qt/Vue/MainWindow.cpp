#include "MainWindow.h"
#include "ui_mainwindow.h"

// PUBLIC:

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();

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
    connect(_editeur,      SIGNAL(retourDemande()), SLOT(montrerChoixLexique()));
}

void MainWindow::_montrerChoixLexique() {
    centralWidget()->setParent(Q_NULLPTR); // Ne pas supprimmer cw en changeant de widget central
    setCentralWidget(_choixLexique);
    resize(300, 150);
}

void MainWindow::_montrerEditeur() {
    centralWidget()->setParent(Q_NULLPTR); // Ne pas supprimmer cw en changeant de widget central
    _editeur->activer();
    setCentralWidget(_editeur);
    resize(800, 600);
}

// PUBLIC SLOTS:

void MainWindow::montrerChoixLexique() {
    _montrerChoixLexique();
}

void MainWindow::montrerEditeur() {
    _montrerEditeur();
}

