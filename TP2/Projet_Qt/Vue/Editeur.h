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
public:
    Editeur(QWidget* parent);

private:
    QVBoxLayout*    _disposition;

    QPushButton*    _btnRetour;
    QTextEdit*      _editeur;

    QGroupBox*      _groupeTypeCorrection;
    QCheckBox*      _caseAutoCompletion;
    QCheckBox*      _caseAutoCorrection;

    QMessageBox*    _boiteSuggestions;


};

#endif // !DISPOSITION_EDITEUR_H
