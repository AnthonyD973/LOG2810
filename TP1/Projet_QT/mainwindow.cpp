#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _boutonSelectionnerFichier = new QPushButton((QString)"Sélectionner la carte.", this);

    _etiquetteOptimiserPour = new QLabel((QString)"Optimiser pour:", this);

    _groupeQuoiOptimiser = new QButtonGroup(this);
    _groupeQuoiOptimiser->addButton(new QRadioButton((QString)"une distance maximale", this));
    _groupeQuoiOptimiser->addButton(new QRadioButton((QString)"un gain minimal",       this));

    _boutonOptimiser = new QPushButton((QString)"OPTIMISER", this);

    _etiquetteSolutionOptimaleTrouvee = new QLabel((QString)"Solution optimale trouvée:", this);

    //...;

    _etiquetteTrouveeEn = new QLabel((QString)"Trouvée en:", this);

    _etiquetteDistanceTotale = new QLabel((QString)"Distance totale:", this);

    _etiquetteGainTotal = new QLabel((QString)"Gain total:", this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
