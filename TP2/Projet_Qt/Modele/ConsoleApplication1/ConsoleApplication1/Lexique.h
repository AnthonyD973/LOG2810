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
	
	~Lexique();
	bool existe(string mot);
	vector<string>motsSuggeres;
	static void creerLexique(string & fichier);
	static Lexique* getInstance() ;



private:
	Lexique();
	string  lexique[_TOTALELEMENTS];
	static Lexique*_instance;

};





