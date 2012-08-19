/*

Classe Lieutenant

*/

# include "Lieutenant.h"

// constructeur
Lieutenant::Lieutenant(bool col) : Unite(col,5){
    # ifdef DEBUG
    cout << "[" << this << "]Lieutenant " << getColorValue(col) << " construit" << endl;
    # endif
}

// attaque la piece situee en (x,y) sur le plateau p
bool Lieutenant::attack(Plateau* p,int x,int y){
    # ifdef DEBUG
    cout << "[" << this << "]" << this->getName() << " attaque [" << p->getPieceID(x,y) << "]" << p->getPiece(x,y)->getName() << " : ";
    # endif
    // this boolean shows if the attacker will be dead or not dead
    bool win;
    if (p->getPieceID(x,y)==DRAPEAU){
        p->removePieceFromGame(x,y);
        win=true;
        p->notifyVictory(this->getColor());
    }
    else{
        if (p->getPieceID(x,y)==BOMBE){
            p->removePieceFromGame(x,y);
            win=false;
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
    }
    return win;
}

// retourne l'identifiant
int Lieutenant::getID(){
	return LIEUTENANT;
}

// retourne le caractere d'affichage
char Lieutenant::getCharID(){
    return C_LIEUTENANT;
}

// retourne le nom
string Lieutenant::getName(){
    return N_LIEUTENANT;
}
