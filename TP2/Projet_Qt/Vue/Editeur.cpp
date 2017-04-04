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
    _curseurSurDernierMot = _boiteTexte->textCursor();
    int posEnd = _curseurSurDernierMot.position();
    int posBeg = posEnd;

    void (Editeur::*fctAAppeler)() = &Editeur::_caractereAjoute;
    QString motSelectionne;

    // Déterminer la fin du mot sur lequel se trouve le curseur.
    if (!_curseurSurDernierMot.atEnd()) {
        _curseurSurDernierMot.setPosition(++posEnd, QTextCursor::KeepAnchor);
        motSelectionne = _curseurSurDernierMot.selectedText();

        while (!_curseurSurDernierMot.atEnd() &&
               islower(motSelectionne.at(motSelectionne.size() - 1).toLatin1())) {

            _curseurSurDernierMot.setPosition(++posEnd, QTextCursor::KeepAnchor);
            motSelectionne = _curseurSurDernierMot.selectedText();
        }

        if (!islower(motSelectionne.at(motSelectionne.size() - 1).toLatin1())) {
            _curseurSurDernierMot.setPosition(--posEnd, QTextCursor::KeepAnchor);
            motSelectionne = _curseurSurDernierMot.selectedText();
        }
    }

    _curseurSurDernierMot.setPosition(posEnd, QTextCursor::MoveAnchor);
    _curseurSurDernierMot.setPosition(posBeg, QTextCursor::KeepAnchor);
    motSelectionne = _curseurSurDernierMot.selectedText();

    // Déterminer le début du mot sur lequel se trouve le curseur.
    if (!_curseurSurDernierMot.atStart()) {
        _curseurSurDernierMot.setPosition(--posBeg, QTextCursor::KeepAnchor);
        motSelectionne = _curseurSurDernierMot.selectedText();

        // Ignorer le dernier caractère écrit s'il ne s'agit pas d'un caractère
        // d'un mot et que le curseur n'est pas déjà au début d'un mot.
        bool auDebutDuMot = (posBeg + 1 != posEnd);
        if (!auDebutDuMot && !islower(motSelectionne.at(0).toLatin1())) {
            fctAAppeler = &Editeur::_motTermine;

            _curseurSurDernierMot.setPosition(  posBeg, QTextCursor::MoveAnchor);
            _curseurSurDernierMot.setPosition(--posBeg, QTextCursor::KeepAnchor);
            motSelectionne = _curseurSurDernierMot.selectedText();
        }

        while (!_curseurSurDernierMot.atStart() &&
               islower(motSelectionne.at(0).toLatin1())) {

            _curseurSurDernierMot.setPosition(--posBeg, QTextCursor::KeepAnchor);
            motSelectionne = _curseurSurDernierMot.selectedText();
        }

        if (!islower(motSelectionne.at(0).toLatin1())) {
            _curseurSurDernierMot.setPosition(++posBeg, QTextCursor::KeepAnchor);
            motSelectionne = _curseurSurDernierMot.selectedText();
        }
    }
    else if (motSelectionne.isEmpty()) {
        fctAAppeler = &Editeur::_motTermine;
        _curseurSurDernierMot = _boiteTexte->textCursor();
    }

    (this->*fctAAppeler)();

    qDebug() << "reactionChangementDeTexte" << motSelectionne;

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
    connect(_boiteTexte,         SIGNAL(cursorPositionChanged()), SLOT(_reactionChangementDeTexte()));
    connect(_boiteCorrecteur,    SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(_remplacerDernierMot(QListWidgetItem*)));
    connect(_caseAutoCompletion, SIGNAL(stateChanged(int)), SLOT(basculerEtatAutoCompletion(int)));
    connect(_caseAutoCorrection, SIGNAL(stateChanged(int)), SLOT(basculerEtatAutoCorrection(int)));
    connect(_btnRetour,          SIGNAL(clicked(bool)),     SLOT(transmettreDemandeRetour()));
}


void Editeur::_caractereAjoute() {
    _boiteCorrecteur->clear();

    QString mot = _curseurSurDernierMot.selectedText();

    if (_autoCompletionActif && !mot.isEmpty()) {
        QString mot = _curseurSurDernierMot.selectedText();

        std::vector<std::string> suggestionsStd =
            Correcteur::getInstance()->suggerer(
                mot.toStdString(),
                _NUM_MOTS_CORRECTEUR_MAX);

        QStringList suggestions;
        for (unsigned int i = 0; i < suggestionsStd.size(); ++i) {
            suggestions.append(QString::fromStdString(suggestionsStd[i]));
        }

        _boiteCorrecteur->addItems(suggestions);
    }
}

void Editeur::_motTermine() {
    // DUPLICATION DE CODE!!! WOOOO
    _boiteCorrecteur->clear();

    QString mot = _curseurSurDernierMot.selectedText();

    if (_autoCorrectionActif && !mot.isEmpty()) {
        std::vector<std::string> motsCorrigesStd =
            Correcteur::getInstance()->corriger(mot.toStdString());

        if (motsCorrigesStd.size() > 1) {

            QStringList motsCorriges;

            const unsigned int NUM_MOTS =
                std::min((unsigned int)motsCorrigesStd.size(), _NUM_MOTS_CORRECTEUR_MAX);

            for (unsigned int i = 0; i < NUM_MOTS; ++i) {
                motsCorriges.append(QString::fromStdString(motsCorrigesStd[i]));
            }

            _boiteCorrecteur->addItems(motsCorriges);
        }
        else if (motsCorrigesStd.size() == 1) {
            _remplacerDernierMot(QString::fromStdString(motsCorrigesStd[0]));
        }
    }
}


void Editeur::_remplacerDernierMot(const QString& motRemplacement) {
    _boiteCorrecteur->clear();

    _boiteTexte->setReadOnly(true); // Empêcher l'utilisateur d'écrire pendant
                                    // qu'on modifie le texte.
    _boiteTexte->blockSignals(true); // Ne pas émettre le signal textChanged().

    _curseurSurDernierMot.removeSelectedText();
    _curseurSurDernierMot.insertText(motRemplacement);

    _boiteTexte->blockSignals(false);
    _boiteTexte->setReadOnly(false);
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


// PRIVATE SLOTS:

void Editeur::_remplacerDernierMot(QListWidgetItem* suggestionChoisie) {
    _remplacerDernierMot(suggestionChoisie->text() + " ");
}
