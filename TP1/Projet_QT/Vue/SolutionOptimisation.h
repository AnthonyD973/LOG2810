#ifndef SOLUTIONOPTIMISATION_H
#define SOLUTIONOPTIMISATION_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>

#include <ctime>

#include "Modèle/Chemin.h"

class SolutionOptimisation : public QWidget
{
    Q_OBJECT

public:
    explicit SolutionOptimisation(QWidget* parent = Q_NULLPTR);

    // =================
    // =   ATTRIBUTS   =
    // =================

private:
    QVBoxLayout*    _disposition;

    QLabel*    _trouveeEn;
    QLineEdit* _solutionTrouvee;
    QLabel*    _distanceTotale;
    QLabel*    _gainTotal;


    // =================
    // =    SIGNAUX    =
    // =================

signals:


    // =================
    // =     SLOTS     =
    // =================

public slots:
    void afficherResultatsOptimisation(const Chemin& cheminOptimal, std::time_t tempsPris);
};

#endif // SOLUTIONOPTIMISATION_H
