/****************************************************************************
 * Fichier: Lexique.cpp
 * Auteurs: Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 * Date: 28 mars 2017
 * Description: Implémentation de la classe Lexique
 ****************************************************************************/

#pragma once
#include <QObject>

#include "Lexique.h"


const char alphabet[] =  "qwertyuiopasdfghjklzxcvbnm";


class Correction : public QObject
{
    Q_OBJECT

public:
    vector<string> suggerer(string mot);
    vector<string> corrigerMot(string mot);

    static void creerCorrection();
    static void construireCorrection(const string& nomLexique);
    inline static Correction* getInstance() { return _instance; }

private:
    Correction();
    virtual ~Correction();

    static void _connecter();

private:
    static Correction* _instance;

// Pour la barre de progression de la vue
signals:
    void progressionConstruction(int progressionPourcent);
    void progressionMinimisation(int progressionPourcent);
    void constructionTerminee();

private slots:
    void _progressionConstruction(int progressionPourcent);
    void _progressionMinimisation(int progressionPourcent);
    void _constructionTerminee();
};
