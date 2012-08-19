#include "Client.h"
#include "fonctions.h"

Client::Client(Plateau* p,string addresseServeur){
	this->plateau=p;
	//on se connecte
	SDLNet_Init();
	IPaddress hote;
	std::cout<<"Connexion serveur ..."<<std::endl;
	SDLNet_ResolveHost(&hote,addresseServeur.c_str(),6969);
	this->socket = SDLNet_TCP_Open(&hote);
	if(socket==NULL){
		std::cerr<<"Erreur lors de la connection au serveur."<<std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout<<"Connecté !"<<std::endl;
	//on attend notre couleur
	char res[1];
	SDLNet_TCP_Recv(socket,(void*)res,1);
	if(res[0]==C_RED){
		this->macouleur=RED;
		std::cout<<"Vous etes rouge."<<std::endl;
	}else if(res[0]==C_BLUE){
		this->macouleur=BLUE;
		std::cout<<"Vous etes bleu."<<std::endl;
	}else{
		std::cerr<<"Vous etes rien du tout ca a buggé méchant."<<std::endl;
		exit(EXIT_FAILURE);
	}
	dernier.xd=-1;
	dernier.yd=-1;
	dernier.xa=-1;
	dernier.ya=-1;
	dernier.pd=NULL;
	dernier.pa=NULL;
}

struct Deplacement Client::getDernierDeplacement(){
	return dernier;
}

Client::~Client(){
	SDLNet_TCP_Close(socket);
	SDLNet_Quit();
}

void Client::envoiDeplacement(int x1, int y1, int x2, int y2){
	
	dernier.xd=x1;
	dernier.yd=y1;
	dernier.xa=x2;
	dernier.ya=y2;
	dernier.pd=plateau->getPiece(x1,y1);
	
	//on envois le deplacement
	char tab[4]={intToChar(x1),intToChar(y1),intToChar(x2),intToChar(y2)};
	SDLNet_TCP_Send(socket,(void*)tab,4);
	
	//on attend une piece si c'est une attaque (on remplace la piece anonyme par la vraie piece(on révéle la piece))
	char res[1];
	SDLNet_TCP_Recv(socket,(void*)res,1);
	
	std::cout<<"piece attaquee: \""<<res[0]<<"\""<<std::endl;
	
	if(res[0]!=C_VIDE){
		this->plateau->deletePiece(x2,y2);
		this->plateau->putPiece(createPiece(charToId(res[0]),!this->macouleur),x2,y2);
		dernier.pa=createPiece(charToId(res[0]),!this->macouleur);
	}else{
		dernier.pa=NULL;
	}
	//on bouge
	this->plateau->move(x1,y1,x2,y2);
	
	//on remplace la vraie piece par une piece anonyme (on recache la piece)
	if(res[0]!=C_VIDE){
		if(!plateau->checkFreeLocation(x1,y1)){
			if(this->plateau->getPiece(x1,y1)->getColor()==!macouleur){
				this->plateau->deletePiece(x1,y1);
				this->plateau->putPiece(new Piece(!macouleur),x1,y1);
			}
		}
		if(!plateau->checkFreeLocation(x2,y2)){
			if(this->plateau->getPiece(x2,y2)->getColor()==!macouleur){
				this->plateau->deletePiece(x2,y2);
				this->plateau->putPiece(new Piece(!macouleur),x2,y2);
			}
		}
	}
}

void Client::envoyerPlateau(){
	//on créer le tableau de char et on envoit
	char pl[40];
	if(this->macouleur==RED){
		int c=0;
		for(int i=0;i<4;i++){
			for(int j=0;j<TAILLE_PLATEAU;j++){
				pl[c]=this->plateau->getCharID(j,i);
				c++;
			}
		}
	}else{
		int c=0;
		for(int i=9;i>5;i--){
			for(int j=9;j>=0;j--){
				pl[c]=this->plateau->getCharID(j,i);
				c++;
			}
		}
	}
	SDLNet_TCP_Send(socket,(void*)pl,40);
	
	//on vide le box de l'ennemi
	plateau->clearAllElementsInBox(!this->macouleur);
	
	//on rempli le camp ennemi de pieces ennemies
	if(this->macouleur==RED){
		for(int i=6;i<TAILLE_PLATEAU;i++){
			for(int j=0;j<TAILLE_PLATEAU;j++){
				this->plateau->putPiece(new Piece(BLUE),j,i);
			}
		}
	}else{
		for(int i=0;i<4;i++){
			for(int j=0;j<TAILLE_PLATEAU;j++){
				this->plateau->putPiece(new Piece(RED),j,i);
			}
		}
	}
	//on attend l'autre joueur
	char res[1];
	SDLNet_TCP_Recv(socket,(void*)res,1);
	if(res[0]!=C_GO){
		std::cerr<<"Une erreur est survenue"<<std::endl;
	}
	
}

bool Client::getMyColor(){
	return this->macouleur;
}

void Client::attendreDeplacementAdverse(){
	
	//on recoit le deplacement effectué par l'ennemi
	char res[4];
	SDLNet_TCP_Recv(socket,(void*)res,4);
	int res1[4]={charToInt(res[0]),charToInt(res[1]),charToInt(res[2]),charToInt(res[3])};
	//on recoit eventuellement la piece si c'est une attaque
	char res2[1];
	SDLNet_TCP_Recv(socket,(void*)res2,1);
	
	std::cout<<"receptions: "<<res1[0]<<" "<<res1[1]<<" "<<res1[2]<<" "<<res1[3]<<" \""<<res2[0]<<"\""<<endl;
	
	dernier.xd=res1[0];
	dernier.yd=res1[1];
	dernier.xa=res1[2];
	dernier.ya=res1[3];
	dernier.pd=createPiece(charToId(res2[0]),!this->macouleur);
	dernier.pa=plateau->getPiece(res1[2],res1[3]);
	
	//si c'est une attaque on révéle la piece
	if(res2[0]!=C_VIDE){
		this->plateau->deletePiece(res1[0],res1[1]);
		this->plateau->putPiece(createPiece(charToId(res2[0]),!this->macouleur),res1[0],res1[1]);
		this->plateau->move(res1[0],res1[1],res1[2],res1[3]);
	}else{
		this->plateau->deletePiece(res1[0],res1[1]);
		this->plateau->putPiece(new Piece(!this->macouleur),res1[2],res1[3]);
	}
	
	//on recache la piece
	if(res2[0]!=C_VIDE){
		if(!plateau->checkFreeLocation(res1[0],res1[1])){
			if(this->plateau->getPiece(res1[0],res1[1])->getColor()==!macouleur){
				this->plateau->deletePiece(res1[0],res1[1]);
				this->plateau->putPiece(new Piece(!macouleur),res1[0],res1[1]);
			}
		}
		if(!plateau->checkFreeLocation(res1[2],res1[3])){
			if(this->plateau->getPiece(res1[2],res1[3])->getColor()==!macouleur){
				this->plateau->deletePiece(res1[2],res1[3]);
				this->plateau->putPiece(new Piece(!macouleur),res1[2],res1[3]);
			}
		}
	}
}
