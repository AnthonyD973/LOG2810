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