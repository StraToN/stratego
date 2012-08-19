/*

Classe Drapeau

*/

# include "Drapeau.h"

// constructeur
Drapeau::Drapeau(bool col) : Piece(col){
    # ifdef DEBUG
    cout << "[" << this << "]Drapeau " << getColorValue(col) << " construit" << endl;
    # endif
}

// retourne l'identifiant
int Drapeau::getID(){
	return DRAPEAU;
}

// retourne le caractere d'affichage
char Drapeau::getCharID(){
    return C_DRAPEAU;
}

// retourne le nom
string Drapeau::getName(){
    return N_DRAPEAU;
}
