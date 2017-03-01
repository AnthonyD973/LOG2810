#include "SolutionOptimisation.h"

#include "Modele/Graphe.h"

#include <string>

SolutionOptimisation::SolutionOptimisation(QWidget* parent)
    : QWidget(parent)
{
    QLabel* etiquetteTrouveeEn       = new QLabel((QString)"Trouvée en:", parent);
    _trouveeEn                       = new QLabel(parent);

    QLabel* etiquetteSolutionTrouvee = new QLabel((QString)"Solution optimale trouvée:", parent);
    _solutionTrouvee                 = new QLineEdit(parent);
    _solutionTrouvee->setReadOnly(true);

    QLabel* etiquetteDistanceTotale  = new QLabel((QString)"Distance totale:", parent);
    _distanceTotale                  = new QLabel(parent);

    QLabel* etiquetteGainTotal       = new QLabel((QString)"Gain total:", parent);
    _gainTotal                       = new QLabel(parent);


    QHBoxLayout* boiteTrouveeEn       = new QHBoxLayout();
    QVBoxLayout* boiteSolutionTrouvee = new QVBoxLayout();
    QHBoxLayout* boiteDistanceTotale  = new QHBoxLayout();
    QHBoxLayout* boiteGainTotal       = new QHBoxLayout();


    boiteTrouveeEn->addWidget(etiquetteTrouveeEn);
    boiteTrouveeEn->addWidget(_trouveeEn);

    boiteSolutionTrouvee->addWidget(etiquetteSolutionTrouvee);
    boiteSolutionTrouvee->addWidget(_solutionTrouvee);

    boiteDistanceTotale->addWidget(etiquetteDistanceTotale);
    boiteDistanceTotale->addWidget(_distanceTotale);

    boiteGainTotal->addWidget(etiquetteGainTotal);
    boiteGainTotal->addWidget(_gainTotal);


    _disposition = new QVBoxLayout(parent);
    _disposition->addLayout(boiteTrouveeEn);
    _disposition->addLayout(boiteSolutionTrouvee);
    _disposition->addLayout(boiteDistanceTotale);
    _disposition->addLayout(boiteGainTotal);


    setLayout(_disposition);
}

// =================
// =     SLOTS     =
// =================

void SolutionOptimisation::afficherResultatsOptimisation(
    const Chemin& cheminOptimal,
    const Graphe& graphe,
    std::time_t tempsPris) {

    _trouveeEn->setText(QString::number(tempsPris) + (QString)" sec");

    std::string strChemin = "";
    for (int i = 0; i < (int)cheminOptimal.sommetsVisites.size(); ++i) {
        strChemin += graphe.getSommet(cheminOptimal.sommetsVisites[i])->getNom() + ", ";
    }
    strChemin = strChemin.substr(0, strChemin.size() - 2);
    _solutionTrouvee->setText((QString)strChemin.c_str());

    _distanceTotale->setText(QString::number(cheminOptimal.distance));
    _gainTotal->setText(QString::number(cheminOptimal.gain));


}
