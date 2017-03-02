#include "SelectionOptimisation.h"

#include <QDebug>

SelectionOptimisation::SelectionOptimisation(QWidget* parent)
    : QWidget(parent),
      _algo(2)
{

    _boutonSelectionnerFichier = new QPushButton((QString)"Sélectionner la carte.",  parent);
    _boiteDeroulanteSommets    = new QComboBox(parent);
    _boiteDeroulanteSommets->setDisabled(true);
    _groupeTypeOptimisation    = new QGroupBox  ((QString)"Type d'optimisation",     parent);
    _valeurCherchee            = new QLineEdit  ((QString)"Valeur cible",            parent);
    _boutonOptimiser           = new QPushButton((QString)"OPTIMISER",               parent);
    _boutonOptimiser->setDisabled(true);


    _dispoFichierSommet        = new QHBoxLayout(parent);
    _dispoFichierSommet->addWidget(_boutonSelectionnerFichier);
    _dispoFichierSommet->addWidget(_boiteDeroulanteSommets);

    QLabel* etiquetteTypeOptimisation = new QLabel((QString)"Optimiser pour:",       parent);
    QRadioButton* boutonDistMax = new QRadioButton((QString)"Une distance maximale", parent);
    QRadioButton* boutonGainMin = new QRadioButton((QString)"Un gain minimal",       parent);

    QVBoxLayout* dispositionTypeOptimisation = new QVBoxLayout(parent);
    dispositionTypeOptimisation->addWidget(etiquetteTypeOptimisation);
    dispositionTypeOptimisation->addWidget(boutonDistMax);
    dispositionTypeOptimisation->addWidget(boutonGainMin);

    _groupeTypeOptimisation->setLayout(dispositionTypeOptimisation);


    _disposition = new QVBoxLayout(parent);
    _disposition->addLayout(_dispoFichierSommet);
    _disposition->addWidget(_groupeTypeOptimisation);
    _disposition->addWidget(_valeurCherchee);
    _disposition->addWidget(_boutonOptimiser);


    setLayout(_disposition);

    connect(_boutonSelectionnerFichier, SIGNAL(clicked(bool)), SLOT(selectionFichierCarte(bool)));
    connect(_boiteDeroulanteSommets,    SIGNAL(currentIndexChanged(const QString&)), SLOT(changerIndiceSommetDepart(const QString&)));
    connect(_boutonOptimiser,           SIGNAL(clicked(bool)), SLOT(commencerOptimisation(bool)));
    connect(boutonDistMax,              SIGNAL(clicked(bool)), SLOT(selectionnerDistanceMaximale(bool)));
    connect(boutonGainMin,              SIGNAL(clicked(bool)), SLOT(selectionnerGainMinimal(bool)));
    connect(_valeurCherchee,            SIGNAL(textChanged(const QString&)), SLOT(changerValeurCible(const QString&)));
    connect(this, SIGNAL(etatBoutonOptimisationDoitEtreChange()), SLOT(changerEtatBoutonOptimisation()));
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
        _graphe = Graphe(_fichierCarte.toStdString());

        for (int i = 0; i < _graphe.getNumSommets(); ++i) {
            _boiteDeroulanteSommets->addItem((QString)_graphe.getSommet(i)->getNom().c_str());
        }
        _boiteDeroulanteSommets->setDisabled(false);
        _indiceSommetDepart = 0;

        _carteOk = true;
        emit etatBoutonOptimisationDoitEtreChange();
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
        _valeurCibleOk = true;
    }
    else {
        _valeurCible = -1;
        _valeurCibleOk = false;
    }

    emit etatBoutonOptimisationDoitEtreChange();
}

void SelectionOptimisation::changerIndiceSommetDepart(const QString& nom) {
    try {
        _indiceSommetDepart = _graphe.getIndice(nom.toStdString());
    }
    catch(const std::runtime_error& e) {
        qDebug() << e.what();
    }
}

void SelectionOptimisation::changerEtatBoutonOptimisation() {
    if (_carteOk && _typeOptimisationOk && _valeurCibleOk) {
        _boutonOptimiser->setDisabled(false);
    }
    else {
        _boutonOptimiser->setDisabled(true);
    }
}

void SelectionOptimisation::commencerOptimisation(bool) {
    qDebug() << "commencerOptimisation. Type :" << (char)_typeOptimisation << " Valeur: " << _valeurCible;

    bool estOkPourOptimiser = false;

    // Pointeur vers une méthode d'optimisation.
    typedef Chemin (Algo::*Optimisation_t) (int, const Graphe&, int) const;
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
        std::time_t tempsDebut = std::time(nullptr);

        qDebug() << "Optimisation...";
        Chemin cheminOptimal = (_algo.*methodeOptimiser)(_valeurCible, _graphe, _indiceSommetDepart);
        qDebug() << "Optimisation terminée.";

        emit optimisationTerminee(cheminOptimal, _graphe, std::time(nullptr) - tempsDebut);
    }
}

void SelectionOptimisation::selectionnerDistanceMaximale(bool) {
    _typeOptimisation = _TypeOptimisation::_DISTANCE_MAX;
    _typeOptimisationOk = true;
    emit etatBoutonOptimisationDoitEtreChange();
}

void SelectionOptimisation::selectionnerGainMinimal(bool) {
    _typeOptimisation = _TypeOptimisation::_GAIN_MIN;
    _typeOptimisationOk = true;
    emit etatBoutonOptimisationDoitEtreChange();
}
