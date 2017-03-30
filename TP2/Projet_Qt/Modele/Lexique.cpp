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

Lexique::Lexique(int longueurMax)
    : _LONGUEUR_MAX(longueurMax)
{
    _racine = new Noeud('\0');
}

Lexique::~Lexique()
{
	delete _racine;
}

void Lexique::creerLexique(int longueurMax)
{
    delete _instance;
    _instance = new Lexique(longueurMax);
}

void Lexique::construireLexique(const string &fichier) {
    _construireLexique(fichier);
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


        Noeud* racine = _instance->_racine;

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

Lexique* Lexique::getInstance()
{
	return _instance;
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



vector<string> Lexique::suggererMot(string mot, int nombreRestantATrouver){

    //se rendre au noeud du lexique qui correspond au mot tape
    //utilisation du code dans la premiere partie de la methode: existe
    int nbRestant=10;
    Noeud* noeudCourant;
    while(nbRestant>0 && noeudCourant!=nullptr )
    {

        bool peutExister = true;
        vector<string> suggestions;
        noeudCourant = _instance->_racine;
        const int MAX_ITERATIONS = std::min((int)mot.size(), _instance->_LONGUEUR_MAX);
        for (int i = 0; i < MAX_ITERATIONS && peutExister; ++i) {
            Noeud* enfant = noeudCourant->addEnfant(mot[i]);
            noeudCourant = enfant; 
            noeudCourant -> rechercherSousChainesValidesPourMot(mot, nombreRestantATrouver, suggestions);
        }

    }
 
    

    //appeller methode qui visite les sous-chaines du noeud courant
    

    //appeller meme methode sur les enfants de ce noeud
        //changer noeudCourant pour le prochain enfant
        //appeller methode

        
   
}
//appeller methode qui visite les sous-chaines d'un noeud
void Lexique::rechercherSousChainesValidesPourMot( string mot, int &nombreRestantATrouver, vector<string> &suggestions)
{
    //TODO: visiter les sous-chaines pour le noeud courant et les placer dans le vecteur "suggestions"
    for(int i =0; i<this->_sousMotsValides.size();i++)
        {   
            mot+=_sousMotsValides[i];
            suggestions.pushback(mot);
            nombreRestantATrouver--;
            mot-=_sousMotsValides
            
        }

}