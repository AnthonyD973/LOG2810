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

#include <vector>

#include "BoiteAutoCompletion.h"

class Editeur : public QWidget
{

    Q_OBJECT

public:
    Editeur(QWidget* parent);

    inline QPushButton* getBtnRetour() const { return _btnRetour; }

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

    BoiteAutoCompletion* _boiteAutoCompletion;

    bool            _autoCompletionActif;
    bool            _autoCorrectionActif;

signals:
    void retourDemande();

public slots:
    void reactionChangementDeTexte();
    void basculerEtatAutoCompletion(int etat);
    void basculerEtatAutoCorrection(int etat);
    void transmettreDemandeRetour();

private slots:
    void _accepterSuggestion(const QString &suggestion);
    void _corrigerMot(const QString &motCorrige);
};

#endif // !DISPOSITION_EDITEUR_H
