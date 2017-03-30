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

    _boiteCorrecteur = new QListWidget(parent);
    _boiteCorrecteur->setFixedSize(300, 150);

    QHBoxLayout* dispoGroupeEtSuggestions = new QHBoxLayout(parent);
    dispoGroupeEtSuggestions->addWidget(_groupeTypeCorrection);
    dispoGroupeEtSuggestions->addWidget(_boiteCorrecteur);

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
    QString texteEcrit = _boiteTexte->toPlainText();
    QString motEcrit;
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
    _boiteCorrecteur->clear();
    emit retourDemande();
}


// PRIVATE:

void Editeur::_connecter() const {
    connect(_boiteTexte,         SIGNAL(textChanged()),     SLOT(_reactionChangementDeTexte()));
    connect(_boiteCorrecteur,    SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(_accepter(QListWidgetItem*)));
    connect(_caseAutoCompletion, SIGNAL(stateChanged(int)), SLOT(basculerEtatAutoCompletion(int)));
    connect(_caseAutoCorrection, SIGNAL(stateChanged(int)), SLOT(basculerEtatAutoCorrection(int)));
    connect(_btnRetour,          SIGNAL(clicked(bool)),     SLOT(transmettreDemandeRetour()));
}


void Editeur::_caractereAjoute(QString mot) {
    _boiteCorrecteur->clear();

    if (_autoCompletionActif) {

        std::vector<std::string> listeStd = Correction::getInstance()->suggerer(mot.toStdString());

        QStringList liste;

        const int MAX_ITERATIONS = std::min((int)listeStd.size(), _NUM_MOTS_CORRECTEUR_MAX);
        for (unsigned int i = 0; i < MAX_ITERATIONS; ++i) {
            liste.append(QString::fromStdString(listeStd[i]));
        }

        _etatCorrecteur = EtatCorrecteur::SUGGESTION;
        _boiteCorrecteur->addItems(liste);
    }
}

void Editeur::_motTermine(QString mot) {
    // DUPLICATION DE CODE!!! WOOOO
    _boiteCorrecteur->clear();

    if (_autoCorrectionActif && mot != "") {

        std::vector<std::string> motsCorrigesStd = Correction::getInstance()->corriger(mot.toStdString());

        if (motsCorrigesStd.size() > 1) {

            QStringList motsCorriges;

            const int MAX_ITERATIONS = std::min((int)motsCorrigesStd.size(), _NUM_MOTS_CORRECTEUR_MAX);
            for (unsigned int i = 0; i < MAX_ITERATIONS; ++i) {
                motsCorriges.append(QString::fromStdString(motsCorrigesStd[i]));
            }

            _boiteCorrecteur->addItems(motsCorriges);
            _etatCorrecteur = EtatCorrecteur::CORRECTION_CHOIX;
        }
        else if (motsCorrigesStd.size() == 1) {
            _etatCorrecteur = EtatCorrecteur::CORRECTION_AUTO;
            _accepter(QString::fromStdString(motsCorrigesStd[0]));
        }
    }
}


void Editeur::_accepter(const QString& suggestion) {
    _boiteCorrecteur->clear();

    int offsetCurseur;
    QString suffixe;
    switch(_etatCorrecteur) {
    case EtatCorrecteur::SUGGESTION:       offsetCurseur = -1; suffixe = " "; break;
    case EtatCorrecteur::CORRECTION_AUTO:  offsetCurseur = -1; suffixe = "" ; break;
    case EtatCorrecteur::CORRECTION_CHOIX: offsetCurseur = -2; suffixe = " "; break;
    }

    QTextCursor curseur = _boiteTexte->textCursor();
    curseur.setPosition(curseur.position() + offsetCurseur);

    _changerMotCourant(suggestion + suffixe, curseur);

    _boiteCorrecteur->clear();
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

void Editeur::_accepter(QListWidgetItem* suggestionChoisie) {
    _accepter(suggestionChoisie->text());
}

//void Editeur::_accepterSuggestion(const QString& motCorrige) {
//    QString suggestion = motCorrige->text();
//    QTextCursor curseur = _boiteTexte->textCursor();
//    _changerMotCourant(suggestion + " ", curseur);

//    _boiteCorrecteur->clear();
//}

//void Editeur::_accepterCorrection(const QString& motCorrige) {
//    int offsetCurseur;
//    switch(_etatCorrecteur) {
//    case EtatCorrecteur::SUGGESTION:       offsetCurseur = -1; break;
//    case EtatCorrecteur::CORRECTION_AUTO:  offsetCurseur = -1; break;
//    case EtatCorrecteur::CORRECTION_CHOIX: offsetCurseur = -2; break;
//    default: break;
//    }

//    QTextCursor curseur = _boiteTexte->textCursor();

//    curseur.setPosition(curseur.position() + offsetCurseur);
//    _changerMotCourant(motCorrige, curseur);

//    _boiteCorrecteur->clear();
//}
