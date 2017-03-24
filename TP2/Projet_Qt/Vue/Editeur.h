#ifndef DISPOSITION_EDITEUR_H
#define DISPOSITION_EDITEUR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QMessageBox>

class Editeur : public QWidget
{

    Q_OBJECT

public:
    Editeur(QWidget* parent);
    virtual ~Editeur() {}

    inline QPushButton* getBtnRetour() const { return _btnRetour; }

private:
    void _connecter();

private:
    QVBoxLayout*    _disposition;

    QPushButton*    _btnRetour;
    QTextEdit*      _boiteTexte;

    QGroupBox*      _groupeTypeCorrection;
    QCheckBox*      _caseAutoCompletion;
    QCheckBox*      _caseAutoCorrection;

    QMessageBox*    _boiteSuggestions;

    QString         _motEcrit;

    bool            _autoCompletionActif;
    bool            _autoCorrectionActif;

public slots:
    void reactionChangementDeTexte();
    void basculerEtatAutoCompletion(int etat);
    void basculerEtatAutoCorrection(int etat);

signals:
    void motTermine(QString);
    void caractereAjoute(QString);

};

#endif // !DISPOSITION_EDITEUR_H
