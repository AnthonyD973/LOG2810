#include "SolutionOptimisation.h"

SolutionOptimisation::SolutionOptimisation(QWidget* parent)
    : QWidget(parent)
{
    _dispotitionHorizontale = new QVBoxLayout(parent);

    _etiquetteSolutionTrouvee = new QLabel((QString)"Solution optimale trouvée:", parent);
    _etiquetteTrouveeEn       = new QLabel((QString)"Trouvée en:", parent);
    _etiquetteDistanceTotale  = new QLabel((QString)"Distance totale:", parent);
    _etiquetteGainTotal       = new QLabel((QString)"Gain total:", parent);
}
