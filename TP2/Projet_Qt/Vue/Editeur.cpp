#include <cctype>
#include <QDebug>

#include "Editeur.h"

Editeur::Editeur(QWidget* parent)
    : QWidget(parent)
{
    _motEcrit = "";
    _autoCompletionActif = false;
    _autoCorrectionActif = false;

    _btnRetour = new QPushButton("Retour", parent);

    _boiteTexte = new QTextEdit(parent);

    _caseAutoCompletion     = new QCheckBox("Activer l'autocomplétion", parent);
    _caseAutoCorrection     = new QCheckBox("Activer l'autocorrection", parent);
    QVBoxLayout* dispoGroupeTypeCorrection = new QVBoxLayout(parent);
    dispoGroupeTypeCorrection->addWidget(_caseAutoCompletion);
    dispoGroupeTypeCorrection->addWidget(_caseAutoCorrection);

    _groupeTypeCorrection   = new QGroupBox(parent);
    _groupeTypeCorrection->setLayout(dispoGroupeTypeCorrection);

    _boiteSuggestions = new QMessageBox(parent);
    _boiteSuggestions->hide();

    _disposition = new QVBoxLayout(parent);

    _disposition->addWidget(_btnRetour);
    _disposition->addWidget(_boiteTexte);
    _disposition->addWidget(_groupeTypeCorrection);
    _disposition->addWidget(_boiteSuggestions);

    setLayout(_disposition);

    _connecter();
}

// PRIVATE:

void Editeur::_connecter() {
    connect(_boiteTexte,         SIGNAL(textChanged()),     SLOT(reactionChangementDeTexte()));
    connect(_caseAutoCompletion, SIGNAL(stateChanged(int)), SLOT(basculerEtatAutoCompletion(int)));
    connect(_caseAutoCorrection, SIGNAL(stateChanged(int)), SLOT(basculerEtatAutoCorrection(int)));
}

void Editeur::reactionChangementDeTexte() {
    typedef void (Editeur::*signalAEmettre_t)(QString);
    signalAEmettre_t signalAEmettre;

    QString texteEcrit = _boiteTexte->toPlainText();
    int pBeg = _boiteTexte->textCursor().position() - 1, pEnd = pBeg;

    // Cas où la boîte est n'est pas vide
    if (pBeg >= 0) {
        if (islower(texteEcrit.at(pBeg).toLatin1())) {
            signalAEmettre = &Editeur::caractereAjoute;
        }
        else {
            signalAEmettre = &Editeur::motTermine;
        }

        while (pBeg >= 0 && islower(texteEcrit.at(pBeg).toLatin1())) {
            --pBeg;
        }
        ++pBeg;

        _motEcrit = texteEcrit.mid(pBeg, pEnd - pBeg + 1);

        emit (this->*signalAEmettre)(_motEcrit);
    }
    else {
        _motEcrit = "";
        emit motTermine(_motEcrit);
    }
    qDebug() << "reactionChangementDeTexte" << _motEcrit;

}

void Editeur::basculerEtatAutoCompletion(int etat) {
    _autoCompletionActif = (etat == Qt::CheckState::Checked);
    qDebug() << "basculerEtatAutoCompletion" << _autoCompletionActif << etat;
}

void Editeur::basculerEtatAutoCorrection(int etat) {
    _autoCorrectionActif = (etat == Qt::CheckState::Checked);
    qDebug() << "basculerEtatAutoCorrection" << _autoCorrectionActif << etat;
}
