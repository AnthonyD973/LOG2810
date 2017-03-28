
#include"Lexique.h"


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
void Lexique::creerLexique(const string & fichier, int longueurMax)
{
	delete _instance;
    _instance = new Lexique(longueurMax);

    _construireLexique(fichier);
	_minimiserLexique();		
}

void Lexique::_construireLexique(const string& fichier)
{

    ifstream donnees(fichier);

    if (donnees)  // si l'ouverture a réussi
	{
		// instructions
		while (!donnees.eof())
		{
			//lire donnees
			string mot;
			donnees >> mot;

            Noeud* noeudCourant = _instance->_racine;
            const int MAX_ITERATIONS = std::min(mot.size(), _instance->_LONGUEUR_MAX);
            for(int i = 0; i < MAX_ITERATIONS; i++) // boucler sur les lettres du mot
			{
                Noeud* enfant = noeudCourant->getEnfant(mot[i]);

                if(enfant == nullptr)
				{
                    // Ajout de l'enfant
                    enfant = new Noeud(mot[i]);
                    noeudCourant->addEnfant(enfant);
                }

                noeudCourant = enfant;
			}

            noeudCourant->addMotValide(mot.substr(MAX_ITERATIONS-1, string::npos));
		}

		donnees.close();  // on ferme le fichier
	}
	else  // sinon
		cout << "Impossible d'ouvrir le fichier !" << endl;
}

void Lexique::_minimiserLexique()
{

}

bool Lexique::existe(const string& mot)
{
    bool peutExister = true;

    Noeud* noeudCourant = _instance->_racine;
    const int MAX_ITERATIONS = std::min(mot.size(), _instance->_LONGUEUR_MAX);
    for (int i = 0; i < MAX_ITERATIONS && peutExister; ++i) {
        Noeud* enfant = noeudCourant->addEnfant(mot[i]);
        noeudCourant = enfant;
    }

    bool existe;
    if (peutExister) {
         existe = noeudCourant->estValide(mot.substr(MAX_ITERATIONS-1, string::npos));
    }
    else {
        existe = false;
    }

    return peutExister;
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


Noeud* Lexique::Noeud::addEnfant(char lettreAssociee) {
    Node* enfant = getEnfant(lettreAssociee);

    if (enfant != nullptr) {
        enfant = new Noeud(lettreAssociee);
        _enfants.push_back(enfant);
    }
    else {
        delete noeud;
    }

    return enfant;
}

Noeud* Lexique::Noeud::getEnfant(char lettreAssociee) {
    Noeud enfant = nullptr;

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

    for (int i = 0; i < _sousMotsValides.size() && !estValide; ++i) {
        if (_sousMotsValides[i] == sousMot) {
            estValide = true;
        }
    }

    return estValide;
}
