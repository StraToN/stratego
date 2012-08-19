#include "Serveur.h"
#include "fonctions.h"

using namespace std;

void affichePlateau(Plateau *plateau){
	
	std::cout<<"  -----------------------------------------"<<std::endl;
	for(int i=9;i>=0;i--){
		std::cout<<i<<" |";
		for(int j=0;j<10;j++){
			if((j==2||j==6)&&(i==4||i==5)){
				std::cout<<"    ";
			}else{
				std::cout<<" "<<plateau->getCharID(j,i)<<" |";
			}
		}
		if(i==5){
			std::cout<<std::endl<<"  ---------       ---------       ---------"<<std::endl;
		}else{
			std::cout<<std::endl<<"  -----------------------------------------"<<std::endl;
		}
	}
	std::cout<<"    0   1   2   3   4   5   6   7   8   9  "<<std::endl;
	std::cout<<std::endl;
}


int lancerServeur(void* data) {

	TCPsocket serveur=NULL;
	TCPsocket joueur1=NULL;
	TCPsocket joueur2=NULL;
	IPaddress adresse;
	
	/*
	SDL_Thread *threadRCPJ1=NULL;
	SDL_Thread *threadRCPJ2=NULL;
	*/
	
	char buffer_pieces_red[40+1];
	char buffer_pieces_blue[40+1];
	char bufcoordonnees[4];
	char buf_color1[1];
	char buf_color2[1];
	char buf_go[1];
	char piece[1];
	
	int x1;
	int y1;
	int x2;
	int y2;

	SDLNet_Init();
	SDLNet_ResolveHost(&adresse,NULL,6969);
    serveur = SDLNet_TCP_Open(&adresse);
    
    Plateau *p = new Plateau();
    
    int current_state=ETAT_CONN_JOUEURS;
    	
	while(current_state <= ETAT_GAMEOVER) {
		switch (current_state) {
			case ETAT_CONN_JOUEURS:
				
				//Connection du joueur 1
				cout<<"En attente joueur 1..."<<endl;
		        while (joueur1 == NULL) {
		       		joueur1 = SDLNet_TCP_Accept(serveur);
		       		SDL_Delay(100);//une pause pour éviter que ca rame
		        }
		        cout<<"Joueur 1 connecté"<<endl;
		        
		        buf_color1[0] = C_RED;
		        SDLNet_TCP_Send(joueur1, (void*)buf_color1, 1);
		        
		        //Connection du joueur 2
		        cout<<"En attente joueur 2..."<<endl;
		        while (joueur2 == NULL){
		        	joueur2 = SDLNet_TCP_Accept(serveur);
		        	SDL_Delay(100);
		        	// metre une condition pour arreter l'attente d'un deuxieme client
		        	// todoo
		        }
		        cout<<"Joueur 2 connecté"<<endl;
		        
		        // Envoi des couleurs ; signifie également que les 2 joueurs sont connectés et que le serveur va attendre les placements
		      	
		      	buf_color2[0] = C_BLUE;
		        SDLNet_TCP_Send(joueur2, (void*)buf_color2, 1);
		        
		        cout<<"Couleurs envoyées !"<<endl;
		        
		        current_state = ETAT_PLATEAUX_JOUEURS;
		        break;
		        
		    case ETAT_PLATEAUX_JOUEURS:
		    	cout<<"Attente plateaux..."<<endl;
		    	
		    	/*
		    	// Attente des plateaux des joueurs
		    	mutex_plateau = SDL_CreateMutex();
		    	
		    	Datas dat;
		    	dat.socket = joueur1;
		    	dat.plateau = p;
		    	dat.color = RED;
		    	dat.mutex = mutex_plateau;
		    	threadRCPJ1 = SDL_CreateThread(servReceivePlateau, &dat);
		    	
		    	dat.socket = joueur2;
		    	dat.plateau = p;
		    	dat.color = BLUE;
		    	dat.mutex = mutex_plateau;
    			threadRCPJ2 = SDL_CreateThread(servReceivePlateau, &dat);
    			SDL_DestroyMutex(mutex_plateau);
    			
    			SDL_WaitThread(threadRCPJ1, NULL);
    			SDL_WaitThread(threadRCPJ2, NULL);
    			*/
    			
				SDLNet_TCP_Recv(joueur1, (void*)buffer_pieces_red, 40);
				buffer_pieces_red[40]='\0';
				cout<<"Reçu plateau joueur rouge : "<<buffer_pieces_red<<endl;
				p->setInitialPosition(RED, buffer_pieces_red);
				
				SDLNet_TCP_Recv(joueur2, (void*)buffer_pieces_blue, 40);
				buffer_pieces_blue[40]='\0';
				cout<<"Reçu plateau joueur bleu : "<<buffer_pieces_blue<<endl;
				p->setInitialPosition(BLUE, buffer_pieces_blue);
    			
    			// A cette position, le jeu peut commencer
				buf_go[0] = C_GO;
				
		        SDLNet_TCP_Send(joueur1, (void*)buf_go, 1);
		        SDLNet_TCP_Send(joueur2, (void*)buf_go, 1);
		        
		        // Affichage Plateau Serveur
		        affichePlateau(p);
		        
		    case ETAT_ACTION_JOUEUR_RED:
		    	cout<<"Tour du joueur rouge"<<endl;
		    	
		    	// Reception 2 coordonnées
		    	SDLNet_TCP_Recv(joueur1, (void*)bufcoordonnees, 4);
		    	
		    	x1=charToInt(bufcoordonnees[0]);
		    	y1=charToInt(bufcoordonnees[1]);
		    	x2=charToInt(bufcoordonnees[2]);
		    	y2=charToInt(bufcoordonnees[3]);
		    	
		    	cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
		    	
		    	// si c'est une attaque on récupère l'ID de la pièce attaquée et on l'envoie, sinon on envoie VIDE
		    	
		    	piece[0] = p->getCharID(x2,y2);
		    	cout<<"\""<<piece[0]<<"\""<<endl;
		    	SDLNet_TCP_Send(joueur1, (void*)piece, 1);

		    	// envoi des mouvements à l'autre joueur qui n'a pas joué ce tour
		    	SDLNet_TCP_Send(joueur2, (void*)bufcoordonnees, 4);
		    	if(!p->checkFreeLocation(x2,y2)){
		    		if(p->getPiece(x2,y2)->getColor()==BLUE){
						piece[0] = p->getCharID(x1,y1);
					}else{
						piece[0]=C_VIDE;
					}
		    	}else{
		    		piece[0]=C_VIDE;
		    	}
		    	cout<<"\""<<piece[0]<<"\""<<endl;
		    	SDLNet_TCP_Send(joueur2, (void*)piece, 1);
		    	// mouvement dans le plateau du serveur
		    	p->move(x1,y1,x2,y2);
		    	
		    	if(p->getVictory()!=NULL){
		    		current_state = ETAT_GAMEOVER;
		    	}else{
		    		current_state = ETAT_ACTION_JOUEUR_BLUE;
		    	}
		    	
		    	break;
				
			case ETAT_ACTION_JOUEUR_BLUE:
				cout<<"Tour du joueur bleu"<<endl;
		    	
		    	// Reception 2 coordonnées
		    	SDLNet_TCP_Recv(joueur2, (void*)bufcoordonnees, 4);
		    	
		    	x1=charToInt(bufcoordonnees[0]);
		    	y1=charToInt(bufcoordonnees[1]);
		    	x2=charToInt(bufcoordonnees[2]);
		    	y2=charToInt(bufcoordonnees[3]);
		    	
		    	cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
		    	
		    	// si c'est une attaque on récupère l'ID de la pièce attaquée et on l'envoie, sinon on envoie VIDE
		    	
		    	piece[0] = p->getCharID(x2,y2);
		    	cout<<"\""<<piece[0]<<"\""<<endl;
		    	SDLNet_TCP_Send(joueur2, (void*)piece, 1);
				
		    	// envoi des mouvements à l'autre joueur qui n'a pas joué ce tour
		    	SDLNet_TCP_Send(joueur1, (void*)bufcoordonnees, 4);
		    	if(!p->checkFreeLocation(x2,y2)){
		    		if(p->getPiece(x2,y2)->getColor()==RED){
						piece[0] = p->getCharID(x1,y1);
					}else{
						piece[0]=C_VIDE;
					}
		    	}else{
		    		piece[0]=C_VIDE;
		    	}
		    	cout<<"\""<<piece[0]<<"\""<<endl;
		    	SDLNet_TCP_Send(joueur1, (void*)piece, 1);
		    	
		    	// mouvement dans le plateau du serveur
		    	p->move(x1,y1,x2,y2);
		    	
		    	if(p->getVictory()!=NULL){
		    		current_state = ETAT_GAMEOVER;
		    	}else{
		    		current_state = ETAT_ACTION_JOUEUR_RED;
		    	}
		    	
		    	break;
		    	
		    case ETAT_GAMEOVER:
		    	cout<<"Jeu terminé."<<endl;
		    	SDLNet_TCP_Close(joueur1);
		    	SDLNet_TCP_Close(joueur2);
		    	SDLNet_TCP_Close(serveur);
				SDLNet_Quit();
		    	return 0;
		    	break;
		    	
		    case ERROR:
		    	cout<<"Erreur !!!"<<endl;
		    	return 1;
		    	break;
		}
	}
	
	return 0;
}
