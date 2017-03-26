#include <cctype>
#include <QDebug>
#include <QListWidget>

#include "Editeur.h"

Editeur::Editeur(QWidget* parent)
    : QWidget(parent)
{
    _autoCompletionActif = false;
    _autoCorrectionActif = false;

    _btnRetour = new QPushButton("&Retour", parent);

    _boiteTexte = new QTextEdit(parent);


    _caseAutoCompletion     = new QCheckBox("Activer l'autoco&mplétion", parent);
    _caseAutoCorrection     = new QCheckBox("Activer l'autocorr&ection", parent);

    QVBoxLayout* dispoGroupeTypeCorrection = new QVBoxLayout(parent);
    dispoGroupeTypeCorrection->addWidget(_caseAutoCompletion);
    dispoGroupeTypeCorrection->addWidget(_caseAutoCorrection);

    _groupeTypeCorrection   = new QGroupBox("Options de l'éditeur", parent);
    _groupeTypeCorrection->setLayout(dispoGroupeTypeCorrection);

    _boiteAutoCompletion = new BoiteAutoCompletion(this);
    _boiteAutoCompletion->setWindowTitle("Suggestions");


    _disposition = new QVBoxLayout(parent);
    _disposition->addWidget(_btnRetour);
    _disposition->addWidget(_boiteTexte);
    _disposition->addWidget(_groupeTypeCorrection);

    setLayout(_disposition);
    _connecter();
}

// PRIVATE:

void Editeur::_connecter() const {
    connect(_boiteTexte,          SIGNAL(textChanged()),     SLOT(reactionChangementDeTexte()));
    connect(_boiteAutoCompletion, SIGNAL(suggestionChoisie(QString)), SLOT(_accepterSuggestion(QString)));
    connect(_caseAutoCompletion,  SIGNAL(stateChanged(int)), SLOT(basculerEtatAutoCompletion(int)));
    connect(_caseAutoCorrection,  SIGNAL(stateChanged(int)), SLOT(basculerEtatAutoCorrection(int)));
    connect(_btnRetour,           SIGNAL(clicked(bool)),     SLOT(transmettreDemandeRetour()));
}

void Editeur::_motTermine(QString mot) {
    if (_autoCorrectionActif) {
        "chuck_norris";
    }
}

void Editeur::_caractereAjoute(QString mot) {
    if (_autoCompletionActif) {
        QStringList liste;
        liste.append("foo");
        liste.append("bar");
        liste.append("foobar");
        liste.append("baz");
        liste.append("qux");

        _boiteAutoCompletion->setItems(liste);
        _boiteAutoCompletion->show();
    }
}

int Editeur::_getDebutMot(int posFin) const {
    int posBeg = posFin;

    QString texteEcrit = _boiteTexte->toPlainText();

    while (posBeg >= 0 && islower(texteEcrit.at(posBeg).toLatin1())) {
        --posBeg;
    }
    ++posBeg;

    return posBeg;
}

// PUBLIC SLOTS:

void Editeur::reactionChangementDeTexte() {
    QString texteEcrit = _boiteTexte->toPlainText(),
            motEcrit;
    int posFin = _boiteTexte->textCursor().position() - 1;

    // Cas où la boîte est n'est pas vide
    if (posFin >= 0) {
        void (Editeur::*fctAAppeler)(QString);

        if (islower(texteEcrit.at(posFin).toLatin1())) {
            fctAAppeler = &Editeur::_caractereAjoute;
        }
        else {
            fctAAppeler = &Editeur::_motTermine;
        }

        int posBeg = _getDebutMot(posFin);

        motEcrit = texteEcrit.mid(posBeg, posFin - posBeg + 1);

        (this->*fctAAppeler)(motEcrit);
    }
    else {
        motEcrit = "";
        _motTermine(motEcrit);
    }
    qDebug() << "reactionChangementDeTexte" << motEcrit;

}

void Editeur::basculerEtatAutoCompletion(int etat) {
    _autoCompletionActif = (etat == Qt::CheckState::Checked);
    qDebug() << "basculerEtatAutoCompletion" << _autoCompletionActif << etat;
}

void Editeur::basculerEtatAutoCorrection(int etat) {
    _autoCorrectionActif = (etat == Qt::CheckState::Checked);
    qDebug() << "basculerEtatAutoCorrection" << _autoCorrectionActif << etat;
}

void Editeur::transmettreDemandeRetour() {
    emit retourDemande();
}


// PRIVATE SLOTS:

void Editeur::_accepterSuggestion(QString suggestion) {
    qDebug() << "accepterSuggestion" << suggestion;

    _boiteTexte->setReadOnly(true); // Empêcher l'utilisateur d'écrire pendant
                                    // qu'on modifie le texte.

    QTextCursor curseur = _boiteTexte->textCursor();

    int posFin = curseur.position() - 1;
    int posBeg = _getDebutMot(posFin);

    curseur.setPosition(posFin+1, QTextCursor::MoveAnchor);
    curseur.setPosition(posBeg, QTextCursor::KeepAnchor);
    curseur.removeSelectedText();

    _boiteTexte->blockSignals(true); // Ne pas émettre le signal textChanged()

    curseur.insertText(suggestion);

    _boiteTexte->blockSignals(false);
    _boiteTexte->setReadOnly(false);
}
