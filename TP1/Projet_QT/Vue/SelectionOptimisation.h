#ifndef SELECTION_OPTIMISATION_H
#define SELECTION_OPTIMISATION_H

#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>

class SelectionOptimisation : public QWidget
{
    Q_OBJECT

public:
    explicit SelectionOptimisation(QWidget* parent = Q_NULLPTR);

private:
    QVBoxLayout*    _disposition;

    QPushButton*    _boutonSelectionnerFichier;
    QGroupBox*      _groupeTypeOptimisation;
    QLineEdit*      _valeurCherchee;
    QPushButton*    _boutonOptimiser;

    QString         _fichierCarte;

public slots:
    void selectionFichierCarte(bool);

signals:

};

#endif // !SELECTION_OPTIMISATION_H
