#ifndef H_AFFICHAGE_TEXTE
#define H_AFFICHAGE_TEXTE

#include <SDL/SDL_net.h>

#include <iostream>
#include <string>

#include "constantes.h"
#include "Plateau.h"
#include "Client.h"

class AffichageTexte{
	private :
		static const int MENU_CREER=1,MENU_REJOINDRE=2,MENU_OPTIONS=3,MENU_CREDITS=4,MENU_QUITTER=5;
		void afficherMenu();
		void creerPartie();
		void rejoindrePartie();
		void affichePlateau();
		void connecterPartie(std::string ipserveur);
		Plateau* plateau;
		Client* cl;
	public :
		AffichageTexte();
};

# endif
