#include <QDebug>
#include <QListWidget>

#include <cctype>
#include <vector>
#include <string>

#include "Editeur.h"

Editeur::Editeur(QWidget* parent)
    : QWidget(parent)
{
    _autoCompletionActif = false;
    _autoCorrectionActif = false;

    _btnRetour = new QPushButton("&Retour", parent);

    _boiteTexte = new QTextEdit(parent);
    _boiteTexte->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    _caseAutoCompletion     = new QCheckBox("Activer l'autoco&mplétion", parent);
    _caseAutoCorrection     = new QCheckBox("Activer l'autocorr&ection", parent);

    QVBoxLayout* dispoGroupeTypeCorrection = new QVBoxLayout(parent);
    dispoGroupeTypeCorrection->addWidget(_caseAutoCompletion);
    dispoGroupeTypeCorrection->addWidget(_caseAutoCorrection);
    _groupeTypeCorrection   = new QGroupBox("Options de l'éditeur", parent);
    _groupeTypeCorrection->setLayout(dispoGroupeTypeCorrection);
    _groupeTypeCorrection->setFixedHeight(100);

    _suggestions = new QListWidget(parent);
    _suggestions->setFixedSize(300, 150);

    QHBoxLayout* dispoGroupeEtSuggestions = new QHBoxLayout(parent);
    dispoGroupeEtSuggestions->addWidget(_groupeTypeCorrection);
    dispoGroupeEtSuggestions->addWidget(_suggestions);

    QWidget* groupeEtSuggestions = new QWidget(parent);
    groupeEtSuggestions->setLayout(dispoGroupeEtSuggestions);


    _disposition = new QVBoxLayout(parent);
    _disposition->addWidget(_btnRetour);
    _disposition->addWidget(_boiteTexte);
    _disposition->addWidget(groupeEtSuggestions);

    setLayout(_disposition);
    _connecter();
}

void Editeur::activer() {
    _boiteTexte->blockSignals(true); // Ne pas émettre le signal textChanged().
    _boiteTexte->clear();
    _boiteTexte->blockSignals(false);
}


// PUBLIC SLOTS:

void Editeur::_reactionChangementDeTexte() {
    QString texteEcrit = _boiteTexte->toPlainText(),
            motEcrit;
    int posFin = _boiteTexte->textCursor().position() - 1;

    bool boiteEstVide = (posFin < 0);
    if (!boiteEstVide) {
        void (Editeur::*fctAAppeler)(QString);

        if (islower(texteEcrit.at(posFin).toLatin1())) {
            fctAAppeler = &Editeur::_caractereAjoute;
        }
        else {
            fctAAppeler = &Editeur::_motTermine;
            --posFin;
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
    _boiteTexte->clear();
    _suggestions->clear();
    emit retourDemande();
}


// PRIVATE:

void Editeur::_connecter() const {
    connect(_boiteTexte,          SIGNAL(textChanged()),     SLOT(_reactionChangementDeTexte()));
    connect(_suggestions,         SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(_accepterSuggestion(QListWidgetItem*)));
    connect(_caseAutoCompletion,  SIGNAL(stateChanged(int)), SLOT(basculerEtatAutoCompletion(int)));
    connect(_caseAutoCorrection,  SIGNAL(stateChanged(int)), SLOT(basculerEtatAutoCorrection(int)));
    connect(_btnRetour,           SIGNAL(clicked(bool)),     SLOT(transmettreDemandeRetour()));
}

void Editeur::_motTermine(QString mot) {
    if (_autoCorrectionActif && mot != "") {
        _corrigerMot("chucknorris");
    }
}

void Editeur::_caractereAjoute(QString mot) {
    if (_autoCompletionActif) {
        std::vector<std::string> listeStd;

        QStringList liste;
        liste.append("un");
        liste.append("deux");
        liste.append("trois");
        liste.append("quatre");
        liste.append("cinq");
        liste.append("six");
        liste.append("sept");
        liste.append("huit");
        liste.append("neuf");
        liste.append("dix");

        _suggestions->clear();
        _suggestions->addItems(liste);
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

void Editeur::_changerMotCourant(const QString& mot, QTextCursor& curseur) {
    _boiteTexte->setReadOnly(true); // Empêcher l'utilisateur d'écrire pendant
                                    // qu'on modifie le texte.

    int posFin = curseur.position() - 1;
    int posBeg = _getDebutMot(posFin);

    _boiteTexte->blockSignals(true); // Ne pas émettre le signal textChanged().

    curseur.setPosition(posFin+1, QTextCursor::MoveAnchor);
    curseur.setPosition(posBeg,   QTextCursor::KeepAnchor);
    curseur.removeSelectedText();

    curseur.insertText(mot);

    _boiteTexte->blockSignals(false);
    _boiteTexte->setReadOnly(false);
}


// PRIVATE SLOTS:

void Editeur::_accepterSuggestion(QListWidgetItem* suggestionChoisie) {
    QString suggestion = suggestionChoisie->text();
    QTextCursor curseur = _boiteTexte->textCursor();
    _changerMotCourant(suggestion + " ", curseur);

    _suggestions->clear();

    qDebug() << "_accepterSuggestion" << suggestion;
}

void Editeur::_corrigerMot(const QString& motCorrige) {
    qDebug() << "_corrigerMot" << motCorrige;

    QTextCursor curseur = _boiteTexte->textCursor();
    curseur.setPosition(curseur.position() - 1);
    _changerMotCourant(motCorrige, curseur);

    _suggestions->clear();
}
