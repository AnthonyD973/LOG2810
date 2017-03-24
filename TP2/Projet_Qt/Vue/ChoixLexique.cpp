#include <QDebug>

#include "ChoixLexique.h"

ChoixLexique::ChoixLexique(QWidget* parent)
    : QWidget(parent)
{
    _btnChoixLexique = new QPushButton((QString)"Choisir le lexique", parent);
    _btnStart        = new QPushButton((QString)"START!!", parent);
    _barreEtat       = new QProgressBar(parent);
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

void ChoixLexique::_connecter() {
    connect(_btnStart, SIGNAL(clicked(bool)), SLOT(testerBarreEtat()));
    connect(this, SIGNAL(initialisationTerminee()), SLOT(terminerInitialisation()));
}

// PUBLIC SLOTS:

void ChoixLexique::changerProgressionBarreEtat(int progression) {
    qDebug() << "changerProgressionBarreEtat" << progression;

    _barreEtat->setValue(progression);
}

void ChoixLexique::demarrerCreationLexique() {
    qDebug() << "demarrerCreationLexique";

    changerProgressionBarreEtat(0);
    _etqQuelEtat->setText("Étape 1/2: Création du lexique");
    _btnChoixLexique->setDisabled(true);
    _btnStart->setDisabled(true);
}

void ChoixLexique::demarrerSimplificationLexique() {
    qDebug() << "demarrerSimplificationLexique";

    changerProgressionBarreEtat(0);
    _etqQuelEtat->setText("Étape 2/2: Simplification du lexique");
}

void ChoixLexique::terminerInitialisation() {
    _btnChoixLexique->setDisabled(false);
    _btnStart->setDisabled(false);
}


void ChoixLexique::testerBarreEtat() {
    demarrerCreationLexique();
    for (int i = 1; i <= 99; ++i) {
        changerProgressionBarreEtat(i);
        system("sleep 0.02");
    }
    system("sleep 1"); // haha, le fameux blocage à 99%
    changerProgressionBarreEtat(100);
    system("sleep 1");

    demarrerSimplificationLexique();
    for (int i = 1; i <= 99; ++i) {
        changerProgressionBarreEtat(i);
        system("sleep 0.02");
    }
    system("sleep 1");
    changerProgressionBarreEtat(100);
    emit initialisationTerminee();
}
