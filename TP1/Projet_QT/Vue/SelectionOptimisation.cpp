#include "SelectionOptimisation.h"

SelectionOptimisation::SelectionOptimisation(QWidget* parent)
    : QWidget(parent)
{

    _boutonSelectionnerFichier =    new QPushButton((QString)"Sélectionner la carte.", parent);
    _groupeOptimiserPour       =    new QGroupBox((QString)"Type d'optimisation", parent);
    _boutonOptimiser           =    new QPushButton((QString)"OPTIMISER", parent);

    QLabel* etiquetteOptimiserPour = new QLabel((QString)"Optimiser pour:", parent);
    QRadioButton* boutonDistMax    = new QRadioButton((QString)"Une distance maximale", parent);
    QRadioButton* boutonGainMin    = new QRadioButton((QString)"Un gain minimal", parent);
    boutonDistMax->setChecked(true);

    QVBoxLayout* dispositionOptimiserPour = new QVBoxLayout(parent);
    dispositionOptimiserPour->addWidget(etiquetteOptimiserPour);
    dispositionOptimiserPour->addWidget(boutonDistMax);
    dispositionOptimiserPour->addWidget(boutonGainMin);

    _groupeOptimiserPour->setLayout(dispositionOptimiserPour);

    _dispositionHorizontale = new QVBoxLayout(parent);
    _dispositionHorizontale->addWidget(_boutonSelectionnerFichier);
    _dispositionHorizontale->addWidget(_groupeOptimiserPour);
    _dispositionHorizontale->addWidget(_boutonOptimiser);

    _dispositionHorizontale = new QVBoxLayout(parent);
    setLayout(_dispositionHorizontale);
}
