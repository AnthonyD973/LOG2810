#include <QDebug>

#include "ChoixLexique.h"
#include "Modele/Correcteur.h"


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
    connect(Correcteur::getInstance(), SIGNAL(progressionConstruction(int)), SLOT(_changerProgressionBarreEtat(int)));
    connect(Correcteur::getInstance(), SIGNAL(constructionTerminee()),       SLOT(_terminerConstruction()));
}

void ChoixLexique::_deconnecterDuCorrecteur() const {
    if (Correcteur::getInstance() != nullptr) {
        disconnect(Correcteur::getInstance(), SIGNAL(progressionConstruction(int)), this, SLOT(_changerProgressionBarreEtat(int)));
        disconnect(Correcteur::getInstance(), SIGNAL(constructionTerminee()),       this, SLOT(_terminerConstruction()));
    }
}

void ChoixLexique::_terminerInitialisation() {
    qDebug() << "terminerInitialisation";

    _lexiqueConstruit = true;
    _btnChoixLexique->setDisabled(false);
    _btnStart->setDisabled(false);

    emit initialisationTerminee();
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
    _terminerInitialisation();
}


// PRIVATE SLOTS:

void ChoixLexique::_choisirLexique() {
    QString cheminLexique = QFileDialog::getOpenFileName(this, "Choisir le lexique", QDir::currentPath() + "/..", "Fichiers texte (*.txt)");

    if (!cheminLexique.isEmpty() && cheminLexique != _fichierLexique) {
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
        Correcteur::creerCorrection();
        _connecterAuCorrecteur();

        _barreEtat->show();
        Correcteur::construireCorrection(_fichierLexique.toStdString());
    }
    else {
        _etqQuelEtat->setText("Lexique déjà construit!");
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
    _etqQuelEtat->setText("Création du lexique.");
    _btnChoixLexique->setDisabled(true);
    _btnStart->setDisabled(true);
    system("sleep 5");
}

void ChoixLexique::_terminerConstruction() {
    qDebug() << "_terminerConstruction";

    _etqQuelEtat->setText("Construction terminée.");
    _terminerInitialisation();
}
