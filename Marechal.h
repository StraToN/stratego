# ifndef H_MARECHAL
# define H_MARECHAL

    # include "Unite.h"
    
    class Marechal : public Unite{
        public :
            // constructeur
            Marechal(bool col);
            // methodes
            virtual bool attack(Plateau* p,int x,int y);
            virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
