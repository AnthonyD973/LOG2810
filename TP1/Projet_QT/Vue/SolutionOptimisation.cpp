#include "SolutionOptimisation.h"

SolutionOptimisation::SolutionOptimisation(QWidget* parent)
    : QWidget(parent)
{
    QLabel* etiquetteTrouveeEn       = new QLabel((QString)"Trouvée en:", parent);
    QLabel* valeurTrouveeEn          = new QLabel(parent);

    QLabel* etiquetteSolutionTrouvee = new QLabel((QString)"Solution optimale trouvée:", parent);
    QLabel* valeurSolutionTrouvee    = new QLabel(parent);

    QLabel* etiquetteDistanceTotale  = new QLabel((QString)"Distance totale:", parent);
    QLabel* valeurDistanceTotale     = new QLabel(parent);

    QLabel* etiquetteGainTotal       = new QLabel((QString)"Gain total:", parent);
    QLabel* valeurGainTotal          = new QLabel(parent);


    valeurTrouveeEn->hide();
    valeurSolutionTrouvee->hide();
    valeurDistanceTotale->hide();
    valeurGainTotal->hide();


    _trouveeEn       = new QHBoxLayout();
    _solutionTrouvee = new QHBoxLayout();
    _distanceTotale  = new QHBoxLayout();
    _gainTotal       = new QHBoxLayout();


    _trouveeEn->addWidget(etiquetteTrouveeEn);
    _trouveeEn->addWidget(valeurTrouveeEn);

    _solutionTrouvee->addWidget(etiquetteSolutionTrouvee);
    _solutionTrouvee->addWidget(valeurSolutionTrouvee);

    _distanceTotale->addWidget(etiquetteDistanceTotale);
    _distanceTotale->addWidget(valeurDistanceTotale);

    _gainTotal->addWidget(etiquetteGainTotal);
    _gainTotal->addWidget(valeurGainTotal);


    _dispositionHorizontale = new QVBoxLayout(parent);
    _dispositionHorizontale->addLayout(_trouveeEn);
    _dispositionHorizontale->addLayout(_solutionTrouvee);
    _dispositionHorizontale->addLayout(_distanceTotale);
    _dispositionHorizontale->addLayout(_gainTotal);


    setLayout(_dispositionHorizontale);
}
