#ifndef SELECTION_OPTIMISATION_H
#define SELECTION_OPTIMISATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>

class SelectionOptimisation : public QWidget
{
    Q_OBJECT

public:
    explicit SelectionOptimisation(QWidget* parent = Q_NULLPTR);

private:
    QVBoxLayout*    _dispotitionHorizontale;
    QPushButton*    _boutonSelectionnerFichier;
    QLabel*         _etiquetteOptimiserPour;
    QButtonGroup*   _groupeQuoiOptimiser;
    QPushButton*    _boutonOptimiser;

};

#endif // !SELECTION_OPTIMISATION_H
