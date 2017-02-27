#include "SelectionOptimisation.h"

SelectionOptimisation::SelectionOptimisation(QWidget* parent)
    : QWidget(parent)
{

    _boutonSelectionnerFichier =    new QPushButton((QString)"Sélectionner la carte.", parent);
    _groupeTypeOptimisation    =    new QGroupBox((QString)"Type d'optimisation", parent);
    _boutonOptimiser           =    new QPushButton((QString)"OPTIMISER", parent);

    QLabel* etiquetteTypeOptimisation = new QLabel((QString)"Optimiser pour:", parent);
    QRadioButton* boutonDistMax    = new QRadioButton((QString)"Une distance maximale", parent);
    QRadioButton* boutonGainMin    = new QRadioButton((QString)"Un gain minimal", parent);
    boutonDistMax->setChecked(true);

    QVBoxLayout* dispositionTypeOptimisation = new QVBoxLayout(parent);
    dispositionTypeOptimisation->addWidget(etiquetteTypeOptimisation);
    dispositionTypeOptimisation->addWidget(boutonDistMax);
    dispositionTypeOptimisation->addWidget(boutonGainMin);

    _groupeTypeOptimisation->setLayout(dispositionTypeOptimisation);

    _dispositionHorizontale = new QVBoxLayout(parent);
    _dispositionHorizontale->addWidget(_boutonSelectionnerFichier);
    _dispositionHorizontale->addWidget(_groupeTypeOptimisation);
    _dispositionHorizontale->addWidget(_boutonOptimiser);


    setLayout(_dispositionHorizontale);
}
