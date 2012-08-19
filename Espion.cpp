/*

Classe Espion

*/

# include "Espion.h"

// constructeur
Espion::Espion(bool col) : Unite(col,1){
    # ifdef DEBUG
    cout << "[" << this << "]Espion " << getColorValue(col) << " construit" << endl;
    # endif
}

// attaque la piece situee en (x,y) sur le plateau p
bool Espion::attack(Plateau* p,int x,int y){
    # ifdef DEBUG
    cout << "[" << this << "]" << this->getName() << " attaque [" << p->getPieceID(x,y) << "]" << p->getPiece(x,y)->getName() << " : ";
    # endif
    // this boolean shows if the attacker will be dead or not dead
    bool win;
    if ((p->getPieceID(x,y)==DRAPEAU)||(p->getPieceID(x,y)==MARECHAL)){
        p->removePieceFromGame(x,y);
        win=true;
        if (p->getPieceID(x,y)==DRAPEAU){
            p->notifyVictory(this->getColor());
        }
    }
    else{
        if (p->getPieceID(x,y)==BOMBE){
            p->removePieceFromGame(x,y);
        }
        else{
            // la piece attaquee est une unite autre qu'un Marechal
            if ((dynamic_cast<Unite*>(p->getPiece(x,y)))->getPower()==this->power){
                p->removePieceFromGame(x,y);
            }
        }
        win=false;
    }
    # ifdef DEBUG
    cout << p->getPiece(x,y);
    # endif
    return win;
}

// retourne l'identifiant
int Espion::getID(){
	return ESPION;
}

// retourne le caractere d'affichage
char Espion::getCharID(){
    return C_ESPION;
}

// retourne le nom
string Espion::getName(){
    return N_ESPION;
}
