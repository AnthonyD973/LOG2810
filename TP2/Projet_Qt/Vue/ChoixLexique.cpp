#include <QDebug>

#include "ChoixLexique.h"
#include "Modele/Correction.h"


// PUBLIC:

ChoixLexique::ChoixLexique(QWidget* parent)
    : QWidget(parent)
{
    _btnChoixLexique = new QPushButton("Choisir le &lexique", parent);
    _btnStart        = new QPushButton("&START!!", parent);
    _btnStart->setDisabled(true);
    _barreEtat       = new QProgressBar(parent);
    _barreEtat->hide();
    _etqQuelEtat     = new QLabel("", parent);

    _dispoBarreEtat  = new QVBoxLayout(parent);
    _dispoBarreEtat->addWidget(_barreEtat);
    _dispoBarreEtat->addWidget(_etqQuelEtat);

    _disposition     = new QVBoxLayout(parent);

    _disposition->addWidget(_btnChoixLexique);
    _disposition->addWidget(_btnStart);
    _disposition->addLayout(_dispoBarreEtat);

    setLayout(_disposition);

    _connecter();
}


// PRIVATE:

void ChoixLexique::_connecter() const {
    connect(_btnChoixLexique, SIGNAL(clicked(bool)), SLOT(_choisirLexique()));
    connect(_btnStart,        SIGNAL(clicked(bool)), SLOT(_initialiserLexique()));
}

void ChoixLexique::_connecterAuCorrecteur() const {
    connect(Correction::getInstance(), SIGNAL(progressionConstruction(int)), SLOT(_changerProgressionBarreEtat(int)));
    connect(Correction::getInstance(), SIGNAL(progressionMinimisation(int)), SLOT(_changerProgressionBarreEtat(int)));
    connect(Correction::getInstance(), SIGNAL(constructionTerminee()),       SLOT(_demarrerSimplificationLexique()));
    connect(Correction::getInstance(), SIGNAL(minimisationTerminee()),       SLOT(_terminerInitialisation()));
}

void ChoixLexique::_deconnecterDuCorrecteur() const {
    if (Correction::getInstance() != nullptr) {
        disconnect(Correction::getInstance(), SIGNAL(progressionConstruction(int)), this, SLOT(_changerProgressionBarreEtat(int)));
        disconnect(Correction::getInstance(), SIGNAL(progressionMinimisation(int)), this, SLOT(_changerProgressionBarreEtat(int)));
        disconnect(Correction::getInstance(), SIGNAL(constructionTerminee()),       this, SLOT(_demarrerSimplificationLexique()));
        disconnect(Correction::getInstance(), SIGNAL(minimisationTerminee()),       this, SLOT(_terminerInitialisation()));
    }
}

void ChoixLexique::_testerBarreEtat() {
    qDebug() << "_testerBarreEtat";

    _barreEtat->show();
    _demarrerCreationLexique();
    for (int i = 1; i <= 99; ++i) {
        _changerProgressionBarreEtat(i);
        system("sleep 0.02");
    }
    system("sleep 1"); // haha, le fameux blocage à 99%
    _changerProgressionBarreEtat(100);

    system("sleep 1");

    _demarrerSimplificationLexique();
    for (int i = 1; i <= 99; ++i) {
        _changerProgressionBarreEtat(i);
        system("sleep 0.02");
    }
    system("sleep 1"); // :-)
    _changerProgressionBarreEtat(100);
    _terminerInitialisation();
}


// PRIVATE SLOTS:

void ChoixLexique::_choisirLexique() {
    QString cheminLexique = QFileDialog::getOpenFileName(this, "Choisir le lexique", QDir::currentPath() + "/..", "Fichiers texte (*.txt)");

    if (!cheminLexique.isNull() && cheminLexique != _fichierLexique) {
        _fichierLexique = cheminLexique;
        _lexiqueConstruit = false;
        _btnStart->setDisabled(false);
    }

    qDebug() << "choisirLexique" << _fichierLexique;
}

void ChoixLexique::_initialiserLexique() {
    qDebug() << "initialiserLexique";

    if (!_lexiqueConstruit) {
        _deconnecterDuCorrecteur();
        Correction::creerCorrection();
        _connecterAuCorrecteur();
        Correction::construireCorrection(_fichierLexique.toStdString());
    }
    else {
        _etqQuelEtat->setText("LEXIQUE DÉJÀ CONSTRUIT");
        _terminerInitialisation();
    }
}

void ChoixLexique::_changerProgressionBarreEtat(int progression) {
    qDebug() << "changerProgressionBarreEtat" << progression;

    _barreEtat->setValue(progression);
}

void ChoixLexique::_demarrerCreationLexique() {
    qDebug() << "demarrerCreationLexique";

    _changerProgressionBarreEtat(0);
    _etqQuelEtat->setText("Étape 1/2: Création du lexique");
    _btnChoixLexique->setDisabled(true);
    _btnStart->setDisabled(true);
}

void ChoixLexique::_demarrerSimplificationLexique() {
    qDebug() << "demarrerSimplificationLexique";

    _changerProgressionBarreEtat(0);
    _etqQuelEtat->setText("Étape 2/2: Simplification du lexique");
}

void ChoixLexique::_terminerInitialisation() {
    qDebug() << "terminerInitialisation";

    _lexiqueConstruit = true;
    _btnChoixLexique->setDisabled(false);
    _btnStart->setDisabled(false);
    emit initialisationTerminee();
}
