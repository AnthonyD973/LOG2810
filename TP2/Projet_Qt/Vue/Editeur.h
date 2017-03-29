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

public:
    Editeur(QWidget* parent);

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
    void _motTermine(QString);
    void _caractereAjoute(QString);

    int  _getDebutMot(int posFin) const;
    void _changerMotCourant(const QString& mot, QTextCursor &curseur);

private:
    QVBoxLayout*    _disposition;

    QPushButton*    _btnRetour;
    QTextEdit*      _boiteTexte;

    QGroupBox*      _groupeTypeCorrection;
    QCheckBox*      _caseAutoCompletion;
    QCheckBox*      _caseAutoCorrection;

    QListWidget*    _suggestions;

    bool            _autoCompletionActif;
    bool            _autoCorrectionActif;

    Correction      _correcteur;

private slots:
    void _reactionChangementDeTexte();
    void _accepterSuggestion(QListWidgetItem *suggestionChoisie);
    void _corrigerMot(const QString& motCorrige);
};

#endif // !DISPOSITION_EDITEUR_H
