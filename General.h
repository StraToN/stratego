# ifndef H_GENERAL
# define H_GENERAL

    # include "Unite.h"
    
    class General : public Unite{
        public :
            //constructeur
            General(bool col);
            // methodes
            virtual bool attack(Plateau* p,int x,int y);
            virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
