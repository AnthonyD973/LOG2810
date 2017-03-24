#ifndef DISPOSITION_CHOIX_LEXIQUE_H
#define DISPOSITION_CHOIX_LEXIQUE_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

class ChoixLexique : public QWidget
{

    Q_OBJECT

public:
    ChoixLexique(QWidget* parent = Q_NULLPTR);
    virtual ~ChoixLexique() {}

private:
    QVBoxLayout*    _disposition;

    QPushButton*    _btnChoixLexique;
    QPushButton*    _btnStart;

    QVBoxLayout*    _dispoBarreEtat;
    QProgressBar*   _barreEtat;
    QLabel*         _etqQuelEtat;
};

#endif // !DISPOSITION_CHOIX_LEXIQUE_H
