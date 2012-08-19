#include "Affichage.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_thread.h>
#include <iostream>
#include <string>
#include "Serveur.h"


Affichage::Affichage(){
	initialiserSDL();
	chargerImages();
	afficherMenu();
	menuEventsManager();
}

void Affichage::initialiserSDL() {
	// initialisation de SDL
	if (SDL_Init(SDL_INIT_VIDEO /* | SDL_INIT_TIMER | SDL_INIT_AUDIO */) == -1){
		cerr<<"Erreur d'initialisation de la SDL : "<<SDL_GetError()<<endl;
		exit(EXIT_FAILURE);
	}
	
	ecran = NULL;
	// récupération de la surface de base (largeur,hauteur,nombre de couleur(sur 32 bits),mode de vidéo(accélération graphique|double buffer))
	ecran = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	
	if (ecran == NULL){
		cerr<<"Impossible de charger le mode vidéo : "<<SDL_GetError()<<endl;
		exit(EXIT_FAILURE);
   	}
	
	// définition du titre de la fenêtre SDL (l'icone n'existant pas pour le moment on met à null)
	SDL_WM_SetCaption("Stratego", NULL);
	
	if(TTF_Init() == -1){
		std::cerr<<"Erreur d'initialisation de TTF_Init : "<<TTF_GetError()<<std::endl;
		exit(EXIT_FAILURE);
	}
	
	police = TTF_OpenFont("polices/angelina.ttf", 50);
	
}

void Affichage::chargerImages(){
	menu_fond=IMG_Load("./images/menuprincipal/menuprincipal.png");
	menu_creer=IMG_Load("./images/menuprincipal/creer.png");
	menu_rejoindre=IMG_Load("./images/menuprincipal/rejoindre.png");
	menu_options=IMG_Load("./images/menuprincipal/options.png");
	menu_credits=IMG_Load("./images/menuprincipal/credits.png");
	menu_quitter=IMG_Load("./images/menuprincipal/quitter.png");
	piece_rouge=IMG_Load("./images/piece.png");
	piece_bleu=IMG_Load("./images/piece2.png");
	piece_rouge_selection=IMG_Load("./images/pieceselection.png");
	piece_bleu_selection=IMG_Load("./images/piece2selection.png");
	jeu_fond=IMG_Load("./images/fond.png");
	jeu_plateau=IMG_Load("./images/plateau.png");
	jeu_plateau_pos.x=50;
	jeu_plateau_pos.y=50;
	piece_bombe=IMG_Load("./images/bombe.png");
	piece_espion=IMG_Load("./images/1-espion.png");
	piece_eclaireur=IMG_Load("./images/2-eclaireur.png");
	piece_demineur=IMG_Load("./images/3-demineur.png");
	piece_sergent=IMG_Load("./images/4-sergent.png");
	piece_lieutenant=IMG_Load("./images/5-lieutenant.png");
	piece_capitaine=IMG_Load("./images/6-capitaine.png");
	piece_commandant=IMG_Load("./images/7-commandant.png");
	piece_colonel=IMG_Load("./images/8-colonel.png");
	piece_general=IMG_Load("./images/9-general.png");
	piece_marechal=IMG_Load("./images/10-marechal.png");
	piece_drapeau=IMG_Load("./images/drapeau.png");
}

void Affichage::afficherMenu() {
	SDL_Rect position;
	
	// on affiche l'image sur le fond (l'image,la taille,l'écran,la position sur l'écran)
	menu_creer_pos.x = ecran->w / 2 - menu_creer->w / 2;
	menu_creer_pos.y = 2*(ecran->h / 10) - menu_creer->h / 2 + 100;
	SDL_BlitSurface(menu_creer, NULL, menu_fond, &menu_creer_pos);
	
	menu_rejoindre_pos.x = ecran->w / 2 - menu_rejoindre->w / 2;
	menu_rejoindre_pos.y = 3*(ecran->h / 10) - menu_rejoindre->h / 2 + 100;
	SDL_BlitSurface(menu_rejoindre, NULL, menu_fond, &menu_rejoindre_pos);
	
	menu_options_pos.x = ecran->w / 2 - menu_options->w / 2;
	menu_options_pos.y = 4*(ecran->h / 10) - menu_options->h / 2 + 100;
	SDL_BlitSurface(menu_options, NULL, menu_fond, &menu_options_pos);
	
	menu_credits_pos.x = ecran->w / 2 - menu_credits->w / 2;
	menu_credits_pos.y = 5*(ecran->h / 10) - menu_credits->h / 2 + 100;
	SDL_BlitSurface(menu_credits, NULL, menu_fond, &menu_credits_pos);
	
	menu_quitter_pos.x = ecran->w / 2 - menu_quitter->w / 2;
	menu_quitter_pos.y = 6*(ecran->h / 10) - menu_quitter->h / 2 + 100;
	SDL_BlitSurface(menu_quitter, NULL, menu_fond, &menu_quitter_pos);
	
	position.x = 0;
	position.y = 0;	
	SDL_BlitSurface(menu_fond, NULL, ecran, &position);

	SDL_Flip(ecran);
}

void Affichage::menuEventsManager(){
	bool continuer = true;
	SDL_Event event;
	SDL_Rect positionred, positionblue;
	
	int currently_selected = MENU_CREER; // bouton créer = selection 1
	
	positionred.x = ecran->w / 2 - 300;
	positionred.y = (1+currently_selected)*(ecran->h / 10) - piece_rouge->h / 2 + 100;
	// on affiche l'image sur le fond (l'image,la taille,l'écran,la position sur l'écran)
	SDL_BlitSurface(piece_rouge, NULL, ecran, &positionred);
	
	positionblue.x = ecran->w / 2 + 300 - piece_rouge->w;
	positionblue.y = positionred.y;
	SDL_BlitSurface(piece_bleu, NULL, ecran, &positionblue);
	
	SDL_Flip(ecran);
	
	SDL_EnableKeyRepeat(150, 100);
	while (continuer){
		// Attente d'un evenement
		SDL_WaitEvent(&event);	
		
		// Gestion des événements
		switch (event.type) {
			case SDL_QUIT:
				continuer = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {	
					case SDL_BUTTON_LEFT:
						switch (currently_selected) {
							case MENU_CREER:
								SDL_Thread *mon_thread;
								mon_thread=SDL_CreateThread(lancerServeur, NULL);
								SDL_Delay(100);
								jeuEventsManager("127.0.0.1");
								updateMenu(currently_selected);
								break;
							case MENU_REJOINDRE:
								ecranConnexion();
								updateMenu(currently_selected);
								break;
							case MENU_OPTIONS:
								
								break;
							case MENU_CREDITS:
								
								break;
							case MENU_QUITTER:
								exit(EXIT_SUCCESS);
								break;
							default:
								break;
						}
						break;
					default:
							break;
				}

				break;
				
			case SDL_MOUSEMOTION:
				if(event.motion.y<menu_rejoindre_pos.y){
					if(currently_selected !=MENU_CREER){
						currently_selected =MENU_CREER;
						updateMenu(currently_selected);
					}
				}else if(event.motion.y<menu_options_pos.y){
					if(currently_selected !=MENU_REJOINDRE){
						currently_selected =MENU_REJOINDRE;
						updateMenu(currently_selected);
					}
				}else if(event.motion.y<menu_credits_pos.y){
					if(currently_selected !=MENU_OPTIONS){
						currently_selected =MENU_OPTIONS;
						updateMenu(currently_selected);
					}
				}else if(event.motion.y<menu_quitter_pos.y){
					if(currently_selected !=MENU_CREDITS){
						currently_selected =MENU_CREDITS;
						updateMenu(currently_selected);
					}
				}else if(currently_selected !=MENU_QUITTER){
					currently_selected =MENU_QUITTER;
					updateMenu(currently_selected);
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_RIGHT:
					case SDLK_DOWN:
						currently_selected = currently_selected % 5 + 1;
						break;
					case SDLK_LEFT:
					case SDLK_UP:
						currently_selected = 5 - (((5 - currently_selected) + 1) % 5);
						break;
					case SDLK_ESCAPE:
						exit(EXIT_SUCCESS);
						break;
					case SDLK_RETURN:
						switch(currently_selected){
							case MENU_CREER:
								SDL_Thread *mon_thread;
								mon_thread=SDL_CreateThread(lancerServeur, NULL);
								SDL_Delay(100);
								jeuEventsManager("127.0.0.1");
								updateMenu(currently_selected);
								break;
							case MENU_REJOINDRE:
								ecranConnexion();
								updateMenu(currently_selected);
								break;
							case MENU_OPTIONS:
								
								break;
							case MENU_CREDITS:
								
								break;
							case MENU_QUITTER:
								exit(EXIT_SUCCESS);
								break;
							default:
								break;
						}
						break;
					default:
						break;
				}
				updateMenu(currently_selected);
				break;
			default:
				break;
		}
	}
}

void Affichage::ecranConnexion(){
	std::string adresse;
	
	{
	
	SDL_Rect position;
	SDL_Surface* fond=SDL_ConvertSurface(jeu_fond,jeu_fond->format,SDL_SRCALPHA);
	writeTTFText("Entrez l'adresse du serveur:",310,330,fond);
	position.x=0;
	position.y=0;
	SDL_BlitSurface(fond, NULL, ecran, &position);
	SDL_Flip(ecran);
	
	}
	
	bool continuer=true;
	while (continuer){
		SDL_Event event;
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				exit(EXIT_SUCCESS);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_RETURN:
					case SDLK_KP_ENTER:
						continuer = false;
						break;
					case SDLK_0:
					case SDLK_KP0:
						adresse+="0";
						break;
					case SDLK_1:
					case SDLK_KP1:
						adresse+="1";
						break;
					case SDLK_2:
					case SDLK_KP2:
						adresse+="2";
						break;
					case SDLK_3:
					case SDLK_KP3:
						adresse+="3";
						break;
					case SDLK_4:
					case SDLK_KP4:
						adresse+="4";
						break;
					case SDLK_5:
					case SDLK_KP5:
						adresse+="5";
						break;
					case SDLK_6:
					case SDLK_KP6:
						adresse+="6";
						break;
					case SDLK_7:
					case SDLK_KP7:
						adresse+="7";
						break;
					case SDLK_8:
					case SDLK_KP8:
						adresse+="8";
						break;
					case SDLK_9:
					case SDLK_KP9:
						adresse+="9";
						break;
					case SDLK_PERIOD:
					case SDLK_KP_PERIOD:
						adresse+=".";
						break;
					case SDLK_BACKSPACE:
						adresse=adresse.substr(0,adresse.size()-1);
						break;
					default:
						break;
				}
				SDL_Rect position;
				SDL_Surface* fond=SDL_ConvertSurface(jeu_fond,jeu_fond->format,SDL_SRCALPHA);
				writeTTFText("Entrez l'adresse du serveur:",310,330,fond);
				writeTTFText(adresse,450,380,fond);
				position.x=0;
				position.y=0;
				SDL_BlitSurface(fond, NULL, ecran, &position);
				SDL_Flip(ecran);
				break;
		}
	}
	jeuEventsManager(adresse);
}

void Affichage::updateMenu(int currently_selected){
	SDL_Rect positionred, positionblue;
	positionred.x = ecran->w / 2 - 300;
	positionblue.x = ecran->w / 2 + 300 - piece_rouge->w;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;	
	SDL_BlitSurface(menu_fond, NULL, ecran, &position);
	positionred.y = (1+currently_selected)*(ecran->h / 10) - piece_rouge->h / 2 + 100;
	positionblue.y = positionred.y;
	SDL_BlitSurface(piece_bleu, NULL, ecran, &positionblue);
	SDL_BlitSurface(piece_rouge, NULL, ecran, &positionred);
	SDL_Flip(ecran);
}

void Affichage::jeuEventsManager(std::string adresse){
	
	SDL_Rect position;
	
	/////////////////////////////
	
	plateau=new Plateau();
	
	cl=new Client(plateau,adresse);
	
	bool rempli = false;
	
	selectionx=-1;
	selectiony=-1;
	
	#ifdef REMPLISSAGEAUTO
	#define REMPLISSAGEAUTO
	
	if(cl->getMyColor()==RED){
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,0,0);
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,1,0);
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,2,0);
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,3,0);
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,4,0);
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,5,0);
		plateau->setPiecePosition(cl->getMyColor(),C_COMMANDANT,6,0);
		plateau->setPiecePosition(cl->getMyColor(),C_COLONEL,7,0);
		plateau->setPiecePosition(cl->getMyColor(),C_COMMANDANT,8,0);
		plateau->setPiecePosition(cl->getMyColor(),C_COMMANDANT,9,0);
		plateau->setPiecePosition(cl->getMyColor(),C_CAPITAINE,0,1);
		plateau->setPiecePosition(cl->getMyColor(),C_CAPITAINE,1,1);
		plateau->setPiecePosition(cl->getMyColor(),C_CAPITAINE,2,1);
		plateau->setPiecePosition(cl->getMyColor(),C_LIEUTENANT,3,1);
		plateau->setPiecePosition(cl->getMyColor(),C_LIEUTENANT,4,1);
		plateau->setPiecePosition(cl->getMyColor(),C_LIEUTENANT,5,1);
		plateau->setPiecePosition(cl->getMyColor(),C_SERGENT,6,1);
		plateau->setPiecePosition(cl->getMyColor(),C_SERGENT,7,1);
		plateau->setPiecePosition(cl->getMyColor(),C_SERGENT,8,1);
		plateau->setPiecePosition(cl->getMyColor(),C_DEMINEUR,9,1);
		plateau->setPiecePosition(cl->getMyColor(),C_DEMINEUR,0,2);
		plateau->setPiecePosition(cl->getMyColor(),C_DEMINEUR,1,2);
		plateau->setPiecePosition(cl->getMyColor(),C_DEMINEUR,2,2);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,3,2);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,4,2);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,5,2);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,6,2);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,7,2);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,8,2);
		plateau->setPiecePosition(cl->getMyColor(),C_ESPION,9,2);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,0,3);
		plateau->setPiecePosition(cl->getMyColor(),C_MARECHAL,1,3);
		plateau->setPiecePosition(cl->getMyColor(),C_GENERAL,2,3);
		plateau->setPiecePosition(cl->getMyColor(),C_COLONEL,3,3);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,4,3);
		plateau->setPiecePosition(cl->getMyColor(),C_CAPITAINE,5,3);
		plateau->setPiecePosition(cl->getMyColor(),C_LIEUTENANT,6,3);
		plateau->setPiecePosition(cl->getMyColor(),C_SERGENT,7,3);
		plateau->setPiecePosition(cl->getMyColor(),C_DEMINEUR,8,3);
		plateau->setPiecePosition(cl->getMyColor(),C_DRAPEAU,9,3);
		
	}else{
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,0,9);
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,1,9);
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,2,9);
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,3,9);
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,4,9);
		plateau->setPiecePosition(cl->getMyColor(),C_BOMBE,5,9);
		plateau->setPiecePosition(cl->getMyColor(),C_ESPION,6,9);
		plateau->setPiecePosition(cl->getMyColor(),C_COLONEL,7,9);
		plateau->setPiecePosition(cl->getMyColor(),C_COMMANDANT,8,9);
		plateau->setPiecePosition(cl->getMyColor(),C_COMMANDANT,9,9);
		plateau->setPiecePosition(cl->getMyColor(),C_CAPITAINE,0,8);
		plateau->setPiecePosition(cl->getMyColor(),C_CAPITAINE,1,8);
		plateau->setPiecePosition(cl->getMyColor(),C_CAPITAINE,2,8);
		plateau->setPiecePosition(cl->getMyColor(),C_LIEUTENANT,3,8);
		plateau->setPiecePosition(cl->getMyColor(),C_LIEUTENANT,4,8);
		plateau->setPiecePosition(cl->getMyColor(),C_LIEUTENANT,5,8);
		plateau->setPiecePosition(cl->getMyColor(),C_SERGENT,6,8);
		plateau->setPiecePosition(cl->getMyColor(),C_SERGENT,7,8);
		plateau->setPiecePosition(cl->getMyColor(),C_SERGENT,8,8);
		plateau->setPiecePosition(cl->getMyColor(),C_DEMINEUR,9,8);
		plateau->setPiecePosition(cl->getMyColor(),C_DEMINEUR,0,7);
		plateau->setPiecePosition(cl->getMyColor(),C_DEMINEUR,1,7);
		plateau->setPiecePosition(cl->getMyColor(),C_DEMINEUR,2,7);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,3,7);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,4,7);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,5,7);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,6,7);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,7,7);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,8,7);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,9,7);
		plateau->setPiecePosition(cl->getMyColor(),C_DRAPEAU,0,6);
		plateau->setPiecePosition(cl->getMyColor(),C_MARECHAL,1,6);
		plateau->setPiecePosition(cl->getMyColor(),C_GENERAL,2,6);
		plateau->setPiecePosition(cl->getMyColor(),C_COLONEL,3,6);
		plateau->setPiecePosition(cl->getMyColor(),C_COMMANDANT,4,6);
		plateau->setPiecePosition(cl->getMyColor(),C_CAPITAINE,5,6);
		plateau->setPiecePosition(cl->getMyColor(),C_LIEUTENANT,6,6);
		plateau->setPiecePosition(cl->getMyColor(),C_SERGENT,7,6);
		plateau->setPiecePosition(cl->getMyColor(),C_DEMINEUR,8,6);
		plateau->setPiecePosition(cl->getMyColor(),C_ECLAIREUR,9,6);
	}
	
	std::cout<<"Le plateau a été rempli automatiquement."<<std::endl;
	
	rempli=true;
	
	#endif
	
	//remplissage non automatique
	pieceselection='\0';
	
	
	affichePlateau();
	
	if(cl->getMyColor()==RED){
		writeTTFText("Vous etes rouge.",200,5,ecran);
	}else{
		writeTTFText("Vous etes bleu.",200,5,ecran);
	}
	
	SDL_Flip(ecran);
	
	
	while (!rempli){
		SDL_Event event;
		SDL_WaitEvent(&event);	
		switch (event.type) {
			case SDL_QUIT:
				exit(EXIT_SUCCESS);
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						int abscisse,ordonnee;
						abscisse=(event.button.x-jeu_plateau_pos.x-1)/57;
						ordonnee=9-((event.button.y-jeu_plateau_pos.y-1)/57);
						
						//
						if(!plateau->checkForbiddenLocation(abscisse,ordonnee)&&isInArea(cl->getMyColor(),ordonnee)){
							if(plateau->checkFreeLocation(abscisse,ordonnee)){
							
								if(pieceselection!='\0'){
									plateau->setPiecePosition(cl->getMyColor(),pieceselection,abscisse,ordonnee);
									
									if(plateau->nbPiecesRestantes(cl->getMyColor(),charToId(pieceselection))==0){
										pieceselection='\0';
									}
									
									if(plateau->nbTotalPiecesRestantes(cl->getMyColor())==0){
										rempli=true;
									}
									
								}else{
									std::cout<<"Aucune piece n'a été selectionnée."<<std::endl;
								}
								
							}else{
								std::cout<<"La place n'est pas vide."<<std::endl;
							}
						}else{
							
							///
							
							if(cl->getMyColor()==RED&&event.button.x>x1+l&&event.button.x<x1+l+57){
								if(event.button.y>h&&event.button.y<h+57){
									pieceselection=C_DRAPEAU;
								}else if(event.button.y>h+y1&&event.button.y<h+y1+57){
									pieceselection=C_MARECHAL;
								}else if(event.button.y>h+y1*2&&event.button.y<h+y1*2+57){
									pieceselection=C_GENERAL;
								}else if(event.button.y>h+y1*3&&event.button.y<h+y1*3+57){
									pieceselection=C_COLONEL;
								}else if(event.button.y>h+y1*4&&event.button.y<h+y1*4+57){
									pieceselection=C_COMMANDANT;
								}else if(event.button.y>h+y1*5&&event.button.y<h+y1*5+57){
									pieceselection=C_CAPITAINE;
								}else if(event.button.y>h+y1*6&&event.button.y<h+y1*6+57){
									pieceselection=C_LIEUTENANT;
								}else if(event.button.y>h+y1*7&&event.button.y<h+y1*7+57){
									pieceselection=C_SERGENT;
								}else if(event.button.y>h+y1*8&&event.button.y<h+y1*8+57){
									pieceselection=C_DEMINEUR;
								}else if(event.button.y>h+y1*9&&event.button.y<h+y1*9+57){
									pieceselection=C_ECLAIREUR;
								}else if(event.button.y>h+y1*10&&event.button.y<h+y1*10+57){
									pieceselection=C_ESPION;
								}else if(event.button.y>h+y1*11&&event.button.y<h+y1*11+57){
									pieceselection=C_BOMBE;
								}else{
									pieceselection='\0';
								}
							}else if(cl->getMyColor()==BLUE&&event.button.x>x2+l&&event.button.x<x2+l+57){
								if(event.button.y>h&&event.button.y<h+57){
									pieceselection=C_DRAPEAU;
								}else if(event.button.y>h+y1&&event.button.y<h+y1+57){
									pieceselection=C_MARECHAL;
								}else if(event.button.y>h+y1*2&&event.button.y<h+y1*2+57){
									pieceselection=C_GENERAL;
								}else if(event.button.y>h+y1*3&&event.button.y<h+y1*3+57){
									pieceselection=C_COLONEL;
								}else if(event.button.y>h+y1*4&&event.button.y<h+y1*4+57){
									pieceselection=C_COMMANDANT;
								}else if(event.button.y>h+y1*5&&event.button.y<h+y1*5+57){
									pieceselection=C_CAPITAINE;
								}else if(event.button.y>h+y1*6&&event.button.y<h+y1*6+57){
									pieceselection=C_LIEUTENANT;
								}else if(event.button.y>h+y1*7&&event.button.y<h+y1*7+57){
									pieceselection=C_SERGENT;
								}else if(event.button.y>h+y1*8&&event.button.y<h+y1*8+57){
									pieceselection=C_DEMINEUR;
								}else if(event.button.y>h+y1*9&&event.button.y<h+y1*9+57){
									pieceselection=C_ECLAIREUR;
								}else if(event.button.y>h+y1*10&&event.button.y<h+y1*10+57){
									pieceselection=C_ESPION;
								}else if(event.button.y>h+y1*11&&event.button.y<h+y1*11+57){
									pieceselection=C_BOMBE;
								}else{
									pieceselection='\0';
								}
							}else{
								pieceselection='\0';
							}
							
							///
							
						}
						//
						
						affichePlateau();
						
						break;
					default:
						break;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {	
					case SDLK_ESCAPE:
						exit(EXIT_SUCCESS);
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
	
	//
	
	/////////////////////////////
	
	cl->envoyerPlateau();
	
   	affichePlateau();
	
	position.x = 0;
	position.y = 0;
	
	bool continuer = true;
	
	if(cl->getMyColor()==BLUE){
		cl->attendreDeplacementAdverse();
		affichePlateau();
		
		if(plateau->getVictory()!=NULL){
			continuer = false;
		}
	}
	
	while (continuer){
		SDL_Event event;
		SDL_WaitEvent(&event);	
		switch (event.type) {
			case SDL_QUIT:
				exit(EXIT_SUCCESS);
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {	
					case SDL_BUTTON_LEFT:
						int abscisse,ordonnee;
						abscisse=(event.button.x-jeu_plateau_pos.x-1)/57;
						ordonnee=9-((event.button.y-jeu_plateau_pos.y-1)/57);
						if(selectionx==-1&&selectiony==-1){
							//////////
							if(!plateau->checkForbiddenLocation(abscisse,ordonnee)){
								if(!plateau->checkFreeLocation(abscisse,ordonnee)){
									if(plateau->getPiece(abscisse,ordonnee)->getColor()==cl->getMyColor()){
										selectionx=abscisse;
										selectiony=ordonnee;
										affichePlateau();
									}else{
										std::cout<<"Ca n'est pas une de vos pieces"<<std::endl;
									}
								}else{
									std::cout<<"Aucune piece n'est présente à cet emplacement"<<std::endl;
								}
							}else{
								std::cout<<"Coordonnées incorrectes"<<std::endl;
							}
							///////////
						}else{
							
							///////////
							
							if(!plateau->checkForbiddenLocation(abscisse,ordonnee)){
								if(plateau->isCorrectMove(selectionx,selectiony,abscisse,ordonnee)){
									cl->envoiDeplacement(selectionx,selectiony,abscisse,ordonnee);
									affichePlateau();
									
									if(plateau->getVictory()==NULL){
										cl->attendreDeplacementAdverse();
										affichePlateau();
										if(plateau->getVictory()!=NULL){
											continuer=false;
										}
									}else{
										continuer=false;
									}
									
								}else{
									std::cout<<"Impossible de cibler cet emplacement."<<std::endl;
								}
							}else{
								std::cout<<"Coordonnées incorrectes"<<std::endl;
							}
							
							selectionx=-1;
							selectiony=-1;
							affichePlateau();
							//////////
							
						}
						break;
					default:
						break;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {	
					case SDLK_ESCAPE:
						continuer=false;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
	
	if(*plateau->getVictory()==cl->getMyColor()){
		writeTTFText("Vous avez gagne !",200,630,ecran);
	}else{
		writeTTFText("Vous avez perdu !",200,630,ecran);
	}
	
	SDL_Flip(ecran);
	
	continuer = true;
	while (continuer){
		SDL_Event event;
		SDL_WaitEvent(&event);	
		switch (event.type) {
			case SDL_QUIT:
				exit(EXIT_SUCCESS);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						continuer=false;
						break;
					default:
						break;
				}
				break;
		}
	}
	
	delete(cl);
	
}

void Affichage::writeTTFText(std::string text,int x,int y,SDL_Surface* fond) {
	SDL_Surface* texte;
	SDL_Color couleur = {255, 255, 255};
	SDL_Rect position;
	position.x=x;
	position.y=y;
	texte = TTF_RenderText_Blended(police,text.c_str(), couleur);
	SDL_BlitSurface(texte, NULL, fond, &position); 
}

void Affichage::affichePlateau(){
	SDL_Surface* pl;
	SDL_Surface* fond;
	SDL_Rect position;
	position.x=0;
	position.y=0;
	pl=SDL_ConvertSurface(jeu_plateau,jeu_plateau->format,SDL_SRCALPHA);
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(!plateau->checkFreeLocation(j,i)){
				affichePiece(plateau->getPiece(j,i),j,i,pl);
			}
		}
	}
	fond=SDL_ConvertSurface(jeu_fond,jeu_fond->format,SDL_SRCALPHA);
	SDL_BlitSurface(pl, NULL, fond, &jeu_plateau_pos);
	
	///////////
	
	if(cl->getMyColor()==RED){
		
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,DRAPEAU)),x1,h,fond);
		if(pieceselection==C_DRAPEAU){
			affichePieceSurface(piece_rouge_selection,piece_drapeau,x1+l,h,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_drapeau,x1+l,h,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,MARECHAL)),x1,h+y1,fond);
		if(pieceselection==C_MARECHAL){
			affichePieceSurface(piece_rouge_selection,piece_marechal,x1+l,h+y1,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_marechal,x1+l,h+y1,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,GENERAL)),x1,h+y1*2,fond);
		if(pieceselection==C_GENERAL){
			affichePieceSurface(piece_rouge_selection,piece_general,x1+l,h+y1*2,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_general,x1+l,h+y1*2,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,COLONEL)),x1,h+y1*3,fond);
		if(pieceselection==C_COLONEL){
			affichePieceSurface(piece_rouge_selection,piece_colonel,x1+l,h+y1*3,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_colonel,x1+l,h+y1*3,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,COMMANDANT)),x1,h+y1*4,fond);
		if(pieceselection==C_COMMANDANT){
			affichePieceSurface(piece_rouge_selection,piece_commandant,x1+l,h+y1*4,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_commandant,x1+l,h+y1*4,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,CAPITAINE)),x1,h+y1*5,fond);
		if(pieceselection==C_CAPITAINE){
			affichePieceSurface(piece_rouge_selection,piece_capitaine,x1+l,h+y1*5,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_capitaine,x1+l,h+y1*5,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,LIEUTENANT)),x1,h+y1*6,fond);
		if(pieceselection==C_LIEUTENANT){
			affichePieceSurface(piece_rouge_selection,piece_lieutenant,x1+l,h+y1*6,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_lieutenant,x1+l,h+y1*6,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,SERGENT)),x1,h+y1*7,fond);
		if(pieceselection==C_SERGENT){
			affichePieceSurface(piece_rouge_selection,piece_sergent,x1+l,h+y1*7,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_sergent,x1+l,h+y1*7,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,DEMINEUR)),x1,h+y1*8,fond);
		if(pieceselection==C_DEMINEUR){
			affichePieceSurface(piece_rouge_selection,piece_demineur,x1+l,h+y1*8,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_demineur,x1+l,h+y1*8,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,ECLAIREUR)),x1,h+y1*9,fond);
		if(pieceselection==C_ECLAIREUR){
			affichePieceSurface(piece_rouge_selection,piece_eclaireur,x1+l,h+y1*9,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_eclaireur,x1+l,h+y1*9,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,ESPION)),x1,h+y1*10,fond);
		if(pieceselection==C_ESPION){
			affichePieceSurface(piece_rouge_selection,piece_espion,x1+l,h+y1*10,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_espion,x1+l,h+y1*10,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,BOMBE)),x1,h+y1*11,fond);
		if(pieceselection==C_BOMBE){
			affichePieceSurface(piece_rouge_selection,piece_bombe,x1+l,h+y1*11,fond);
		}else{
			affichePieceSurface(piece_rouge,piece_bombe,x1+l,h+y1*11,fond);
		}
		
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,DRAPEAU)),x2,h,fond);
		affichePieceSurface(piece_bleu,piece_drapeau,x2+l,h,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,MARECHAL)),x2,h+y1,fond);
		affichePieceSurface(piece_bleu,piece_marechal,x2+l,h+y1,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,GENERAL)),x2,h+y1*2,fond);
		affichePieceSurface(piece_bleu,piece_general,x2+l,h+y1*2,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,COLONEL)),x2,h+y1*3,fond);
		affichePieceSurface(piece_bleu,piece_colonel,x2+l,h+y1*3,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,COMMANDANT)),x2,h+y1*4,fond);
		affichePieceSurface(piece_bleu,piece_commandant,x2+l,h+y1*4,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,CAPITAINE)),x2,h+y1*5,fond);
		affichePieceSurface(piece_bleu,piece_capitaine,x2+l,h+y1*5,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,LIEUTENANT)),x2,h+y1*6,fond);
		affichePieceSurface(piece_bleu,piece_lieutenant,x2+l,h+y1*6,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,SERGENT)),x2,h+y1*7,fond);
		affichePieceSurface(piece_bleu,piece_sergent,x2+l,h+y1*7,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,DEMINEUR)),x2,h+y1*8,fond);
		affichePieceSurface(piece_bleu,piece_demineur,x2+l,h+y1*8,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,ECLAIREUR)),x2,h+y1*9,fond);
		affichePieceSurface(piece_bleu,piece_eclaireur,x2+l,h+y1*9,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,ESPION)),x2,h+y1*10,fond);
		affichePieceSurface(piece_bleu,piece_espion,x2+l,h+y1*10,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,BOMBE)),x2,h+y1*11,fond);
		affichePieceSurface(piece_bleu,piece_bombe,x2+l,h+y1*11,fond);
		
	}else{
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,DRAPEAU)),x1,h,fond);
		affichePieceSurface(piece_rouge,piece_drapeau,x1+l,h,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,MARECHAL)),x1,h+y1,fond);
		affichePieceSurface(piece_rouge,piece_marechal,x1+l,h+y1,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,GENERAL)),x1,h+y1*2,fond);
		affichePieceSurface(piece_rouge,piece_general,x1+l,h+y1*2,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,COLONEL)),x1,h+y1*3,fond);
		affichePieceSurface(piece_rouge,piece_colonel,x1+l,h+y1*3,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,COMMANDANT)),x1,h+y1*4,fond);
		affichePieceSurface(piece_rouge,piece_commandant,x1+l,h+y1*4,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,CAPITAINE)),x1,h+y1*5,fond);
		affichePieceSurface(piece_rouge,piece_capitaine,x1+l,h+y1*5,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,LIEUTENANT)),x1,h+y1*6,fond);
		affichePieceSurface(piece_rouge,piece_lieutenant,x1+l,h+y1*6,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,SERGENT)),x1,h+y1*7,fond);
		affichePieceSurface(piece_rouge,piece_sergent,x1+l,h+y1*7,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,DEMINEUR)),x1,h+y1*8,fond);
		affichePieceSurface(piece_rouge,piece_demineur,x1+l,h+y1*8,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,ECLAIREUR)),x1,h+y1*9,fond);
		affichePieceSurface(piece_rouge,piece_eclaireur,x1+l,h+y1*9,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,ESPION)),x1,h+y1*10,fond);
		affichePieceSurface(piece_rouge,piece_espion,x1+l,h+y1*10,fond);
		writeTTFText(intToString(plateau->nbPiecesRestantes(RED,BOMBE)),x1,h+y1*11,fond);
		affichePieceSurface(piece_rouge,piece_bombe,x1+l,h+y1*11,fond);
		
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,DRAPEAU)),x2,h,fond);
		if(pieceselection==C_DRAPEAU){
			affichePieceSurface(piece_bleu_selection,piece_drapeau,x2+l,h,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_drapeau,x2+l,h,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,MARECHAL)),x2,h+y1,fond);
		if(pieceselection==C_MARECHAL){
			affichePieceSurface(piece_bleu_selection,piece_marechal,x2+l,h+y1,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_marechal,x2+l,h+y1,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,GENERAL)),x2,h+y1*2,fond);
		if(pieceselection==C_GENERAL){
			affichePieceSurface(piece_bleu_selection,piece_general,x2+l,h+y1*2,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_general,x2+l,h+y1*2,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,COLONEL)),x2,h+y1*3,fond);
		if(pieceselection==C_COLONEL){
			affichePieceSurface(piece_bleu_selection,piece_colonel,x2+l,h+y1*3,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_colonel,x2+l,h+y1*3,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,COMMANDANT)),x2,h+y1*4,fond);
		if(pieceselection==C_COMMANDANT){
			affichePieceSurface(piece_bleu_selection,piece_commandant,x2+l,h+y1*4,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_commandant,x2+l,h+y1*4,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,CAPITAINE)),x2,h+y1*5,fond);
		if(pieceselection==C_CAPITAINE){
			affichePieceSurface(piece_bleu_selection,piece_capitaine,x2+l,h+y1*5,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_capitaine,x2+l,h+y1*5,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,LIEUTENANT)),x2,h+y1*6,fond);
		if(pieceselection==C_LIEUTENANT){
			affichePieceSurface(piece_bleu_selection,piece_lieutenant,x2+l,h+y1*6,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_lieutenant,x2+l,h+y1*6,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,SERGENT)),x2,h+y1*7,fond);
		if(pieceselection==C_SERGENT){
			affichePieceSurface(piece_bleu_selection,piece_sergent,x2+l,h+y1*7,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_sergent,x2+l,h+y1*7,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,DEMINEUR)),x2,h+y1*8,fond);
		if(pieceselection==C_DEMINEUR){
			affichePieceSurface(piece_bleu_selection,piece_demineur,x2+l,h+y1*8,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_demineur,x2+l,h+y1*8,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,ECLAIREUR)),x2,h+y1*9,fond);
		if(pieceselection==C_ECLAIREUR){
			affichePieceSurface(piece_bleu_selection,piece_eclaireur,x2+l,h+y1*9,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_eclaireur,x2+l,h+y1*9,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,ESPION)),x2,h+y1*10,fond);
		if(pieceselection==C_ESPION){
			affichePieceSurface(piece_bleu_selection,piece_espion,x2+l,h+y1*10,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_espion,x2+l,h+y1*10,fond);
		}
		writeTTFText(intToString(plateau->nbPiecesRestantes(BLUE,BOMBE)),x2,h+y1*11,fond);
		if(pieceselection==C_BOMBE){
			affichePieceSurface(piece_bleu_selection,piece_bombe,x2+l,h+y1*11,fond);
		}else{
			affichePieceSurface(piece_bleu,piece_bombe,x2+l,h+y1*11,fond);
		}
	}
	///////////
	
	if(cl->getDernierDeplacement().xa!=-1){
		std::string s;
		s="("+intToString(cl->getDernierDeplacement().xd)+","+intToString(cl->getDernierDeplacement().yd)+") vers ("+intToString(cl->getDernierDeplacement().xa)+","+intToString(cl->getDernierDeplacement().ya)+")";
		writeTTFText(s,235,700,fond);
		
		affichePiece(cl->getDernierDeplacement().pd,3,-3,fond);
		if(cl->getDernierDeplacement().pa!=NULL){
			affichePiece(cl->getDernierDeplacement().pa,8,-3,fond);
		}
	}
	
	SDL_BlitSurface(fond, NULL, ecran, &position);
	SDL_Flip(ecran);
}

void Affichage::affichePieceSurface(SDL_Surface *couleur,SDL_Surface *type,int x,int y,SDL_Surface* surface){
	SDL_Rect position;
	position.x = x;
	position.y = y;
	SDL_BlitSurface(SDL_DisplayFormatAlpha(couleur), NULL, surface, &position);
	if (type != NULL) {
		SDL_BlitSurface(SDL_DisplayFormatAlpha(type), NULL, surface, &position);
	}
}

void Affichage::affichePiece(Piece * piece,int x,int y,SDL_Surface* pl){
	SDL_Surface *couleur=NULL;
	SDL_Surface *type=NULL;
	SDL_Rect position;
	position.x = 1+(57*x);
	position.y = 514-(57*y);
	if(piece->getColor()==RED){
		if(x==selectionx&&y==selectiony){
			couleur=piece_rouge_selection;
		}else{
			couleur=piece_rouge;
		}
	}else{
		if(x==selectionx&&y==selectiony){
			couleur=piece_bleu_selection;
		}else{
			couleur=piece_bleu;
		}
	}
	SDL_BlitSurface(SDL_DisplayFormatAlpha(couleur), NULL, pl, &position);
	
	switch(piece->getCharID()){
		case C_BOMBE:
			type=piece_bombe;
			break;
		case C_ESPION:
			type=piece_espion;
			break;
		case C_ECLAIREUR:
			type=piece_eclaireur;
			break;
		case C_DEMINEUR:
			type=piece_demineur;
			break;
		case C_SERGENT:
			type=piece_sergent;
			break;
		case C_LIEUTENANT:
			type=piece_lieutenant;
			break;
		case C_CAPITAINE:
			type=piece_capitaine;
			break;
		case C_COMMANDANT:
			type=piece_commandant;
			break;
		case C_COLONEL:
			type=piece_colonel;
			break;
		case C_GENERAL:
			type=piece_general;
			break;
		case C_MARECHAL:
			type=piece_marechal;
		break;
		case C_DRAPEAU:
			type=piece_drapeau;
			break;
		default :
			type=NULL;
			break;
	}
	if(type!=NULL){
		SDL_BlitSurface(SDL_DisplayFormatAlpha(type), NULL, pl, &position);
	}
}

void Affichage::showError(int numerror) {
	//switch
}

