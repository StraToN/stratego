# ifndef H_BOX
# define H_BOX

    # include <map>
    # include "ListPiece.h"

    class Box{
        private :
            // attributs
            map<int,ListPiece*>* pieces;
            ListPiece* l_bombe;
            ListPiece* l_espion;
            ListPiece* l_eclaireur;
            ListPiece* l_demineur;
            ListPiece* l_sergent;
            ListPiece* l_lieutenant;
            ListPiece* l_capitaine;
            ListPiece* l_commandant;
            ListPiece* l_colonel;
            ListPiece* l_general;
            ListPiece* l_marechal;
            ListPiece* l_drapeau;
            bool color;
            
        public :
            // constructeur et destructeur
            Box(bool col);
            ~Box();
            // methodes
            void putIn(Piece* p);
            Piece* takeOut(int id);
            int totalCount();
            int count(int type);
            void clearAll();
    };

# endif
