# ifndef H_SERGENT
# define H_SERGENT

    # include "Unite.h"
    
    class Sergent : public Unite{
        public :
            // constructeur
            Sergent(bool col);
            // methodes
            virtual bool attack(Plateau* p,int x,int y);
            virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
