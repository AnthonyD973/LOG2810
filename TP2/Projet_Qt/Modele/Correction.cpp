/****************************************************************************
 * Fichier: Correction.cpp
 * Auteurs: Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 * Date: 28 mars 2017
 * Description: Implémentation de la classe Correction
 ****************************************************************************/
#include "Correction.h"

Correction* Correction::_instance = nullptr;

Correction::Correction()
{ }

Correction::~Correction()
{ }

vector<string> Correction::suggerer(string mot) {
    vector<string> suggestions;
	int nbSuggestions=0;
	Node* racineI=Lexique::getInstance()->_racine;
	while(nbSuggestions<10)
	{
		for(int i=0; i<mot.size();i++)
			{
				if(Lexique::getInstance()->_racine->getEnfant(mot[i])!=nullptr)
					{
						for(int j=0;j<Lexique::getInstance()->_racine->getEnfant(mot[i])->_sousMotsValides.size();j++)
							{
								string mot=Lexique::getInstance()-> _racine->_lettreAssociee + Lexique::getInstance()-> _racine->getEnfant(mot[i])->_lettreAssociee + Lexique::getInstance()->_racine->getEnfant(mot[i])-> _sousMotsValides[i];
								suggestions.pushback(mot);
								nbSuggestions++;

							}
					}
				else
					{
						Lexique::getInstance()->_racine=racineI;
						return suggestions;
					}

				Lexique::getInstance()->_racine=mot[i];
			}
	}

    suggestions.push_back("un");
//    suggestions.push_back("deux");
//    suggestions.push_back("trois");
//    suggestions.push_back("quatre");
//    suggestions.push_back("cinq");
//    suggestions.push_back("six");
//    suggestions.push_back("sept");
//    suggestions.push_back("huit");
//    suggestions.push_back("neuf");
//    suggestions.push_back("dix");

	Lexique::getInstance()->_racine=racineI;
    return suggestions;
}

vector<string> Correction::corriger(string mot)
{

    vector<string> motsCorriges;

	if (Lexique::getInstance()->existe(mot))
	{
        motsCorriges.push_back(mot);
	}
	else
	{
        for (unsigned int i = 0; i < mot.size(); i++)
		{
			char reserve = mot[i];
            for (int j = 0; j < 26; j++)
			{
				mot[i] = alphabet[j];
				if (Lexique::getInstance()->existe(mot))
					motsCorriges.push_back(mot);
			}
			mot[i] = reserve;
		}
		
	}

    return motsCorriges;
}

void Correction::creerCorrection() {
    delete _instance;
    _instance = new Correction();
}

void Correction::construireCorrection(const string& nomLexique) {
    Lexique::creerLexique(100);
    _connecter();
    Lexique::construireLexique(nomLexique);
}


// PRIVATE:

void Correction::_connecter() {
    connect(Lexique::getInstance(), SIGNAL(progressionConstruction(int)), _instance, SLOT(_progressionConstruction(int)));
    connect(Lexique::getInstance(), SIGNAL(constructionTerminee()),       _instance, SLOT(_constructionTerminee()));
}


// PRIVATE SLOTS:

void Correction::_progressionConstruction(int progressionPourcent) {
    emit progressionConstruction(progressionPourcent);
}

void Correction::_constructionTerminee() {
    emit constructionTerminee();
}
