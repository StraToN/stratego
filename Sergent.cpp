/*

Classe Sergent

*/

# include "Sergent.h"

// constructeur
Sergent::Sergent(bool col) : Unite(col,4){
    # ifdef DEBUG
    cout << "[" << this << "]Sergent " << getColorValue(col) << " construit" << endl;
    # endif
}

// attaque la piece situee en (x,y) sur le plateau p
bool Sergent::attack(Plateau* p,int x,int y){
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
int Sergent::getID(){
	return SERGENT;
}

// retourne le caractere d'affichage
char Sergent::getCharID(){
    return C_SERGENT;
}

// retourne le nom
string Sergent::getName(){
    return N_SERGENT;
}
