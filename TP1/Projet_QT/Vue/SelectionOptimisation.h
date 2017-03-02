#ifndef SELECTION_OPTIMISATION_H
#define SELECTION_OPTIMISATION_H

#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>

#include <ctime>

#include "Modele/Algo.h"
#include "Modele/Chemin.h"

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
    Graphe          _graphe;
    int             _indiceSommetDepart;

    QVBoxLayout*    _disposition;

    QHBoxLayout*    _dispoFichierSommet;
    QPushButton*    _boutonSelectionnerFichier;
    QComboBox*      _boiteDeroulanteSommets;

    QGroupBox*      _groupeTypeOptimisation;
    QLineEdit*      _valeurCherchee;
    QPushButton*    _boutonOptimiser;

    QString         _fichierCarte;
    int             _valeurCible = -1;

    _TypeOptimisation _typeOptimisation = _NUM_TYPES_OPTIMISATION;

    bool
        _carteOk            = false,
        _typeOptimisationOk = false,
        _valeurCibleOk      = false;

    // =================
    // =    SIGNAUX    =
    // =================

signals:
    void optimisationTerminee(const Chemin& cheminOptimal, const Graphe& graphe, std::time_t tempsPris);
    void etatBoutonOptimisationDoitEtreChange();

    // =================
    // =     SLOTS     =
    // =================

public slots:
    void selectionFichierCarte(bool);
    void changerValeurCible(const QString& valeur);
    void changerIndiceSommetDepart(const QString& nom);
    void changerEtatBoutonOptimisation();
    void commencerOptimisation(bool);

    void selectionnerDistanceMaximale(bool);
    void selectionnerGainMinimal(bool);
};

#endif // !SELECTION_OPTIMISATION_H
