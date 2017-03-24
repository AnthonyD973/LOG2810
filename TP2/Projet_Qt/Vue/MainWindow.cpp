#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _connecter();

    allerAuChoixLexique();
    allerAEditeur();

    _choixLexique  = new ChoixLexique(parent);
    allerAuChoixLexique();


    resize(800, 600);
    setWindowTitle("Polypad++");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_connecter() {
    connect(_editeur->getBtnRetour(), SIGNAL(clicked(bool)), SLOT(allerAuChoixLexique()));
}

void MainWindow::allerAuChoixLexique() {
    setCentralWidget(_choixLexique);
}

void MainWindow::allerAEditeur() {
    setCentralWidget(_editeur);
}
