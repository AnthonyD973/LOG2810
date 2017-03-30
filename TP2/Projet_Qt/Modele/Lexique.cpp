/****************************************************************************
 * Fichier: Lexique.cpp
 * Auteurs: Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 * Date: 28 mars 2017
 * Description: Implémentation de la classe Lexique
 ****************************************************************************/

#include <QDebug>

#include "Lexique.h"


// ====================
// =  CLASSE LEXIQUE  =
// ====================

Lexique* Lexique::_instance = nullptr;

void Lexique::creerLexique(int longueurMax)
{
    delete _instance;
    _instance = new Lexique(longueurMax);
}

void Lexique::construireLexique(const string &fichier) {
    _construireLexique(fichier);
}

Lexique* Lexique::getInstance()
{
    return _instance;
}


bool Lexique::existe(const string& mot) const
{
    bool peutExister = true;

    Noeud* noeudCourant = _instance->_racine;
    const int MAX_ITERATIONS = std::min((int)mot.size(), _instance->_LONGUEUR_MAX);
    for (int i = 0; i < MAX_ITERATIONS && peutExister; ++i) {
        noeudCourant = noeudCourant->getEnfant(mot[i]);
        peutExister = (noeudCourant != nullptr);
    }

    bool existe;
    if (peutExister) {
         existe = noeudCourant->estValide(mot.substr(MAX_ITERATIONS, string::npos));
    }
    else {
        existe = false;
    }

    return existe;
}

vector<string> Lexique::suggerer(const string& mot, int nombreATrouver) {

    //se rendre au noeud du lexique qui correspond au mot tape
    //utilisation du code dans la premiere partie de la methode: existe
    Noeud* noeudCourant = _racine;

    const int MAX_ITERATIONS = std::min((int)mot.size(), _instance->_LONGUEUR_MAX);
    int hauteur;
    for (hauteur = 0; hauteur < MAX_ITERATIONS && noeudCourant != nullptr; ++hauteur) {
        noeudCourant = noeudCourant->getEnfant(mot[hauteur]);
    }

    vector<string> suggestions;
    if (noeudCourant != nullptr) {
        suggestions = noeudCourant->recherchePrefixe(mot, hauteur, nombreATrouver);
    }

    return suggestions;

}


// PRIVATE:

Lexique::Lexique(int longueurMax)
    : _LONGUEUR_MAX(longueurMax)
{
    _racine = new Noeud('\0');
}

Lexique::~Lexique()
{
    delete _racine;
}


void Lexique::_construireLexique(const string& fichier)
{

    ifstream donnees(fichier);

    if (donnees)  // si l'ouverture a réussi
	{
        // Compter le nombre de mots afin de pouvoir déterminer la
        // progression de la création de l'automate.
        int nombreDeMots = 0;
        string motPantin;
        while (donnees >> motPantin) {
            ++nombreDeMots;
        }

        donnees.clear();
        donnees.seekg(0); // Se remettre au début du fichier

        int nombreDeMotsTraites = 0;
        int progressionPourcent = -1;


		// instructions
		while (!donnees.eof())
        {
            // Lire donnees
			string mot;
			donnees >> mot;

            Noeud* noeudCourant = _instance->_racine;
            const int MAX_ITERATIONS = std::min((int)mot.size(), _instance->_LONGUEUR_MAX);
            for(int i = 0; i < MAX_ITERATIONS; i++) // boucler sur les lettres du mot
            {
                Noeud* enfant = noeudCourant->addEnfant(mot[i]);
                noeudCourant = enfant;
			}

            if (mot != "") {
                noeudCourant->addValide(mot.substr(MAX_ITERATIONS, string::npos));
            }

            // Avertir la vue de la progression
            ++nombreDeMotsTraites;
            int nouvelleProgression  = (100 * nombreDeMotsTraites) / nombreDeMots;
            if (progressionPourcent != nouvelleProgression) {
                progressionPourcent  = nouvelleProgression;
                emit _instance->progressionConstruction(progressionPourcent);
            }
        }

        donnees.close(); // on ferme le fichier
	}
	else  // sinon
        qDebug() << "Impossible d'ouvrir le fichier !" << endl;

    emit _instance->constructionTerminee();
}


// ====================
// =   CLASSE NOEUD   =
// ====================

Lexique::Noeud::Noeud(char lettreAssociee)
    : _lettreAssociee(lettreAssociee)
{ }

Lexique::Noeud::~Noeud() {
    for (Noeud* n : _enfants) {
        delete n;
    }
}


Lexique::Noeud* Lexique::Noeud::addEnfant(char lettreAssociee) {
    Noeud* enfant = getEnfant(lettreAssociee);

    if (enfant == nullptr) {
        enfant = new Noeud(lettreAssociee);
        _enfants.push_back(enfant);
    }

    return enfant;
}

Lexique::Noeud* Lexique::Noeud::getEnfant(char lettreAssociee) {
    Noeud* enfant = nullptr;

    for (Noeud* e : _enfants) {
        if (e->getLettreAssociee() == lettreAssociee) {
            enfant = e;
            break;
        }
    }

    return enfant;
}


void Lexique::Noeud::addValide(const string& sousMot) {
    _sousMotsValides.push_back(sousMot);
}

bool Lexique::Noeud::estValide(const string& sousMot) {
    bool estValide = false;

    for (unsigned int i = 0; i < _sousMotsValides.size() && !estValide; ++i) {
        if (_sousMotsValides[i] == sousMot) {
            estValide = true;
        }
    }

    return estValide;
}

vector<string> Lexique::Noeud::recherchePrefixe(
        const string& mot,
        int hauteurCourante,
        int nombreATrouver) {

    vector<string> suggestions =
            _rechercherChainesValides(
                mot.substr(0, hauteurCourante),
                mot.substr(hauteurCourante, string::npos),
                nombreATrouver);

    for (Noeud* enfant : _enfants) {
        string motEnfant =
            (hauteurCourante == mot.size()) ? mot + enfant->getLettreAssociee() : mot;

        vector<string> nouveauxMots =
            enfant->recherchePrefixe(
                motEnfant,
                hauteurCourante + 1,
                nombreATrouver - suggestions.size());

        suggestions.reserve(suggestions.size() + nouveauxMots.size());
        std::move(
            nouveauxMots.begin(),
            nouveauxMots.end(),
            std::inserter(suggestions, suggestions.end()));
    }

    return suggestions;
}


// PRIVATE:

vector<string> Lexique::Noeud::_rechercherChainesValides(const string& debutMot, const string& finMot, int nombreATrouver) {
    vector<string> motsValides;

    unsigned int i = 0;
    while(i < _sousMotsValides.size() && (int)motsValides.size() < nombreATrouver) {
        // N'ajouter que les sous-chaînes qui commence par la fin du mot
        if (_sousMotsValides[i].substr(0, finMot.size()) == finMot) {
            motsValides.push_back(debutMot + _sousMotsValides[i]);
        }

        ++i;
    }

    return motsValides;
}
