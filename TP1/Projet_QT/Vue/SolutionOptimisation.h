#ifndef SOLUTIONOPTIMISATION_H
#define SOLUTIONOPTIMISATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class SolutionOptimisation : public QWidget
{
    Q_OBJECT

public:
    explicit SolutionOptimisation(QWidget* parent = Q_NULLPTR);

private:
    QVBoxLayout*    _dispotitionHorizontale;

    QLabel*         _etiquetteSolutionTrouvee;
    QLabel*         _etiquetteDistanceTotale;
    QLabel*         _etiquetteGainTotal;
    QLabel*         _etiquetteTrouveeEn;

signals:

public slots:
};

#endif // SOLUTIONOPTIMISATION_H
