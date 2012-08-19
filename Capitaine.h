# ifndef H_CAPITAINE
# define H_CAPITAINE

    # include "Unite.h"
    
    class Capitaine : public Unite{
        public :
            // constructeur
            Capitaine(bool col);
            // methodes
            virtual bool attack(Plateau* p,int x,int y);
            virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
