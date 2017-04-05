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


class Correcteur : public QObject
{
    Q_OBJECT

public:
    vector<string> suggerer(const string& mot, int numMotsMax);
    vector<string> corriger(const string& mot);

    static void creerCorrection();
    static void construireCorrection(const string& nomLexique);
    inline static Correcteur* getInstance() { return _instance; }

private:
    Correcteur();
    virtual ~Correcteur();

    static void _connecter();

private:
    static Correcteur* _instance;

// Pour la barre de progression de la vue
signals:
    void progressionConstruction(int progressionPourcent);
    void constructionTerminee();

private slots:
    void _progressionConstruction(int progressionPourcent);
    void _constructionTerminee();
};
