/*

Classe Marechal

*/

# include "Marechal.h"

// constructeur
Marechal::Marechal(bool col) : Unite(col,10){
    # ifdef DEBUG
    cout << "[" << this << "]Marechal " << getColorValue(col) << " construit" << endl;
    # endif
}

// attaque la piece situee en (x,y) sur le plateau p
bool Marechal::attack(Plateau* p,int x,int y){
    # ifdef DEBUG
    cout << "[" << this << "]" << this->getName() << " attaque [" << p->getPieceID(x,y) << "]" << p->getPiece(x,y)->getName() << " : ";
    # endif
    // this boolean shows if the attacker will be dead or not dead
    bool win;
    if (p->getPieceID(x,y)==DRAPEAU){
        win=true;
        p->notifyVictory(this->getColor());
    }
    else{
        if (p->getPieceID(x,y)==BOMBE){
            win=false;
        }
        else{
            // la piece attaquee est une unite
            if (((dynamic_cast<Unite*>(p->getPiece(x,y)))->getPower())==this->power){
                win=false;
            }
            else{
                win=true;
            }
        }
    }
    p->removePieceFromGame(x,y);
    # ifdef DEBUG
    cout << p->getPiece(x,y);
    # endif
    return win;
}

// retourne l'identifiant
int Marechal::getID(){
	return MARECHAL;
}

// retourne le caractere d'affichage
char Marechal::getCharID(){
    return C_MARECHAL;
}

// retourne le nom
string Marechal::getName(){
    return N_MARECHAL;
}
