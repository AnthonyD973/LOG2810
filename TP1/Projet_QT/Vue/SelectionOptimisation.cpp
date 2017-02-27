#include "SelectionOptimisation.h"

SelectionOptimisation::SelectionOptimisation(QWidget* parent)
    : QWidget(parent)
{
    _dispotitionHorizontale = new QVBoxLayout(parent);

    _boutonSelectionnerFichier =    new QPushButton((QString)"Sélectionner la carte.", parent);
    _etiquetteOptimiserPour    =    new QLabel((QString)"Optimiser pour:", parent);
    _groupeQuoiOptimiser       =    new QButtonGroup(parent);
    _groupeQuoiOptimiser->addButton(new QRadioButton((QString)"une distance maximale", parent));
    _groupeQuoiOptimiser->addButton(new QRadioButton((QString)"un gain minimal",       parent));
    _boutonOptimiser           =    new QPushButton((QString)"OPTIMISER", parent);
}
