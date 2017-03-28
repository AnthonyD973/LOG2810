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
	class Noeud
	{
	public:
		Noeud(bool estFinal, char lettreAssociee);
		void addEnfant(Noeud* noeud);
		Noeud* getEnfant(char lettreAssociee); //retourne nullptr si enfant n'existe pas
	private:
		vector<Noeud*> _enfants;
		bool _estFinal;
		char _lettreAssociee;
	};

public:
	~Lexique();
	bool existe(string mot);
	vector<string>motsSuggeres;
	static void creerLexique(string & fichier);
	static Lexique* getInstance() ;



private:
	Lexique();
	string lexique[_TOTALELEMENTS];
	static Lexique* _instance;
	static void _construireLexique(const string& fichier, Lexique& lexique);
	void _minimiserLexique();
	Noeud* _racine;

};





