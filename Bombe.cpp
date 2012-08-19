/*

Classe Bombe

*/

#include "Bombe.h"

// constructeur
Bombe::Bombe(bool col) : Piece(col){
    # ifdef DEBUG
    cout << "[" << this << "]Bombe " << getColorValue(col) << " construite" << endl;
    # endif
}

// retourne l'identifiant
int Bombe::getID(){
	return BOMBE;
}

// retourne le caractere d'affichage
char Bombe::getCharID(){
    return C_BOMBE;
}

// retourne le nom
string Bombe::getName(){
    return N_BOMBE;
}
