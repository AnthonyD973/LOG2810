/****************************************************************************
 * Fichier: Correction.h
 * Auteurs: Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 * Date: 28 mars 2017
 * Description: Description de la classe Correction
 ****************************************************************************/

#pragma once
#include"Lexique.h"


const char alphabet[] =  "qwertyuiopasdfghjklzxcvbnm" ;


class Correction
{
public:
	Correction();
	~Correction();

	vector<string>motsSuggeres;
	vector<string>motsCorriges;
	std::vector<string> corrigerMot(string mot);


private:
	Lexique* lexique;

};