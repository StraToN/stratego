# ifndef H_PIECE
# define H_PIECE

    # include "constantes.h"
    
    class Piece{
    	protected :
            // attribut
    		bool color;     // true for player 1 (red) and false for player 2 (blue)
    	public :
            // constructeurs et destructeur
            Piece();
            Piece(const Piece &);
    		Piece(bool col);
    		virtual ~Piece();
    		// methodes
    		bool getColor();
    		virtual int getID();
    		virtual char getCharID();
    		virtual string getName();
    };

# endif
