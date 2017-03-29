#pragma once

#include <QObject>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Lexique : public QObject
{
    Q_OBJECT

	class Noeud
	{
	public:
        Noeud(char lettreAssociee);
        ~Noeud();

        Noeud* addEnfant(char lettreAssociee); // Si l'enfant existe déjà, addEnfant est équivalent à getEnfant.
        Noeud* getEnfant(char lettreAssociee); // Retourne nullptr si enfant n'existe pas

        void addValide(const string& sousMot);
        bool estValide(const string& sousMot);

        inline char getLettreAssociee() const { return _lettreAssociee; }

	private:
		vector<Noeud*> _enfants;
        vector<string> _sousMotsValides;
		char _lettreAssociee;
	};

public:
    bool existe(const string& mot) const;

    static void creerLexique(int longueurMax);
    static void construireLexique(const string& fichier);
    static Lexique* getInstance();

private:
    Lexique(int longueurMax);
    virtual ~Lexique();

    static void _construireLexique(const string& fichier);

    const int _LONGUEUR_MAX;
    Noeud* _racine;

    static Lexique* _instance;

// Pour la barre de progression de la vue
signals:
    void progressionConstruction(int progressionPourcent);
    void progressionMinimisation(int progressionPourcent);
    void constructionTerminee();
};





