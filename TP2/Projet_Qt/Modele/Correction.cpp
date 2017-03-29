#include "Correction.h"

Correction* Correction::_instance = nullptr;

Correction::Correction()
{ }

Correction::~Correction()
{ }

std::vector<string> Correction::corrigerMot(string mot) 
{
	if (Lexique::getInstance()->existe(mot))
	{
        motsCorriges.push_back(mot);
	}
	else
	{
        for (int i = 0; i < mot.size(); i++)
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
    Lexique::creerLexique(nomLexique, 100);
}


// PRIVATE:

void Correction::_connecter() const {
    connect(Lexique::getInstance(), SIGNAL(progressionConstruction(int)), SLOT(_progressionConstruction(int)));
    connect(Lexique::getInstance(), SIGNAL(progressionMinimisation(int)), SLOT(_progressionMinimisation(int)));
    connect(Lexique::getInstance(), SIGNAL(constructionTerminee()),       SLOT(_constructionTerminee(int)));
    connect(Lexique::getInstance(), SIGNAL(minimisationTerminee()),       SLOT(_minimisationTerminee(int)));
}


// PRIVATE SLOTS:

void Correction::_progressionConstruction(int progressionPourcent) {
    emit progressionConstruction(progressionPourcent);
}

void Correction::_progressionMinimisation(int progressionPourcent) {
    emit progressionMinimisation(progressionPourcent);
}

void Correction::_constructionTerminee() {
    emit constructionTerminee();
}

void Correction::_minimisationTerminee() {
    emit minimisationTerminee();
}
