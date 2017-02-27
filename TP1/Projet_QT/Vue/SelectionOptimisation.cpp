#include "SelectionOptimisation.h"

SelectionOptimisation::SelectionOptimisation(QWidget* parent)
    : QWidget(parent)
{

    _boutonSelectionnerFichier = new QPushButton((QString)"Sélectionner la carte.",  parent);
    _groupeTypeOptimisation    = new QGroupBox  ((QString)"Type d'optimisation",     parent);
    _valeurCherchee            = new QLineEdit  ((QString)"Valeur distance/gain",    parent);
    _boutonOptimiser           = new QPushButton((QString)"OPTIMISER",               parent);


    QLabel* etiquetteTypeOptimisation = new QLabel((QString)"Optimiser pour:",       parent);
    QRadioButton* boutonDistMax = new QRadioButton((QString)"Une distance maximale", parent);
    QRadioButton* boutonGainMin = new QRadioButton((QString)"Un gain minimal",       parent);
    boutonDistMax->setChecked(true);

    QVBoxLayout* dispositionTypeOptimisation = new QVBoxLayout(parent);
    dispositionTypeOptimisation->addWidget(etiquetteTypeOptimisation);
    dispositionTypeOptimisation->addWidget(boutonDistMax);
    dispositionTypeOptimisation->addWidget(boutonGainMin);

    _groupeTypeOptimisation->setLayout(dispositionTypeOptimisation);


    _disposition = new QVBoxLayout(parent);
    _disposition->addWidget(_boutonSelectionnerFichier);
    _disposition->addWidget(_groupeTypeOptimisation);
    _disposition->addWidget(_valeurCherchee);
    _disposition->addWidget(_boutonOptimiser);


    setLayout(_disposition);
}
