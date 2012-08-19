/*

Fonctions de conversions :
    - identifiant vers caractere d'affichage
    - caractere d'affichage vers identifiant
    - couleur vers nom de la couleur

*/

# include "fonctions.h"
# include "Bombe.h"
# include "Capitaine.h"
# include "Colonel.h"
# include "Commandant.h"
# include "Demineur.h"
# include "Drapeau.h"
# include "Eclaireur.h"
# include "Espion.h"
# include "General.h"
# include "Lieutenant.h"
# include "Marechal.h"
# include "Sergent.h"

#include <string>
#include <sstream>

// convertit un identifiant en caractere d'affichage
char idToChar(int id){
    char c;
    switch (id){
        case BOMBE:
            c=C_BOMBE;
        break;
        case ESPION:
            c=C_ESPION;
        break;
        case ECLAIREUR:
            c=C_ECLAIREUR;
        break;
        case DEMINEUR:
            c=C_DEMINEUR;
        break;
        case SERGENT:
            c=C_SERGENT;
        break;
        case LIEUTENANT:
            c=C_LIEUTENANT;
        break;
        case CAPITAINE:
            c=C_CAPITAINE;
        break;
        case COMMANDANT:
            c=C_COMMANDANT;
        break;
        case COLONEL:
            c=C_COLONEL;
        break;
        case GENERAL:
            c=C_GENERAL;
        break;
        case MARECHAL:
            c=C_MARECHAL;
        break;
        case DRAPEAU:
            c=C_DRAPEAU;
        break;
        default :
            c=C_CACHEE;
    }
    return c;
}

// convertit un caractere d'affichage en identifiant
int charToId(char c){
    int id;
    switch (c){
        case C_BOMBE:
            id=BOMBE;
        break;
        case C_ESPION:
            id=ESPION;
        break;
        case C_ECLAIREUR:
            id=ECLAIREUR;
        break;
        case C_DEMINEUR:
            id=DEMINEUR;
        break;
        case C_SERGENT:
            id=SERGENT;
        break;
        case C_LIEUTENANT:
            id=LIEUTENANT;
        break;
        case C_CAPITAINE:
            id=CAPITAINE;
        break;
        case C_COMMANDANT:
            id=COMMANDANT;
        break;
        case C_COLONEL:
            id=COLONEL;
        break;
        case C_GENERAL:
            id=GENERAL;
        break;
        case C_MARECHAL:
            id=MARECHAL;
        break;
        case C_DRAPEAU:
            id=DRAPEAU;
        break;
        case C_VIDE:
            id=VIDE;
        break;
        default :
            id=CACHEE;
    }
    return id;
}

// convertit un caractere d'affichage en nom de piece
string charToName(char c){
    string name;
    switch (c){
        case C_BOMBE:
            name=N_BOMBE;
        break;
        case C_ESPION:
            name=N_ESPION;
        break;
        case C_ECLAIREUR:
            name=N_ECLAIREUR;
        break;
        case C_DEMINEUR:
            name=N_DEMINEUR;
        break;
        case C_SERGENT:
            name=N_SERGENT;
        break;
        case C_LIEUTENANT:
            name=N_LIEUTENANT;
        break;
        case C_CAPITAINE:
            name=N_CAPITAINE;
        break;
        case C_COMMANDANT:
            name=N_COMMANDANT;
        break;
        case C_COLONEL:
            name=N_COLONEL;
        break;
        case C_GENERAL:
            name=N_GENERAL;
        break;
        case C_MARECHAL:
            name=N_MARECHAL;
        break;
        case C_DRAPEAU:
            name=N_DRAPEAU;
        break;
        default :
            name="";
    }
    return name;
}

// retourne le nom de la couleur passee en parametre
string getColorValue(bool col){
    return (col==RED) ? RED_VALUE : BLUE_VALUE;
}

// definit si l'ordonnee fait partie de la zone du joueur de couleur donnee
bool isInArea(bool player,int ordonnee){
    bool in=false;
    if (player==RED){
        // zone du joueur rouge
        in=ordonnee<4;
    }
    else{
        // zone du joueur bleu
        in=ordonnee>5;
    }
    return in;
}

// crée une piece a partir d'un identifiant
Piece* createPiece(int id,bool col){
    Piece* p=NULL;
    switch (id){
        case BOMBE:
            p=new Bombe(col);
        break;
        case ESPION:
            p=new Espion(col);
        break;
        case ECLAIREUR:
            p=new Eclaireur(col);
        break;
        case DEMINEUR:
            p=new Demineur(col);
        break;
        case SERGENT:
            p=new Sergent(col);
        break;
        case LIEUTENANT:
            p=new Lieutenant(col);
        break;
        case CAPITAINE:
            p=new Capitaine(col);
        break;
        case COMMANDANT:
            p=new Commandant(col);
        break;
        case COLONEL:
            p=new Colonel(col);
        break;
        case GENERAL:
            p=new General(col);
        break;
        case MARECHAL:
            p=new Marechal(col);
        break;
        case DRAPEAU:
            p=new Drapeau(col);
        break;
        case VIDE:
        	p=new Piece(col);
    }
    return p;
}

char intToChar(int i){
	std::string chaine;
	std::stringstream stream;
	stream<<std::dec<<i;
	stream>>chaine;
	return chaine.c_str()[0];
}

int charToInt(char c){
	int i;
	std::stringstream stream;
	stream<<c;
	stream>>i;
	return i;
}

std::string intToString(int i){
	std::string chaine;
	std::stringstream stream;
	stream<<std::dec<<i;
	stream>>chaine;
	return chaine;
}
