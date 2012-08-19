#ifndef H_SERVEUR
#define H_SERVEUR

#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Plateau.h"
#include <sstream>

#define ETAT_CONN_JOUEURS 			1
#define ETAT_PLATEAUX_JOUEURS 		2
#define ETAT_ACTION_JOUEUR_RED 		3
#define ETAT_ACTION_JOUEUR_BLUE		4
#define ETAT_GAMEOVER	 			5
#define ERROR						6

int lancerServeur(void* data);
void affichePlateau(Plateau *plateau);

# endif
