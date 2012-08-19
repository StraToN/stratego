# ifndef H_COMMANDANT
# define H_COMMANDANT

    #include "Unite.h"
    
    class Commandant : public Unite{
        public :
            // constructeur
            Commandant(bool col);
            // methodes
            virtual bool attack(Plateau* p,int x,int y);
            virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
