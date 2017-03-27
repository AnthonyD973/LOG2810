#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include <fstream>
#include <vector>


using namespace std;

const int _TOTALELEMENTS = 22000;


class Lexique
{
public:
	Lexique();
	~Lexique();
	bool existe(string mot);
	vector<string>motsSuggeres;
	void creerLexique(string & fichier);



private:
	string  lexique[_TOTALELEMENTS];

};

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
		// instructions
		while (!donnees.eof())
		{
			for (int i = 0;i < _TOTALELEMENTS;i++)
			{
				getline(donnees,lexique[i]);
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
		
	}
}





