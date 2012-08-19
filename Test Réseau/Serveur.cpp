#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc,char** argv)
{
    //SDL_Init(SDL_INIT_VIDEO);
    SDLNet_Init();

    TCPsocket serveur,connectee;
    IPaddress adresse;
    SDLNet_ResolveHost(&adresse,NULL,6969);
    serveur = SDLNet_TCP_Open(&adresse);

    while (true) {
        connectee = NULL;
        while (connectee == NULL) {
        	//ecoute le port 6969 et le met dans connectee si reception
            connectee = SDLNet_TCP_Accept(serveur);
            SDL_Delay(1000);//une pause pour éviter que ca rame
        }
		
		int taille=6;//taille de la chaine que l'on s'attend a recevoir
		char buffer[taille+1];
		buffer[taille]='\0';//caractere de fin de chaine
		SDLNet_TCP_Recv(connectee,(void*)buffer,taille);
		std::cout<<"Recu: "<<buffer<<std::endl;
		
		std::string ch="Pong !";
        SDLNet_TCP_Send(connectee,(void*)ch.c_str(),ch.size());
		std::cout<<"Envoye: "<<ch<<std::endl;

        SDLNet_TCP_Close(connectee);
    }

    return EXIT_SUCCESS;
}
