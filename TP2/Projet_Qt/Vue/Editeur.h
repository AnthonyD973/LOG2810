#ifndef DISPOSITION_EDITEUR_H
#define DISPOSITION_EDITEUR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QDialog>
#include <QListWidget>

#include <vector>

#include "Modele/Correction.h"


class Editeur : public QWidget
{

    Q_OBJECT

private:
    enum class EtatCorrecteur : unsigned char {
        SUGGESTION = 0,
        CORRECTION_AUTO,
        CORRECTION_CHOIX
    };

public:
    Editeur(QWidget* parent);
    virtual ~Editeur() { }

    inline QPushButton* getBtnRetour() const { return _btnRetour; }

    void activer();

signals:
    void retourDemande();

public slots:
    void basculerEtatAutoCompletion(int etat);
    void basculerEtatAutoCorrection(int etat);
    void transmettreDemandeRetour();

private:
    void _connecter() const;
    void _caractereAjoute(QString);
    void _motTermine(QString);

    void _accepter(const QString &suggestion);

    int  _getDebutMot(int posFin) const;
    void _changerMotCourant(const QString& mot, QTextCursor &curseur);

private:
    QVBoxLayout*    _disposition;

    QPushButton*    _btnRetour;
    QTextEdit*      _boiteTexte;

    QGroupBox*      _groupeTypeCorrection;
    QCheckBox*      _caseAutoCompletion;
    QCheckBox*      _caseAutoCorrection;

    QListWidget*    _boiteCorrecteur;

    bool            _autoCompletionActif;
    bool            _autoCorrectionActif;

    EtatCorrecteur  _etatCorrecteur  = EtatCorrecteur::SUGGESTION;
    const int       _NUM_MOTS_CORRECTEUR_MAX = 10;

private slots:
    void _reactionChangementDeTexte();
    void _accepter(QListWidgetItem *suggestionChoisie);
//    void _accepterSuggestion(const QString& motCorrige);
//    void _accepterCorrection(const QString& motCorrige);
};

#endif // !DISPOSITION_EDITEUR_H
