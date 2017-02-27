#include "SolutionOptimisation.h"

SolutionOptimisation::SolutionOptimisation(QWidget* parent)
    : QWidget(parent)
{
    QLabel* etiquetteTrouveeEn       = new QLabel((QString)"Trouvée en:", parent);
    QLabel* valeurTrouveeEn          = new QLabel(parent);

    QLabel* etiquetteSolutionTrouvee = new QLabel((QString)"Solution optimale trouvée:", parent);
    QLineEdit* valeurSolutionTrouvee = new QLineEdit(parent);
    valeurSolutionTrouvee->setReadOnly(true);

    QLabel* etiquetteDistanceTotale  = new QLabel((QString)"Distance totale:", parent);
    QLabel* valeurDistanceTotale     = new QLabel(parent);

    QLabel* etiquetteGainTotal       = new QLabel((QString)"Gain total:", parent);
    QLabel* valeurGainTotal          = new QLabel(parent);


    valeurTrouveeEn->hide();
    valeurDistanceTotale->hide();
    valeurGainTotal->hide();


    _trouveeEn       = new QHBoxLayout();
    _solutionTrouvee = new QVBoxLayout();
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


    _disposition = new QVBoxLayout(parent);
    _disposition->addLayout(_trouveeEn);
    _disposition->addLayout(_solutionTrouvee);
    _disposition->addLayout(_distanceTotale);
    _disposition->addLayout(_gainTotal);


    setLayout(_disposition);
}
