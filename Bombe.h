# ifndef H_BOMBE
# define H_BOMBE

    #include "Piece.h"
    
    class Bombe : public Piece{
    	public :
            // constructeur
    		Bombe(bool col);
    		// methodes
    		virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
