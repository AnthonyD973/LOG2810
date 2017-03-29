#pragma once
#include <QObject>

#include "Lexique.h"


const char alphabet[] =  "qwertyuiopasdfghjklzxcvbnm";


class Correction : public QObject
{
    Q_OBJECT

public:
    Correction();
    virtual ~Correction();

    vector<string> motsSuggeres;
    vector<string> motsCorriges;
	std::vector<string> corrigerMot(string mot);

    static void creerCorrection(const string& nomFichier);
    inline static Correction* getInstance() { return _instance; }

private:
    void _connecter() const;

private:
    static Correction* _instance;

// Pour la barre de progression de la vue
signals:
    void progressionConstruction(int progressionPourcent);
    void progressionMinimisation(int progressionPourcent);
    void constructionTerminee();
    void minimisationTerminee();

private slots:
    void _progressionConstruction(int progressionPourcent);
    void _progressionMinimisation(int progressionPourcent);
    void _constructionTerminee();
    void _minimisationTerminee();
};
