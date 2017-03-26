#include <QDebug>

#include "ChoixLexique.h"


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

void ChoixLexique::_connecter() {
    connect(_btnChoixLexique, SIGNAL(clicked(bool)), SLOT(choisirLexique()));
    connect(_btnStart, SIGNAL(clicked(bool)), SLOT(initialiserLexique()));
}

void ChoixLexique::_demarrerCreationLexique() {
    qDebug() << "demarrerCreationLexique";

    changerProgressionBarreEtat(0);
    _etqQuelEtat->setText("Étape 1/2: Création du lexique");
    _btnChoixLexique->setDisabled(true);
    _btnStart->setDisabled(true);
}

void ChoixLexique::_demarrerSimplificationLexique() {
    qDebug() << "demarrerSimplificationLexique";

    changerProgressionBarreEtat(0);
    _etqQuelEtat->setText("Étape 2/2: Simplification du lexique");
}

void ChoixLexique::_terminerInitialisation() {
    qDebug() << "terminerInitialisation";

    _lexiqueConstruit = true;
    _btnChoixLexique->setDisabled(false);
    _btnStart->setDisabled(false);
    emit initialisationTerminee();
}

void ChoixLexique::_testerBarreEtat() {
    qDebug() << "testerBarreEtat";

    _barreEtat->show();
    _demarrerCreationLexique();
    for (int i = 1; i <= 99; ++i) {
        changerProgressionBarreEtat(i);
        system("sleep 0.02");
    }
    system("sleep 1"); // haha, le fameux blocage à 99%
    changerProgressionBarreEtat(100);

    system("sleep 1");

    _demarrerSimplificationLexique();
    for (int i = 1; i <= 99; ++i) {
        changerProgressionBarreEtat(i);
        system("sleep 0.02");
    }
    system("sleep 1"); // :-)
    changerProgressionBarreEtat(100);
    _terminerInitialisation();
}


// PUBLIC SLOTS:

void ChoixLexique::choisirLexique() {
    QString cheminLexique = QFileDialog::getOpenFileName(this, "Choisir le lexique", QDir::currentPath() + "/..", "Fichiers texte (*.txt)");

    if (!cheminLexique.isNull() && cheminLexique != _lexique) {
        _lexique = cheminLexique;
        _lexiqueConstruit = false;
        _btnStart->setDisabled(false);
    }

    qDebug() << "choisirLexique" << _lexique;
}

void ChoixLexique::initialiserLexique() {
    qDebug() << "initialiserLexique";

    if (!_lexiqueConstruit) {
        _testerBarreEtat();
    }
    else {
        _terminerInitialisation();
    }
}

void ChoixLexique::changerProgressionBarreEtat(int progression) {
    qDebug() << "changerProgressionBarreEtat" << progression;

    _barreEtat->setValue(progression);
}
