#include "AffichageTexte.h"

AffichageTexte::AffichageTexte(){
	afficherMenu();
}

void AffichageTexte::afficherMenu() {
	int choix=0;
	while(choix!=MENU_QUITTER){
		std::cout<<"Sélectionnez un choix :"<<std::endl;
		std::cout<<MENU_CREER<<" Créer une partie"<<std::endl;
		std::cout<<MENU_REJOINDRE<<" Rejoindre une partie"<<std::endl;
		std::cout<<MENU_OPTIONS<<" Options"<<std::endl;
		std::cout<<MENU_CREDITS<<" Crédits"<<std::endl;
		std::cout<<MENU_QUITTER<<" Quitter"<<std::endl;
		std::cin>>choix;
		switch(choix){
			case MENU_CREER:
				creerPartie();
				break;
			case MENU_REJOINDRE:
				rejoindrePartie();
				break;
			case MENU_OPTIONS:
				std::cout<<"Ya pas d'options !"<<std::endl;
				break;
			case MENU_CREDITS:
				std::cout<<"Ce jeu a ete code par Nicolas HENRY, Philippe SCHMUCKER, Julian MURGIA et Michael DOHR."<<std::endl;
				break;
			case MENU_QUITTER:
				exit(EXIT_SUCCESS);
				break;
		}
	}
}

void AffichageTexte::creerPartie(){
	//a faire ici: creer le serveur
	connecterPartie("127.0.0.1");
	//a faire ici: fermer le serveur
}

void AffichageTexte::rejoindrePartie(){
	std::string ipserveur;
	std::cout<<"Entrez l'IP du serveur :"<<std::endl;
	std::cin>>ipserveur;
	connecterPartie(ipserveur);
}

void AffichageTexte::connecterPartie(std::string ipserveur){
	// a faire : creer le client et se connecter au serveur
	//
	
	
	//a finir : remplissage du plateau par le joueur
	bool rempli=false;
	char piece;
	int abscisse,ordonnee;
	bool pieceok=false;
	
	plateau=new Plateau();
	
	cl=new Client(plateau,ipserveur);

	#define REMPLISSAGEAUTO
	#ifdef REMPLISSAGEAUTO
	
	if(cl->getMyColor()==RED){
		plateau->setPiecePosition(cl->getMyColor(),'B',0,0);
		plateau->setPiecePosition(cl->getMyColor(),'B',1,0);
		plateau->setPiecePosition(cl->getMyColor(),'B',2,0);
		plateau->setPiecePosition(cl->getMyColor(),'B',3,0);
		plateau->setPiecePosition(cl->getMyColor(),'B',4,0);
		plateau->setPiecePosition(cl->getMyColor(),'B',5,0);
		plateau->setPiecePosition(cl->getMyColor(),'6',6,0);
		plateau->setPiecePosition(cl->getMyColor(),'7',7,0);
		plateau->setPiecePosition(cl->getMyColor(),'6',8,0);
		plateau->setPiecePosition(cl->getMyColor(),'6',9,0);
		plateau->setPiecePosition(cl->getMyColor(),'5',0,1);
		plateau->setPiecePosition(cl->getMyColor(),'5',1,1);
		plateau->setPiecePosition(cl->getMyColor(),'5',2,1);
		plateau->setPiecePosition(cl->getMyColor(),'4',3,1);
		plateau->setPiecePosition(cl->getMyColor(),'4',4,1);
		plateau->setPiecePosition(cl->getMyColor(),'4',5,1);
		plateau->setPiecePosition(cl->getMyColor(),'3',6,1);
		plateau->setPiecePosition(cl->getMyColor(),'3',7,1);
		plateau->setPiecePosition(cl->getMyColor(),'3',8,1);
		plateau->setPiecePosition(cl->getMyColor(),'2',9,1);
		plateau->setPiecePosition(cl->getMyColor(),'2',0,2);
		plateau->setPiecePosition(cl->getMyColor(),'2',1,2);
		plateau->setPiecePosition(cl->getMyColor(),'2',2,2);
		plateau->setPiecePosition(cl->getMyColor(),'1',3,2);
		plateau->setPiecePosition(cl->getMyColor(),'1',4,2);
		plateau->setPiecePosition(cl->getMyColor(),'1',5,2);
		plateau->setPiecePosition(cl->getMyColor(),'1',6,2);
		plateau->setPiecePosition(cl->getMyColor(),'1',7,2);
		plateau->setPiecePosition(cl->getMyColor(),'1',8,2);
		plateau->setPiecePosition(cl->getMyColor(),'1',9,2);
		plateau->setPiecePosition(cl->getMyColor(),'0',0,3);
		plateau->setPiecePosition(cl->getMyColor(),'9',1,3);
		plateau->setPiecePosition(cl->getMyColor(),'8',2,3);
		plateau->setPiecePosition(cl->getMyColor(),'7',3,3);
		plateau->setPiecePosition(cl->getMyColor(),'D',4,3);
		plateau->setPiecePosition(cl->getMyColor(),'5',5,3);
		plateau->setPiecePosition(cl->getMyColor(),'4',6,3);
		plateau->setPiecePosition(cl->getMyColor(),'3',7,3);
		plateau->setPiecePosition(cl->getMyColor(),'2',8,3);
		plateau->setPiecePosition(cl->getMyColor(),'1',9,3);
		
	}else{
		plateau->setPiecePosition(cl->getMyColor(),'B',0,9);
		plateau->setPiecePosition(cl->getMyColor(),'B',1,9);
		plateau->setPiecePosition(cl->getMyColor(),'B',2,9);
		plateau->setPiecePosition(cl->getMyColor(),'B',3,9);
		plateau->setPiecePosition(cl->getMyColor(),'B',4,9);
		plateau->setPiecePosition(cl->getMyColor(),'B',5,9);
		plateau->setPiecePosition(cl->getMyColor(),'D',6,9);
		plateau->setPiecePosition(cl->getMyColor(),'7',7,9);
		plateau->setPiecePosition(cl->getMyColor(),'6',8,9);
		plateau->setPiecePosition(cl->getMyColor(),'6',9,9);
		plateau->setPiecePosition(cl->getMyColor(),'5',0,8);
		plateau->setPiecePosition(cl->getMyColor(),'5',1,8);
		plateau->setPiecePosition(cl->getMyColor(),'5',2,8);
		plateau->setPiecePosition(cl->getMyColor(),'4',3,8);
		plateau->setPiecePosition(cl->getMyColor(),'4',4,8);
		plateau->setPiecePosition(cl->getMyColor(),'4',5,8);
		plateau->setPiecePosition(cl->getMyColor(),'3',6,8);
		plateau->setPiecePosition(cl->getMyColor(),'3',7,8);
		plateau->setPiecePosition(cl->getMyColor(),'3',8,8);
		plateau->setPiecePosition(cl->getMyColor(),'2',9,8);
		plateau->setPiecePosition(cl->getMyColor(),'2',0,7);
		plateau->setPiecePosition(cl->getMyColor(),'2',1,7);
		plateau->setPiecePosition(cl->getMyColor(),'2',2,7);
		plateau->setPiecePosition(cl->getMyColor(),'1',3,7);
		plateau->setPiecePosition(cl->getMyColor(),'1',4,7);
		plateau->setPiecePosition(cl->getMyColor(),'1',5,7);
		plateau->setPiecePosition(cl->getMyColor(),'1',6,7);
		plateau->setPiecePosition(cl->getMyColor(),'1',7,7);
		plateau->setPiecePosition(cl->getMyColor(),'1',8,7);
		plateau->setPiecePosition(cl->getMyColor(),'1',9,7);
		plateau->setPiecePosition(cl->getMyColor(),'0',0,6);
		plateau->setPiecePosition(cl->getMyColor(),'9',1,6);
		plateau->setPiecePosition(cl->getMyColor(),'8',2,6);
		plateau->setPiecePosition(cl->getMyColor(),'7',3,6);
		plateau->setPiecePosition(cl->getMyColor(),'6',4,6);
		plateau->setPiecePosition(cl->getMyColor(),'5',5,6);
		plateau->setPiecePosition(cl->getMyColor(),'4',6,6);
		plateau->setPiecePosition(cl->getMyColor(),'3',7,6);
		plateau->setPiecePosition(cl->getMyColor(),'2',8,6);
		plateau->setPiecePosition(cl->getMyColor(),'1',9,6);
	}
	
	rempli=true;
	std::cout<<"Le plateau a été rempli automatiquement."<<std::endl;
	
	#endif
	
	while(!rempli){
		// on affiche une premiere fois le plateau pour que l'utilisateur sache ou placer ses pions
		affichePlateau();
		// on affiche quelles pieces le joueur peut placer
		std::cout<<N_DRAPEAU<<"("<<C_DRAPEAU<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),DRAPEAU)<<" "<<N_MARECHAL<<"("<<C_MARECHAL<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),MARECHAL)<<" "<<N_GENERAL<<"("<<C_GENERAL<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),GENERAL)<<" "<<N_COLONEL<<"("<<C_COLONEL<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),COLONEL)<<" "<<N_COMMANDANT<<"("<<C_COMMANDANT<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),COMMANDANT)<<" "<<N_CAPITAINE<<"("<<C_CAPITAINE<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),CAPITAINE)<<" "<<N_LIEUTENANT<<"("<<C_LIEUTENANT<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),LIEUTENANT)<<" "<<N_SERGENT<<"("<<C_SERGENT<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),SERGENT)<<" "<<N_DEMINEUR<<"("<<C_DEMINEUR<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),DEMINEUR)<<" "<<N_ECLAIREUR<<"("<<C_ECLAIREUR<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),ECLAIREUR)<<" "<<N_ESPION<<"("<<C_ESPION<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),ESPION)<<" "<<N_BOMBE<<"("<<C_BOMBE<<")x"<<plateau->nbPiecesRestantes(cl->getMyColor(),BOMBE)<<""<<std::endl<<std::endl;
		
		pieceok=false;
		while(!pieceok){
			std::cout<<"Entrez une piece à placer : ";
			std::cin>>piece;
			
			if(plateau->nbPiecesRestantes(cl->getMyColor(),charToId(piece))>0){
				pieceok=true;
			}else{
				std::cout<<"Toutes les entités de "<<charToName(piece)<<" ont deja ete placees"<<endl;
			}
		}
		
		pieceok=false;
		while(!pieceok){
			std::cout<<"Entrez une abscisse : ";
			std::cin>>abscisse;
			std::cout<<"Entrez une ordonnee : ";
			std::cin>>ordonnee;
			
			if(!plateau->checkForbiddenLocation(abscisse,ordonnee)&&isInArea(cl->getMyColor(),ordonnee)){
				if(plateau->checkFreeLocation(abscisse,ordonnee)){
					pieceok=true;
				}else{
					std::cout<<"La place n'est pas vide."<<std::endl;
				}
			}else{
				std::cout<<"Coordonnées incorrectes."<<std::endl;
			}
			
		}
		
		plateau->setPiecePosition(cl->getMyColor(),piece,abscisse,ordonnee);
		
		if(plateau->nbTotalPiecesRestantes(cl->getMyColor())==0){
			rempli=true;
		}
		
	}
	cl->envoyerPlateau();
	
	std::cout<<"Debut du jeu !"<<std::endl;
	
	affichePlateau();
	
	bool playerturn = RED;
	
	// a finir: gestion de la partie
	
	while(plateau->getVictory()==NULL){
		if(cl->getMyColor()==playerturn){
			int abscissecible,ordonneecible;
			
			std::cout<<"C'est à vous de jouer !"<<std::endl;
			pieceok=false;
			
			while(!pieceok){
				std::cout<<"Entrez l'abscisse de la piece a selectionner : ";
				std::cin>>abscisse;
				std::cout<<"Entrez l'ordonnee de la piece a selectionner : ";
				std::cin>>ordonnee;
				if(!plateau->checkForbiddenLocation(abscisse,ordonnee)){
					if(!plateau->checkFreeLocation(abscisse,ordonnee)){
						if(plateau->getPiece(abscisse,ordonnee)->getColor()==cl->getMyColor()){
							pieceok=true;
						}else{
							std::cout<<"Ca n'est pas une de vos pieces"<<std::endl;
						}
					}else{
						std::cout<<"Aucune piece n'est présente à cet emplacement"<<std::endl;
					}
				}else{
					std::cout<<"Coordonnées incorrectes"<<std::endl;
				}
			}
			
			pieceok=false;
			
			while(!pieceok){
				std::cout<<"Entrez l'abscisse de la case cible : ";
				std::cin>>abscissecible;
				std::cout<<"Entrez l'ordonnee de la case cible : ";
				std::cin>>ordonneecible;
				if(!plateau->checkForbiddenLocation(abscissecible,ordonneecible)){
					if(plateau->isCorrectMove(abscisse,ordonnee,abscissecible,ordonneecible)){
						pieceok=true;
					}else{
						std::cout<<"Impossible de cibler cet emplacement."<<std::endl;
					}
				}else{
					std::cout<<"Coordonnées incorrectes"<<std::endl;
				}
			}
			std::cout<<"Envois des déplacements..."<<std::endl;
			cl->envoiDeplacement(abscisse,ordonnee,abscissecible,ordonneecible);
			//envois deplacement
			//reception ok
			
		}else{
			std::cout<<"Attente du joueur adverse..."<<std::endl;
			cl->attendreDeplacementAdverse();
			//attente reception
		}
		affichePlateau();
		playerturn=!playerturn;
		
	}
	
	if(*plateau->getVictory()==RED){
		std::cout<<"Le joueur rouge a gagne la partie !!"<<std::endl;
	}else{
		std::cout<<"Le joueur bleu a gagne la partie !!"<<std::endl;
	}
	
	
	//
	// a faire : fermer le client
}

void AffichageTexte::affichePlateau(){
	
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
