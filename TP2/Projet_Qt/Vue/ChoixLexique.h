#ifndef DISPOSITION_CHOIX_LEXIQUE_H
#define DISPOSITION_CHOIX_LEXIQUE_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

class ChoixLexique : public QWidget {
public:
    ChoixLexique(QWidget* parent = Q_NULLPTR);

private:
    QVBoxLayout*    _disposition;

    QPushButton*    _btnChoixLexique;
    QPushButton*    _btnStart;

    QVBoxLayout*    _dispoBarreEtat;
    QProgressBar*   _barreEtat;
    QLabel*         _etqQuelEtat;
};

#endif // !DISPOSITION_CHOIX_LEXIQUE_H
