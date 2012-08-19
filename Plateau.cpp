/*

Classe Plateau

Represente le plateau de jeu avec les boites de rangement des pieces (Box)
Cette classe est utilisee par le serveur, les clients n'etant qu'une 
simple representation graphique de la partie

*/

# include "Plateau.h"
# include "Unite.h"

// constructeur
Plateau::Plateau(){
    // le joueur rouge commence
    this->turn=RED;
    this->victory=NULL;
    // creation des boites de rangement des pieces des 2 joueurs
    this->redbox=new Box(RED);
    this->bluebox=new Box(BLUE);
    # ifdef DEBUG
    cout << "[" << this << "]Plateau construit" << endl;
    # endif
    
    for(int i=0;i<TAILLE_PLATEAU;i++){
		for(int j=0;j<TAILLE_PLATEAU;j++){
			plateau[j][i]=NULL;
		}
	}
    
}

// destructeur
Plateau::~Plateau(){
    // suppression des elements du plateau
    for (int i=0;i<TAILLE_PLATEAU;i++){
        for (int j=0;j<TAILLE_PLATEAU;j++){
            delete this->plateau[j][i];
        }
    }
    // suppression du plateau
    delete[] this->plateau;
    // suppression des boites de rangement
    delete this->redbox;
    delete this->bluebox;
    # ifdef DEBUG
    cout << "[" << this << "]Plateau detruit" << endl;
    # endif
}

// verifie que les coordonnees x et y sont valides
bool Plateau::checkForbiddenLocation(int x,int y){
    // booleen forbidden a false si les coordonnees sont autorisees
    bool forbidden=false;
    if ((x<0)||(x>=TAILLE_PLATEAU)||(y<0)||(y>=TAILLE_PLATEAU)||
        ((y==4||y==5)&&(x==2||x==3||x==6||x==7))){
        // coordonnees hors du plateau ou dans les etendues d'eau
        forbidden=true;
    }
    return forbidden;
}

// verifie que la case de coordonnees (x,y) est libre
bool Plateau::checkFreeLocation(int x,int y){
    return (getPiece(x,y)==NULL) ? true : false;
}

// verifie si la case est occupee par un ennemi
bool Plateau::checkEnnemyLocation(int x,int y,bool ennemy){
    // booleen located a true si une piece ennemie se trouve en (x,y)
    bool located=false;
    if (!checkFreeLocation(x,y)){
        // une piece est presente en (x,y)
        located=(getPiece(x,y)->getColor()==ennemy) ? true : false;
    }
    return located;
}

// verifie que la case (x,y) n'est pas interdite et est libre
bool Plateau::isFreeAndCorrectLocation(int x,int y){
    return checkFreeLocation(x,y)&&(!checkForbiddenLocation(x,y));
}

// verifie si les cases (x1,y1) et (x2,y2) sont adjacentes
bool Plateau::sideBySide(int x1,int y1,int x2,int y2){
    return (((x1==x2)&&(abs(y1-y2)==1))||((y1==y2)&&(abs(x1-x2)==1)));
}

// verifie la validite du deplacement d'un eclaireur
bool Plateau::checkLongMove(int xdep,int ydep,int xarr,int yarr){
    // booleen correct a true si le deplacement est valide
    bool correct=false;
    if (xdep==xarr){
        // abscisses de depart et d'arrivee identiques
        correct=true;
        if (ydep<yarr){
            // ordonnee de depart inferieure a celle d'arrivee
            for (int i=yarr-1;(i>ydep)&&correct;i--){
                // verification de toutes les cases entre (xdep,ydep) et (xarr,yarr)
                correct=isFreeAndCorrectLocation(xdep,i);
            }
        }
        else{
            // ordonnee de depart superieure a celle d'arrivee
            for (int i=yarr+1;(i<ydep)&&correct;i++){
                // verification de toutes les cases entre (xdep,ydep) et (xarr,yarr)
                correct=isFreeAndCorrectLocation(xdep,i);
            }
        }
        // verifie que la destination (xarr,yarr) est correcte
        correct=isCorrectDestination(xarr,yarr,!(getPiece(xdep,ydep)->getColor()));
    }
    if (ydep==yarr){
        // ordonnees de depart et d'arrivee identiques
        correct=true;
        if (xdep<xarr){
            // abscisse de depart inferieure a celle d'arrivee
            for (int i=xarr-1;(i>xdep)&&correct;i--){
                // verification de toutes les cases qui composent le trajet
                correct=isFreeAndCorrectLocation(i,ydep);
            }
        }
        else{
            // abscisse de depart superieure a celle d'arrivee
            for (int i=xarr+1;(i<xdep)&&correct;i++){
                // verification de toutes les cases qui composent le trajet
                correct=isFreeAndCorrectLocation(i,ydep);
            }
        }
        // verifie que la destination (xarr,yarr) est correcte
        correct=isCorrectDestination(xarr,yarr,!(getPiece(xdep,ydep)->getColor()));
    }
    return correct;
}

// la case d'arrivee doit etre libre ou occupee par un ennemi et non interdite
bool Plateau::isCorrectDestination(int x,int y,bool ennemy){
    return (((checkFreeLocation(x,y))||(checkEnnemyLocation(x,y,ennemy)))&&(!checkForbiddenLocation(x,y)));
}

// verifie si le deplacement de (xdep,ydep) vers (xarr,yarr) est correct
bool Plateau::isCorrectMove(int xdep,int ydep,int xarr,int yarr){
    // booleen correct a true si le deplacement est correct
    bool correct=false;
    if (getPieceID(xdep,ydep)==ECLAIREUR){
    	// la piece a deplacer est un eclaireur
        correct=checkLongMove(xdep,ydep,xarr,yarr) ? true : false;
    }
    else if(getPieceID(xdep,ydep)!=BOMBE&&getPieceID(xdep,ydep)!=DRAPEAU){
        // la piece a deplacer est ni un eclaireur ni une bombe ni un drapeau
        correct=(sideBySide(xdep,ydep,xarr,yarr)&&isCorrectDestination(xarr,yarr,!(getPiece(xdep,ydep)->getColor()))) ? true : false;
    }
    return correct;
}

// place la piece p donnee en parametre dans la case (x,y)
void Plateau::putPiece(Piece* p,int x,int y){
    this->plateau[x][y]=p;
}

// retourne l'identifiant de la piece situee en (x,y)
int Plateau::getPieceID(int x,int y){	
	int id;
	if (checkFreeLocation(x,y)){
		id = VIDE;
	}
	else{
		id=this->getPiece(x,y)->getID();
	}
    return id;
}

// retourne le caractere d'affichage de la piece situee en (x,y)
char Plateau::getCharID(int x,int y){
	char c;
	if (checkFreeLocation(x,y)){
		c=C_VIDE;
	}
	else{
		c=this->getPiece(x,y)->getCharID();
	}
    return c;
}

// retourne la piece situee en (x,y)
Piece* Plateau::getPiece(int x,int y){
    return this->plateau[x][y];
}

// Deplace la piece situee en (xdep,ydep) vers (xarr,yarr).
// Le combat est engage si la case (xarr,yarr) est occupee par une piece ennemie.
// Cette methode sera appelee a chaque tour de chaque joueur et est precede
// par la methode isCorrectMove(xdep,ydep,xarr,yarr) qui determine
// si le coup joue est valide ou non.
void Plateau::move(int xdep,int ydep,int xarr,int yarr){
    if (isFreeAndCorrectLocation(xarr,yarr)){
        // recuperation de la piece a deplacer dans une variable temporaire tmp
        Piece* tmp=this->getPiece(xdep,ydep);
        // retrait de la partie de la piece a deplacer
        this->removePieceFromGame(xdep,ydep);
        Piece* p=NULL;
        if (tmp->getColor()==RED){
            // piece identique a tmp sortie de la boite rouge
            p=redbox->takeOut(tmp->getID());
        }
        else{
            // piece identique a tmp sortie de la boite bleue
            p=bluebox->takeOut(tmp->getID());
        }
        // placement de la piece sortie de la boite dans la case d'arrivee (xarr,yarr)
        this->putPiece(p,xarr,yarr);
    }
    else{
        // attaque la piece situee dans la case d'arrivee (xarr,yarr)
        bool win=(dynamic_cast<Unite*>(this->getPiece(xdep,ydep)))->attack(this,xarr,yarr);
        if (win){
            // la piece attaquante a remporte le combat
            this->move(xdep,ydep,xarr,yarr);
        }
        else{
            // la piece attaquante est morte
            this->removePieceFromGame(xdep,ydep);
        }
    }
}

// retire une piece du plateau de jeu
void Plateau::removePieceFromGame(int x,int y){
    if (getPiece(x,y)->getColor()==RED){
        // rangement de la piece retiree dans la boite rouge
        this->redbox->putIn(getPiece(x,y));
    }
    else{
        // rangement de la piece retiree dans la boite bleue
        this->bluebox->putIn(getPiece(x,y));
    }
    // case (x,y) reinitialisee a NULL
    this->plateau[x][y]=NULL;
}

// supprime une piece
void Plateau::deletePiece(int x,int y){
    delete getPiece(x,y);
    this->plateau[x][y]=NULL;
}

// retourne le tour de jeu
bool Plateau::getTurn(){
    // booleen turn a true si c'est au joueur rouge de jouer
    return this->turn;
}

// passe au joueur suivant
void Plateau::changeTurn(){
    this->turn=!getTurn();
}

// initialise la position des pieces d'un joueur donne en parametre
// a partir d'un tableau de caractere d'affichage
void Plateau::setInitialPosition(bool player,char pieces[]){
    if (player==RED){
        // position initiale des pieces du joueur rouge
        for (int i=0;i<40;i++){
            // sortie de la boite de la piece correspondante au caractere d'affichage
            Piece* p=redbox->takeOut(charToId(pieces[i]));
            // placement de la piece sur le plateau
            this->putPiece(p,i%10,i/10);
        }
    }
    else{
        // position initiale des pieces du joueur bleu
        for (int i=0;i<40;i++){
            // sortie de la boite de la piece correspondante au caractere d'affichage
            Piece* p=bluebox->takeOut(charToId(pieces[i]));
            // placement de la piece sur le plateau
            this->putPiece(p,(99-i)%10,(99-i)/10);
        }
    }
}

// Place une piece de type donne du joueur donne dans la case (x,y)
void Plateau::setPiecePosition(bool player,char piece, int x, int y){
    Piece* p=NULL;
    if (player==RED){
        p=redbox->takeOut(charToId(piece));
    }
    else{
        p=bluebox->takeOut(charToId(piece));
    }
    this->putPiece(p,x,y);
}

// declare la victoire du joueur passe en parametre
void Plateau::notifyVictory(bool player){
    this->victory=new bool(player);
}

// Compte le nombre total de pieces restantes pour un joueur donne
int Plateau::nbTotalPiecesRestantes(bool player){
	return player==RED ? redbox->totalCount() : bluebox->totalCount();
}

// Compte le nombre de pieces restantes d'un type donne pour un joueur donne
int Plateau::nbPiecesRestantes(bool player,int type){
	return player==RED ? redbox->count(type) : bluebox->count(type);
}

// Vide la boite d'un joueur donne
void Plateau::clearAllElementsInBox(bool player){
    if (player==RED){
        redbox->clearAll();
    }
    else{
        bluebox->clearAll();
    }
}

bool* Plateau::getVictory() {
	return this->victory;
}
