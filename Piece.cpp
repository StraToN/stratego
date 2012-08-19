/*

Classe Piece

Superclasse de toutes les pieces

*/

# include "Piece.h"

// constructeur vide
Piece::Piece(){
    # ifdef DEBUG
    cout << "[" << this << "]Piece construite" << endl;
    # endif
}

// constructeur de copie
Piece::Piece(const Piece & piece){
    this->color=piece.color;
    # ifdef DEBUG
    cout << "[" << this << "]Piece " << getColorValue(piece.color) << " construite" << endl;
    # endif
}

// constructeur avec une couleur passee en parametre
Piece::Piece(bool col){
	this->color=col;
    # ifdef DEBUG
    cout << "[" << this << "]Piece " << getColorValue(col) << " construite" << endl;
    # endif
}

// destructeur
Piece::~Piece(){
    # ifdef DEBUG
    cout << "[" << this << "]Piece " << getColorValue(col) << " detruite" << endl;
    # endif
}

// retourne la couleur de la piece
bool Piece::getColor(){
	return this->color;
}

// retourne l'identifiant
int Piece::getID(){
	return PIECE;
}

// methodes redefinies dans les classes filles
char Piece::getCharID(){
    return C_CACHEE;
}
string Piece::getName(){
    return "";
}
