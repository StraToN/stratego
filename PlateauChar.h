# ifndef H_PLATEAUCHAR
# define H_PLATEAUCHAR

    # include "fonctions.h"

    class PlateauChar{
    	private:
            // attributs
    		char plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
    		// methodes
            bool checkLongMove(int xdep,int ydep,int xarr,int yarr);
    		bool isFreeAndCorrectLocation(int x,int y);
            bool sideBySide(int x1,int y1,int x2,int y2);
    		bool checkEnnemyLocation(int x,int y);
    		bool isCorrectDestination(int x,int y);
    		
    	public:
            // constructeur et destructeur
    		PlateauChar();
    		~PlateauChar();
    		// methodes
    		char getCharID(int x,int y);
    		bool checkForbiddenLocation(int x,int y);
     		bool isCorrectMove(int xdep,int ydep,int xarr,int yarr);
    		void move(int xdep,int ydep,int xarr,int yarr);
    		void putPiece(char p,int x,int y);
    		void removePieceFromGame(int x,int y);
    		void setInitialPosition(char pieces[]);
    		bool checkFreeLocation(int x,int y);
    };

# endif
