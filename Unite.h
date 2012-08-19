# ifndef H_UNITE
# define H_UNITE

    # include "Plateau.h"
    # include "Piece.h"
    
    class Unite : public Piece{
        protected :
            // attribut
            int power;
            // constructeurs
            Unite(bool col,int pow);
            Unite(const Unite &);
        public :
            // methodes
            virtual bool attack(Plateau* p,int x,int y)=0;
            int getPower();
            virtual int getID();
    		virtual char getCharID()=0;
    		virtual string getName()=0;
    };

# endif
