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

#include <ctime>

#include "Modèle/Algo.h"
#include "Modèle/Chemin.h"

class SelectionOptimisation : public QWidget
{
    enum _TypeOptimisation : char {
        _DISTANCE_MAX = '0',
        _GAIN_MIN,
        _NUM_TYPES_OPTIMISATION
    };

    Q_OBJECT

public:
    explicit SelectionOptimisation(QWidget* parent = Q_NULLPTR);

    // =================
    // =   ATTRIBUTS   =
    // =================

private:
    Algo            _algo;

    QVBoxLayout*    _disposition;

    QPushButton*    _boutonSelectionnerFichier;
    QGroupBox*      _groupeTypeOptimisation;
    QLineEdit*      _valeurCherchee;
    QPushButton*    _boutonOptimiser;

    QString         _fichierCarte;
    int             _valeurCible = -1;

    _TypeOptimisation _typeOptimisation = _NUM_TYPES_OPTIMISATION;

    // =================
    // =    SIGNAUX    =
    // =================

signals:
    void optimisationTerminee(const Chemin& cheminOptimal, std::time_t tempsPris);

    // =================
    // =     SLOTS     =
    // =================

public slots:
    void selectionFichierCarte(bool);
    void changerValeurCible(const QString& valeur);
    void commencerOptimisation(bool);

    void selectionnerDistanceMaximale(bool);
    void selectionnerGainMinimal(bool);
};

#endif // !SELECTION_OPTIMISATION_H
