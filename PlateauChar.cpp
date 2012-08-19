/*

Classe PlateauChar

Represente le plateau de jeu avec des caracteres d'affichage pour chaque piece differente

*/

# include "PlateauChar.h"

// constructeur
PlateauChar::PlateauChar(){
    # ifdef DEBUG
    cout << "[" << this << "]PlateauChar construit" << endl;
    # endif
}

// destructeur
PlateauChar::~PlateauChar(){
    # ifdef DEBUG
    cout << "[" << this << "]Plateau detruit" << endl;
    # endif
}

// verifie que les coordonnees x et y sont valides
bool PlateauChar::checkForbiddenLocation(int x,int y){
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
bool PlateauChar::checkFreeLocation(int x,int y){
    return (plateau[x][y]==C_VIDE) ? true : false;
}

// verifie si la case est occupee par un ennemi
bool PlateauChar::checkEnnemyLocation(int x,int y){
    return (plateau[x][y]==C_CACHEE) ? true : false;
}

// verifie que la case (x,y) n'est pas interdite et est libre
bool PlateauChar::isFreeAndCorrectLocation(int x,int y){
    return checkFreeLocation(x,y)&&(!checkForbiddenLocation(x,y));
}

// verifie si les cases (x1,y1) et (x2,y2) sont adjacentes
bool PlateauChar::sideBySide(int x1,int y1,int x2,int y2){
    return (((x1==x2)&&(abs(y1-y2)==1))||((y1==y2)&&(abs(x1-x2)==1)));
}

// verifie la validite du deplacement d'un eclaireur
bool PlateauChar::checkLongMove(int xdep,int ydep,int xarr,int yarr){
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
        correct=isCorrectDestination(xarr,yarr);
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
        correct=isCorrectDestination(xarr,yarr);
    }
    return correct;
}

// la case d'arrivee doit etre libre ou occupee par un ennemi et non interdite
bool PlateauChar::isCorrectDestination(int x,int y){
    return (((checkFreeLocation(x,y))||(checkEnnemyLocation(x,y)))&&(!checkForbiddenLocation(x,y)));
}

// verifie si le deplacement de (xdep,ydep) vers (xarr,yarr) est correct
bool PlateauChar::isCorrectMove(int xdep,int ydep,int xarr,int yarr){
    // booleen correct a true si le deplacement est correct
    bool correct=false;
    if (plateau[xdep][ydep]!=C_ECLAIREUR){
        // la piece a deplacer n'est pas un eclaireur
        correct=(sideBySide(xdep,ydep,xarr,yarr)&&isCorrectDestination(xarr,yarr)) ? true : false;
    }
    else{
        // la piece a deplacer est un eclaireur
        correct=checkLongMove(xdep,ydep,xarr,yarr) ? true : false;
    }
    return correct;
}

// place la piece p donnee en parametre dans la case (x,y)
void PlateauChar::putPiece(char c,int x,int y){
    this->plateau[x][y]=c;
}

// retourne le caractere d'affichage de la piece situee en (x,y)
char PlateauChar::getCharID(int x,int y){
	return plateau[x][y];
}

// Deplace la piece situee en (xdep,ydep) vers (xarr,yarr).
// Le combat est engage si la case (xarr,yarr) est occupee par une piece ennemie.
// Cette methode sera appelee a chaque tour de chaque joueur et est precede
// par la methode isCorrectMove(xdep,ydep,xarr,yarr) qui determine
// si le coup joue est valide ou non.
void PlateauChar::move(int xdep,int ydep,int xarr,int yarr){
	char c=plateau[xdep][ydep];
	plateau[xdep][ydep]=C_VIDE;
	plateau[xarr][yarr]=c;
}

// retire une piece du plateau de jeu
void PlateauChar::removePieceFromGame(int x,int y){
	plateau[x][y]=C_VIDE;
}

// initialise la position des pieces d'un joueur donne en parametre
// a partir d'un tableau de caractere d'affichage
void PlateauChar::setInitialPosition(char pieces[]){    // position initiale des pieces du joueur rouge
    for (int i=0;i<(int)(sizeof(pieces)/sizeof(char));i++){
        putPiece(pieces[i],(i%10),(i/10));
        putPiece(C_CACHEE,((99-i)%10),((99-i)/10));
    }
    
}
