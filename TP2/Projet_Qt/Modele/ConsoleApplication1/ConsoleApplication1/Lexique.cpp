
#include"Lexique.h"

 Lexique* Lexique::_instance = nullptr;

Lexique::Lexique()
{
	_racine = new Noeud(false, '\0');
}

Lexique::~Lexique()
{
	delete _racine;
}
void Lexique::creerLexique(string & fichier)
{
	delete _instance;
	_instance = new Lexique();

	_construireLexique(fichier, _instance);
	_minimiserLexique();		
}

void Lexique::_construireLexique(const string& fichier, Lexique& lexique)
{

	ifstream donnees(fichier, ios::in);  // 

	if (donnees)  // si l'ouverture a r�ussi
	{
		// instructions
		while (!donnees.eof())
		{
			//lire donnees
			string mot;
			donnees >> mot;
			for(int i=0; i<mot.size(); i++) //boucler sur les lettres du mot
			{
				if((_instance._racine->getEnfant(mot[i])==nullptr)
				{
					//TODO: ajout 
				}
				else
				{
					//TODO: ce qui se passe quand l'enfant existe deja
				}
			}
		}

		donnees.close();  // on ferme le fichier
	}
	else  // sinon
		cout << "Impossible d'ouvrir le fichier !" << endl;
}

void Lexique::_minimiserLexique()
{

}

bool Lexique::existe(string mot)
{
	for (int i = 0;i < _TOTALELEMENTS;i++)
	{
		if (lexique[i] == mot)
			return true;
	}
	return false;
}

Lexique* Lexique::getInstance()
{
	return _instance;
}