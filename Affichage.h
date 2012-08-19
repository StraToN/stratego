#ifndef H_AFFICHAGE
#define H_AFFICHAGE

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include <string>

#include "constantes.h"
#include "Plateau.h"
#include "Client.h"

class Affichage{
	private :
		SDL_Surface *ecran;
		SDL_Surface *menu_fond;
		SDL_Surface *menu_creer;
		SDL_Rect menu_creer_pos;
		SDL_Surface *menu_rejoindre;
		SDL_Rect menu_rejoindre_pos;
		SDL_Surface *menu_options;
		SDL_Rect menu_options_pos;
		SDL_Surface *menu_credits;
		SDL_Rect menu_credits_pos;
		SDL_Surface *menu_quitter;
		SDL_Rect menu_quitter_pos;
		SDL_Surface *piece_rouge;
		SDL_Surface *piece_bleu;
		SDL_Surface *piece_rouge_selection;
		SDL_Surface *piece_bleu_selection;
		SDL_Surface *jeu_fond;
		SDL_Surface *jeu_plateau;
		SDL_Rect jeu_plateau_pos;
		SDL_Surface *piece_bombe;
		SDL_Surface *piece_espion;
		SDL_Surface *piece_eclaireur;
		SDL_Surface *piece_demineur;
		SDL_Surface *piece_sergent;
		SDL_Surface *piece_lieutenant;
		SDL_Surface *piece_capitaine;
		SDL_Surface *piece_commandant;
		SDL_Surface *piece_colonel;
		SDL_Surface *piece_general;
		SDL_Surface *piece_marechal;
		SDL_Surface *piece_drapeau;
		static const int MENU_CREER=1,MENU_REJOINDRE=2,MENU_OPTIONS=3,MENU_CREDITS=4,MENU_QUITTER=5;
		void initialiserSDL();
		void chargerImages();
		void afficherMenu();
		void menuEventsManager();
		void jeuEventsManager(std::string adresse);
		void ecranConnexion();
		void affichePlateau();
		void affichePiece(Piece * piece,int x,int y,SDL_Surface* pl);
		void updateMenu(int currently_selected);
		void showError(int numerror);
		void writeTTFText(std::string text,int x,int y,SDL_Surface* fond);
		Plateau* plateau;
		Client* cl;
		int selectionx;
		int selectiony;
		TTF_Font *police;
		void affichePieceSurface(SDL_Surface *couleur,SDL_Surface *type,int x,int y,SDL_Surface* surface);
		char pieceselection;
		static const int x1=730,x2=860,y1=57,h=30,l=30;
	public :
		Affichage();
};

# endif
