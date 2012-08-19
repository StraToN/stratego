/*

Classe Box

Représente la boite de rangement qui contient
toutes les pieces d'un joueur

*/

# include "Box.h"

// constructeur
Box::Box(bool col){
    // couleur de la boite
    this->color=col;
    // initialisation de la boite
    this->pieces=new map<int,ListPiece*>();
    // initialisation des listes des differentes pieces
    this->l_bombe=new ListPiece();
    this->l_espion=new ListPiece();
    this->l_eclaireur=new ListPiece();
    this->l_demineur=new ListPiece();
    this->l_sergent=new ListPiece();
    this->l_lieutenant=new ListPiece();
    this->l_capitaine=new ListPiece();
    this->l_commandant=new ListPiece();
    this->l_colonel=new ListPiece();
    this->l_general=new ListPiece();
    this->l_marechal=new ListPiece();
    this->l_drapeau=new ListPiece();
    // remplissages de ces listes
    l_bombe->fill(QTE_BOMBE,BOMBE,col);
    l_espion->fill(QTE_ESPION,ESPION,col);
    l_eclaireur->fill(QTE_ECLAIREUR,ECLAIREUR,col);
    l_demineur->fill(QTE_DEMINEUR,DEMINEUR,col);
    l_sergent->fill(QTE_SERGENT,SERGENT,col);
    l_lieutenant->fill(QTE_LIEUTENANT,LIEUTENANT,col);
    l_capitaine->fill(QTE_CAPITAINE,CAPITAINE,col);
    l_commandant->fill(QTE_COMMANDANT,COMMANDANT,col);
    l_colonel->fill(QTE_COLONEL,COLONEL,col);
    l_general->fill(QTE_GENERAL,GENERAL,col);
    l_marechal->fill(QTE_MARECHAL,MARECHAL,col);
    l_drapeau->fill(QTE_DRAPEAU,DRAPEAU,col);
    // insertion de ces listes dans la boite
    pieces->insert(make_pair(BOMBE,l_bombe));
    pieces->insert(make_pair(ESPION,l_espion));
    pieces->insert(make_pair(ECLAIREUR,l_eclaireur));
    pieces->insert(make_pair(DEMINEUR,l_demineur));
    pieces->insert(make_pair(SERGENT,l_sergent));
    pieces->insert(make_pair(LIEUTENANT,l_lieutenant));
    pieces->insert(make_pair(CAPITAINE,l_capitaine));
    pieces->insert(make_pair(COMMANDANT,l_commandant));
    pieces->insert(make_pair(COLONEL,l_colonel));
    pieces->insert(make_pair(GENERAL,l_general));
    pieces->insert(make_pair(MARECHAL,l_marechal));
    pieces->insert(make_pair(DRAPEAU,l_drapeau));
    # ifdef DEBUG
    cout << "[" << this << "]Box " << getColorValue(col) << " construite" << endl;
    # endif
}

// destructeur
Box::~Box(){
    // vide la boite
    this->pieces->clear();
    // supprime toutes les listes
    delete l_bombe;
    delete l_espion;
    delete l_eclaireur;
    delete l_demineur;
    delete l_sergent;
    delete l_lieutenant;
    delete l_capitaine;
    delete l_commandant;
    delete l_colonel;
    delete l_general;
    delete l_marechal;
    delete l_drapeau;
    # ifdef DEBUG
    cout << "[" << this << "]Box " << getColorValue(col) << " detruite" << endl;
    # endif
}

// range la piece passee en parametre dans la boite
void Box::putIn(Piece* p){
    map<int,ListPiece*>::const_iterator ci=pieces->find(p->getID());
    ((*ci).second)->add(p);
}

// retire une piece de type donne en parametre de la boite
Piece* Box::takeOut(int id){
    map<int,ListPiece*>::const_iterator ci=pieces->find(id);
    return ((*ci).second)->remove();
}

// Vide une boite
void Box::clearAll(){
    l_espion->clear();
    l_eclaireur->clear();
    l_demineur->clear();
    l_sergent->clear();
    l_lieutenant->clear();
    l_capitaine->clear();
    l_commandant->clear();
    l_colonel->clear();
    l_general->clear();
    l_marechal->clear();
    l_drapeau->clear();
    l_bombe->clear();
}

// Compte le nombre de pieces restantes dans la boite
int Box::totalCount(){
    return (l_bombe->size()+
            l_espion->size()+
            l_eclaireur->size()+
            l_demineur->size()+
            l_sergent->size()+
            l_lieutenant->size()+
            l_capitaine->size()+
            l_commandant->size()+
            l_colonel->size()+
            l_general->size()+
            l_marechal->size()+
            l_drapeau->size());
}

// Compte le nombre de pieces de type donne restantes
int Box::count(int type){
    map<int,ListPiece*>::const_iterator ci=pieces->find(type);
    return ((*ci).second)->size();
}
