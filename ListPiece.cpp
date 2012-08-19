/*

Classe ListPiece

Représente une liste de pieces qui sert a classer
les differents types de pieces dans la boite de pieces (Box)

*/

# include "ListPiece.h"
# include "Bombe.h"
# include "Capitaine.h"
# include "Colonel.h"
# include "Commandant.h"
# include "Demineur.h"
# include "Drapeau.h"
# include "Eclaireur.h"
# include "Espion.h"
# include "General.h"
# include "Lieutenant.h"
# include "Marechal.h"
# include "Sergent.h"

// constructeur qui initialise une liste vide
ListPiece::ListPiece(){
    this->pieces=new list<Piece*>();
    # ifdef DEBUG
    cout << "[" << this << "]ListPiece construite" << endl;
    # endif
}

// constructeur qui initialise une liste avec une taille donnee
ListPiece::ListPiece(int size){
    this->pieces=new list<Piece*>(size);
    # ifdef DEBUG
    cout << "[" << this << "]ListPiece construite" << endl;
    # endif
}

// destructeur qui efface les elements de la liste puis libere la memoire
ListPiece::~ListPiece(){
    this->pieces->clear();
    delete this->pieces;
    # ifdef DEBUG
    cout << "[" << this << "]ListPiece detruite" << endl;
    # endif
}

// retourne la taille de la liste
int ListPiece::size(){
    return pieces->size();
}

// ajoute une piece en tete de liste
void ListPiece::add(Piece* p){
    # ifdef DEBUG
    cout << "Taille de [" << this << "]ListPiece : " << this->size() << endl;
    # endif
    this->pieces->push_front(p);
    # ifdef DEBUG
    cout << "Taille de [" << this << "]ListPiece : " << this->size() << endl;
    # endif
}

// remplit la liste de pieces d'un type et d'une couleur donnes
void ListPiece::fill(int qte,int type,bool col){
    # ifdef DEBUG
    cout << "Taille de [" << this << "]ListPiece : " << this->size() << endl;
    # endif
    switch (type){
        case BOMBE:
            this->pieces->assign(qte,new Bombe(col));
        break;
        case ESPION:
            this->pieces->assign(qte,new Espion(col));
        break;
        case ECLAIREUR:
            this->pieces->assign(qte,new Eclaireur(col));
        break;
        case DEMINEUR:
            this->pieces->assign(qte,new Demineur(col));
        break;
        case SERGENT:
            this->pieces->assign(qte,new Sergent(col));
        break;
        case LIEUTENANT:
            this->pieces->assign(qte,new Lieutenant(col));
        break;
        case CAPITAINE:
            this->pieces->assign(qte,new Capitaine(col));
        break;
        case COMMANDANT:
            this->pieces->assign(qte,new Commandant(col));
        break;
        case COLONEL:
            this->pieces->assign(qte,new Colonel(col));
        break;
        case GENERAL:
            this->pieces->assign(qte,new General(col));
        break;
        case MARECHAL:
            this->pieces->assign(qte,new Marechal(col));
        break;
        case DRAPEAU:
            this->pieces->assign(qte,new Drapeau(col));
        break;
    }
    # ifdef DEBUG
    cout << "Taille de [" << this << "]ListPiece : " << this->size() << endl;
    # endif
}

// retire et retourne la premiere piece de la liste
Piece* ListPiece::remove(){
    # ifdef DEBUG
    cout << "Taille de [" << this << "]ListPiece : " << this->size() << endl;
    # endif
    Piece* piece=NULL;
    try{
        piece=this->get(0);
    }
    catch (BadIndexException){
        // erreur d'index
        cout << "Index Out Of Bounds Exception" << endl;
    }
    this->pieces->pop_front();
    # ifdef DEBUG
    cout << "Taille de [" << this << "]ListPiece : " << this->size() << endl;
    # endif
    return piece;
}

// Vide une liste
void ListPiece::clear(){
    this->pieces->clear();
}

// retourne la piece situee a l'index donne
Piece* ListPiece::get(int index){
    if ((index<0)||(index>=this->size())){
        // index hors des limites de la liste
        throw BadIndexException();
    }
    // placement de l'iterateur sur le premier element
    list<Piece*>::const_iterator ci=this->pieces->begin();
    for (int i=0;i<index;i++){
        ci++;
    }
    return *ci;
}
