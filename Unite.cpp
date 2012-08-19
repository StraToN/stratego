/*

Classe Unite

Superclasse de toutes les unites, c'est-à-dire des pieces mobiles

*/

# include "Unite.h"

// constructeur avec une couleur et une force passes en parametre
Unite::Unite(bool col,int pow) : Piece(col){
	this->power=pow;
    # ifdef DEBUG
    cout << "[" << this << "]Unite " << getColorValue(col) << " construite" << endl;
    # endif
}

// constructeur de copie
Unite::Unite(const Unite & unite) : Piece(unite){
    power=unite.power;
    # ifdef DEBUG
    cout << "[" << this << "]Unite " << getColorValue(unite.color) << " construite" << endl;
    # endif
}

// retourne la force
int Unite::getPower(){
    return this->power;
}

// retourne l'identifiant
int Unite::getID(){
	return UNITE;
}
