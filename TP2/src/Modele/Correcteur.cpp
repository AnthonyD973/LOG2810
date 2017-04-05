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

/****************************************************************************
 * Fonction: Correcteur::suggerer
 * Description: Utilise la methode suggerer de la classe lexique
 * Parametres:	- (const String&) mot: le mot ecrit(IN)
                - (int) numMotsMax: nombre maximal de suggestions (IN)
 * Retour:		(vector<string>) les mots suggeres
 ****************************************************************************/
vector<string> Correcteur::suggerer(const string& mot, int numMotsMax) {
    return Lexique::getInstance()->suggerer(mot, numMotsMax);
}

/****************************************************************************
 * Fonction: Correcteur::corriger
 * Description: Corrige le mot entre en parametre
 * Parametres:	- (const string&) mot: le mot a corriger(IN)
 * Retour:		(vector<string>) les mots qui different d'une lettre au mot entree en parametre
 ****************************************************************************/
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

/****************************************************************************
 * Fonction: Correcteur::creerCorrection
 * Description: Cree une instance de la classe Correction
 * Parametres:	aucun
 * Retour:		aucun
 ****************************************************************************/
void Correcteur::creerCorrection() {
    delete _instance;
    _instance = new Correcteur();
}

/****************************************************************************
 * Fonction: Correcteur::construireCorrection
 * Description: cree et construit le lexique a partir du fichier .txt
 * Parametres:	- (const String&) nomLexique: le nom du fichier .txt(IN)
 * Retour:		aucun
 ****************************************************************************/
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
