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

#include "Modele/Correcteur.h"


class Editeur : public QWidget
{

    Q_OBJECT

private:

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
    void _caractereAjoute();
    void _motTermine();

    void _remplacerDernierMot(const QString& motRemplacement);

    int  _getDebutMot(int posFin) const;

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

    QTextCursor     _curseurSurDernierMot;
    const unsigned int _NUM_MOTS_CORRECTEUR_MAX = 10;

private slots:
    void _reactionChangementDeTexte();
    void _remplacerDernierMot(QListWidgetItem *suggestionChoisie);
//    void _accepterSuggestion(const QString& motCorrige);
//    void _accepterCorrection(const QString& motCorrige);
};

#endif // !DISPOSITION_EDITEUR_H
