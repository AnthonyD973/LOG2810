#ifndef DISPOSITION_CHOIX_LEXIQUE_H
#define DISPOSITION_CHOIX_LEXIQUE_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

class DispositionChoixLexique : public QVBoxLayout {
public:
    DispositionChoixLexique::DispositionChoixLexique(QWidget* parent);

private:
    QPushButton*    _btnChoixLexique;
    QPushButton*    _btnStart;

    QVBoxLayout*    _dispoBarreEtat;
    QProgressBar*   _barreEtat;
    QLabel*         _etqQuelEtat;
};

#endif // !DISPOSITION_CHOIX_LEXIQUE_H
