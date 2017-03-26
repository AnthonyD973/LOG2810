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
    void _connecter();

    void _demarrerCreationLexique();
    void _demarrerSimplificationLexique();
    void _terminerInitialisation();

    void _testerBarreEtat();

private:
    QVBoxLayout*    _disposition;

    QPushButton*    _btnChoixLexique;
    QPushButton*    _btnStart;

    QVBoxLayout*    _dispoBarreEtat;
    QProgressBar*   _barreEtat;
    QLabel*         _etqQuelEtat;

    QString         _lexique;
    bool            _lexiqueConstruit;

signals:
    void initialisationTerminee();

public slots:
    void choisirLexique();
    void initialiserLexique();
    void changerProgressionBarreEtat(int progression);

};

#endif // !DISPOSITION_CHOIX_LEXIQUE_H
