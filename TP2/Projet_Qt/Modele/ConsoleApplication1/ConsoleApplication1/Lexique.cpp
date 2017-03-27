
#include"Lexique.h"

 Lexique* Lexique::_instance = nullptr;

Lexique::Lexique()
{

}

Lexique::~Lexique()
{
}
void Lexique::creerLexique(string & fichier)
{
	

	ifstream donnees(fichier, ios::in);  // 

	if (donnees)  // si l'ouverture a réussi
	{
		delete _instance;
		_instance = new Lexique();
		// instructions
		while (!donnees.eof())
		{
			for (int i = 0;i < _TOTALELEMENTS;i++)
			{
				getline(donnees, _instance->lexique[i]);
			}

		}

		donnees.close();  // on ferme le fichier
	}
	else  // sinon
		cout << "Impossible d'ouvrir le fichier !" << endl;




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