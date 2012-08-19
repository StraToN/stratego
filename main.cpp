#include "Affichage.h"
#include "AffichageTexte.h"
#include <string>
#include <iostream>

int main(int argc, char *argv[]){
	if(argc==1){
		new Affichage();
	}else if(argc==2){
		if(strcmp(argv[0],"--verbose")||strcmp(argv[0],"-v")){
			new AffichageTexte();
		}else{
			std::cout<<"usage: Strategwar [--verbose|-v]"<<std::endl;
		}
	}else{
		std::cout<<"usage: Strategwar [--verbose|-v]"<<std::endl;
	}
	return EXIT_SUCCESS;
}
