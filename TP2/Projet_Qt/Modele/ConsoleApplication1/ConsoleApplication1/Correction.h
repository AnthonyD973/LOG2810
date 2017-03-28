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

Correction::Correction()
{
}

Correction::~Correction()
{
}

std::vector<string> Correction::corrigerMot(string mot) 
{
	if (Lexique::getInstance()->existe(mot))
	{
		motsCorriges.push_back(mot);;
	}
	else
	{
		for (int i = 0;i < mot.size();i++)
		{
			char reserve = mot[i];
			for (int j = 0;j < 26;j++)
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

