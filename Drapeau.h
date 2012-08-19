# ifndef H_DRAPEAU
# define H_DRAPEAU

    # include "Piece.h"
    
    class Drapeau : public Piece{
        public :
            // constructeur
            Drapeau(bool col);
            // methodes
            virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
