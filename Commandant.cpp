/*

Classe Commandant

*/

# include "Commandant.h"

// constructeur
Commandant::Commandant(bool col) : Unite(col,7){
    # ifdef DEBUG
    cout << "[" << this << "]Commandant " << getColorValue(col) << " construit" << endl;
    # endif
}

// attaque la piece situee en (x,y) sur le plateau p
bool Commandant::attack(Plateau* p,int x,int y){
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
int Commandant::getID(){
	return COMMANDANT;
}

// retourne le caractere d'affichage
char Commandant::getCharID(){
    return C_COMMANDANT;
}

// retourne le nom
string Commandant::getName(){
    return N_COMMANDANT;
}
