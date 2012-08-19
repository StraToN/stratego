# ifndef H_ESPION
# define H_ESPION

    # include "Unite.h"
    
    class Espion : public Unite{
        public :
            // constructeur
            Espion(bool col);
            // methodes
            virtual bool attack(Plateau* p,int x,int y);
            virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
