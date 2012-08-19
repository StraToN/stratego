#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv){
	//initialisation SDL   
	//SDL_Init(0);
	SDLNet_Init();

	TCPsocket socket;
	IPaddress hote;
	
	//Initialise Hote
	SDLNet_ResolveHost(&hote,"127.0.0.1",6969); 
	//Initialisation du Socket
	socket = SDLNet_TCP_Open(&hote);
	// Maintenant Socket contient une socket valide que l'on peut utiliser
	// pour communiquer, ou est égale à NULL
	if(socket==NULL){
		std::cerr<<"Erreur lors de la connection au serveur."<<std::endl;
		exit(EXIT_FAILURE);
	}
	
	std::string ch="Ping ?";
	SDLNet_TCP_Send(socket,(void*)ch.c_str(),ch.size()); 
	std::cout<<"Envoye: "<<ch<<std::endl;
	
	int taille=6;//taille de la chaine que l'on s'attend a recevoir
	char buffer[taille+1];
	buffer[taille]='\0';//caractere de fin de chaine
	SDLNet_TCP_Recv(socket,(void*)buffer,taille);
	
	std::cout<<"Recu: "<<buffer<<std::endl;
	
	SDLNet_TCP_Close(socket);
	
	return EXIT_SUCCESS;
}
