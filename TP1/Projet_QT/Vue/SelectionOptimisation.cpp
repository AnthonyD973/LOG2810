#include "SelectionOptimisation.h"

#include <QDebug>

SelectionOptimisation::SelectionOptimisation(QWidget* parent)
    : QWidget(parent),
      _algo(2)
{

    _boutonSelectionnerFichier = new QPushButton((QString)"Sélectionner la carte.",  parent);
    _groupeTypeOptimisation    = new QGroupBox  ((QString)"Type d'optimisation",     parent);
    _valeurCherchee            = new QLineEdit  ((QString)"Valeur cible",            parent);
    _boutonOptimiser           = new QPushButton((QString)"OPTIMISER",               parent);


    QLabel* etiquetteTypeOptimisation = new QLabel((QString)"Optimiser pour:",       parent);
    QRadioButton* boutonDistMax = new QRadioButton((QString)"Une distance maximale", parent);
    QRadioButton* boutonGainMin = new QRadioButton((QString)"Un gain minimal",       parent);

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

    connect(_boutonSelectionnerFichier, SIGNAL(clicked(bool)), SLOT(selectionFichierCarte(bool)));
    connect(_boutonOptimiser,           SIGNAL(clicked(bool)), SLOT(commencerOptimisation(bool)));
    connect(boutonDistMax,              SIGNAL(clicked(bool)), SLOT(selectionnerDistanceMaximale(bool)));
    connect(boutonGainMin,              SIGNAL(clicked(bool)), SLOT(selectionnerGainMinimal(bool)));
    connect(_valeurCherchee,            SIGNAL(textChanged(const QString&)), SLOT(changerValeurCible(const QString&)));
}

// =================
// =     SLOTS     =
// =================

void SelectionOptimisation::selectionFichierCarte(bool) {
    QString cheminFichier = QFileDialog::getOpenFileName(
                this,
                (QString)"Choisir Carte",
                QDir::currentPath() + "/..",
                "Fichiers texte (*.txt)");

    if (!cheminFichier.isNull()) {
        _fichierCarte = cheminFichier;
    }
}

void SelectionOptimisation::changerValeurCible(const QString &valeur) {
    bool entreeEstProbablementOk;

    if (valeur.size() != 0) {
        bool estUnChiffre = (valeur[0] >= (QChar)'0') && (valeur[0] <= (QChar)'9');
        if (estUnChiffre) {
            entreeEstProbablementOk = true;
        }
        else {
            entreeEstProbablementOk = false;
        }
    }
    else {
        entreeEstProbablementOk = false;
    }

    if (entreeEstProbablementOk) {
        _valeurCible = valeur.toInt(Q_NULLPTR, 0);
    }
    else {
        _valeurCible = -1;
    }
}

void SelectionOptimisation::commencerOptimisation(bool) {
    qDebug() << "commencerOptimisation. Type :" << (char)_typeOptimisation << " Valeur: " << _valeurCible;

    bool estOkPourOptimiser = false;

    typedef Chemin (Algo::*Optimisation_t) (int, const Graphe&, int) const; // Pointeur vers une méthode d'optimisation.
    Optimisation_t methodeOptimiser;

    if (!_fichierCarte.isNull()) {
        if (_valeurCible >= 0) {
            switch(_typeOptimisation) {
            case _DISTANCE_MAX: methodeOptimiser = &Algo::meilleurCheminPourDistanceDe; estOkPourOptimiser = true; break;
            case _GAIN_MIN:     methodeOptimiser = &Algo::meilleurCheminPourGainDe;     estOkPourOptimiser = true; break;
            default: qDebug() << "Type d'optimisation non spécifié."; break;
            }
        }
        else {
            qDebug() << "Valeur cible saisie non valide.";
        }
    }
    else {
        qDebug() << "Aucun fichier d'entrée spécifié.";
    }

    if (estOkPourOptimiser) {
        Graphe graphe(_fichierCarte.toStdString());

        std::time_t tempsDebut = std::time(nullptr);

        Chemin cheminOptimal = (_algo.*methodeOptimiser)(_valeurCible, graphe, 0);

        qDebug() << "Optimisation...";
        emit optimisationTerminee(cheminOptimal, graphe, std::time(nullptr) - tempsDebut);
        qDebug() << "Optimisation terminée.";
    }
}

void SelectionOptimisation::selectionnerDistanceMaximale(bool) {
    _typeOptimisation = _TypeOptimisation::_DISTANCE_MAX;
}

void SelectionOptimisation::selectionnerGainMinimal(bool) {
    _typeOptimisation = _TypeOptimisation::_GAIN_MIN;
}
