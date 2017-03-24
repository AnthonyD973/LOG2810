#ifndef DISPOSITION_CHOIX_LEXIQUE_H
#define DISPOSITION_CHOIX_LEXIQUE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

class ChoixLexique : public QWidget
{

    Q_OBJECT

public:
    ChoixLexique(QWidget* parent = Q_NULLPTR);

private:
    void _connecter();

private:
    QVBoxLayout*    _disposition;

    QPushButton*    _btnChoixLexique;
    QPushButton*    _btnStart;

    QVBoxLayout*    _dispoBarreEtat;
    QProgressBar*   _barreEtat;
    QLabel*         _etqQuelEtat;

signals:
    void initialisationTerminee();

public slots:
    void changerProgressionBarreEtat(int progression);
    void demarrerCreationLexique();
    void demarrerSimplificationLexique();
    void terminerInitialisation();

    void testerBarreEtat();
};

#endif // !DISPOSITION_CHOIX_LEXIQUE_H
