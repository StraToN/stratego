# ifndef H_LIEUTENANT
# define H_LIEUTENANT

    #include "Unite.h"
    
    class Lieutenant : public Unite{
        public :
            // constructeur
            Lieutenant(bool col);
            // methodes
            virtual bool attack(Plateau* p,int x,int y);
            virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
