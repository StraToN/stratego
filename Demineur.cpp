/*

Classe Demineur

*/

# include "Demineur.h"

// constructeur
Demineur::Demineur(bool col) : Unite(col,3){
    # ifdef DEBUG
    cout << "[" << this << "]Demineur " << getColorValue(col) << " construit" << endl;
    # endif
}

// attaque la piece situee en (x,y) sur le plateau p
bool Demineur::attack(Plateau* p,int x,int y){
    # ifdef DEBUG
    cout << "[" << this << "]" << this->getName() << " attaque [" << p->getPieceID(x,y) << "]" << p->getPiece(x,y)->getName() << " : ";
    # endif
    // this boolean shows if the attacker will be dead or not dead
    bool win;
    if ((p->getPieceID(x,y)==DRAPEAU)||(p->getPieceID(x,y)==BOMBE)){
        p->removePieceFromGame(x,y);
        win=true;
        if (p->getPieceID(x,y)==DRAPEAU){
            p->notifyVictory(this->getColor());
        }
    }
    else{
        // la piece attaquee est une unite
        if ((dynamic_cast<Unite*>(p->getPiece(x,y)))->getPower()<this->power){
            p->removePieceFromGame(x,y);
            win=true;
        }
        else{
            if ((dynamic_cast<Unite*>(p->getPiece(x,y)))->getPower()==this->power){
                p->removePieceFromGame(x,y);
            }
            win=false;
        }
    }
    # ifdef DEBUG
    cout << p->getPiece(x,y);
    # endif
    return win;
}

// retourne l'identifiant
int Demineur::getID(){
	return DEMINEUR;
}

// retourne le caractere d'affichage
char Demineur::getCharID(){
    return C_DEMINEUR;
}

// retourne le nom
string Demineur::getName(){
    return N_DEMINEUR;
}
