#ifndef DISPOSITION_CHOIX_LEXIQUE_H
#define DISPOSITION_CHOIX_LEXIQUE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <QFileDialog>

class ChoixLexique : public QWidget
{

    Q_OBJECT

public:
    ChoixLexique(QWidget* parent = Q_NULLPTR);

private:
    void _connecter() const;
    void _connecterAuCorrecteur() const;
    void _deconnecterDuCorrecteur() const;

    void _terminerInitialisation();

    void _testerBarreEtat();

private:
    QVBoxLayout*    _disposition;

    QPushButton*    _btnChoixLexique;
    QPushButton*    _btnStart;

    QVBoxLayout*    _dispoBarreEtat;
    QProgressBar*   _barreEtat;
    QLabel*         _etqQuelEtat;

    QString         _fichierLexique;
    bool            _lexiqueConstruit;

signals:
    void initialisationTerminee();

private slots:
    void _choisirLexique();
    void _initialiserLexique();
    void _changerProgressionBarreEtat(int progression);
    void _demarrerCreationLexique();
    void _terminerConstruction();

};

#endif // !DISPOSITION_CHOIX_LEXIQUE_H
