# ifndef H_CLIENT
# define H_CLIENT

#include "Plateau.h"
#include "Piece.h"
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <iostream>
#include <string>
#include <cstdlib>

struct Deplacement{
	int xd;
	int yd;
	int xa;
	int ya;
	Piece* pd;
	Piece* pa;
};

class Client{

	private:
		Plateau* plateau;
		TCPsocket socket;
		bool macouleur;
		struct Deplacement dernier;

	public:
		
		Client(Plateau* p,string addresseServeur);
		~Client();
		
		// envois au serveur
		void envoiDeplacement(int x1, int y1, int x2, int y2);

		void envoyerPlateau();
		// envoie le plateau au serveur au débutr de la partie

		bool getMyColor();
		// renvoie la couleur du joueur

		void attendreDeplacementAdverse(); // METHODE BLOQUANTE
		// récupère xdépart, ydépart, xarrivée, yarrivée + eventuellement type Pièce attaquante (ou NULL) et traitement dans cette méthode
		
		struct Deplacement getDernierDeplacement();
		
};

# endif
