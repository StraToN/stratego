/*

Classe Colonel

*/

# include "Colonel.h"

// constructeur
Colonel::Colonel(bool col) : Unite(col,8){
    # ifdef DEBUG
    cout << "[" << this << "]Colonel " << getColorValue(col) << " construit" << endl;
    # endif
}

// attaque la piece situee en (x,y) sur le plateau p
bool Colonel::attack(Plateau* p,int x,int y){
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
    # ifdef DEBUG
    cout << p->getPiece(x,y);
    # endif
    return win;
}

// retourne l'identifiant
int Colonel::getID(){
	return COLONEL;
}

// retourne le caractere d'affichage
char Colonel::getCharID(){
    return C_COLONEL;
}

// retourne le nom
string Colonel::getName(){
    return N_COLONEL;
}
