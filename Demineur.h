# ifndef H_DEMINEUR
# define H_DEMINEUR

    # include "Unite.h"
    
    class Demineur : public Unite{
        public :
            // constructeur
            Demineur(bool col);
            // methodes
            virtual bool attack(Plateau* p,int x,int y);
            virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
