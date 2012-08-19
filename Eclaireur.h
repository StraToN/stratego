# ifndef H_ECLAIREUR
# define H_ECLAIREUR

    # include "Unite.h"

    class Eclaireur : public Unite{
        public :
            // constructeur
            Eclaireur(bool col);
            // methodes
            virtual bool attack(Plateau* p,int x,int y);
            virtual int getID();
            virtual char getCharID();
            virtual string getName();
    };

# endif
