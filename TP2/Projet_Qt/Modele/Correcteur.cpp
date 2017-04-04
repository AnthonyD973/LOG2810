/****************************************************************************
 * Fichier: Correction.cpp
 * Auteurs: Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 * Date: 28 mars 2017
 * Description: Implémentation de la classe Correction
 ****************************************************************************/
#include "Correcteur.h"

Correcteur* Correcteur::_instance = nullptr;

Correcteur::Correcteur()
{ }

Correcteur::~Correcteur()
{ }

vector<string> Correcteur::suggerer(const string& mot, int numMotsMax) {
    return Lexique::getInstance()->suggerer(mot, numMotsMax);
}

vector<string> Correcteur::corriger(const string& mot)
{
    string motCopie = mot;
    vector<string> motsCorriges;

    if (Lexique::getInstance()->existe(motCopie))
    {
        motsCorriges.push_back(motCopie);
    }
    else
    {
        for (unsigned int i = 0; i < motCopie.size(); i++)
        {
            char reserve = motCopie[i];
            for (int j = 0; j < 26; j++)
            {
                motCopie[i] = alphabet[j];
                if (Lexique::getInstance()->existe(motCopie))
                    motsCorriges.push_back(motCopie);
            }
            motCopie[i] = reserve;
        }

    }

    return motsCorriges;
}

void Correcteur::creerCorrection() {
    delete _instance;
    _instance = new Correcteur();
}

void Correcteur::construireCorrection(const string& nomLexique) {
    Lexique::creerLexique(3);
    _connecter();
    Lexique::construireLexique(nomLexique);
}


// PRIVATE:

void Correcteur::_connecter() {
    connect(Lexique::getInstance(), SIGNAL(progressionConstruction(int)), _instance, SLOT(_progressionConstruction(int)));
    connect(Lexique::getInstance(), SIGNAL(constructionTerminee()),       _instance, SLOT(_constructionTerminee()));
}


// PRIVATE SLOTS:

void Correcteur::_progressionConstruction(int progressionPourcent) {
    emit progressionConstruction(progressionPourcent);
}

void Correcteur::_constructionTerminee() {
    emit constructionTerminee();
}
