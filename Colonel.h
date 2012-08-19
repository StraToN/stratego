# ifndef H_COLONEL
# define H_COLONEL

    # include "Unite.h"
    
    class Colonel : public Unite{
        public :
            // constructeur
            Colonel(bool col);
            // methodes
            virtual bool attack(Plateau* p,int x,int y);
            virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
