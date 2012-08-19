# ifndef H_PLATEAU
# define H_PLATEAU

    # include "Box.h"
    # include "fonctions.h"

    class Plateau{
    	private:
            // attributs
    		Piece* plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
    		Box* redbox;
    		Box* bluebox;
    		bool turn;
    		bool* victory;
    		// methodes
            bool checkLongMove(int xdep,int ydep,int xarr,int yarr);
    		bool isFreeAndCorrectLocation(int x,int y);
            bool sideBySide(int x1,int y1,int x2,int y2);
    		bool checkEnnemyLocation(int x,int y,bool ennemy);
    		bool isCorrectDestination(int x,int y,bool ennemy);
    		
    	public:
            // constructeur et destructeur
    		Plateau();
    		~Plateau();
    		// methodes
    		bool getTurn();
    		void changeTurn();
    		int getPieceID(int x,int y);
    		char getCharID(int x,int y);
     		Piece* getPiece(int x,int y);
    		bool checkForbiddenLocation(int x,int y);
     		bool isCorrectMove(int xdep,int ydep,int xarr,int yarr);
    		void move(int xdep,int ydep,int xarr,int yarr);
    		void putPiece(Piece* p,int x,int y);
    		void removePieceFromGame(int x,int y);
    		void deletePiece(int x,int y);
    		void setInitialPosition(bool player,char pieces[]);
    		void setPiecePosition(bool player,char piece, int x, int y);
    		void notifyVictory(bool player);
    		bool checkFreeLocation(int x,int y);
    		int nbTotalPiecesRestantes(bool player);
    		int nbPiecesRestantes(bool player,int type);
    		void clearAllElementsInBox(bool player);
    		bool* getVictory();
    };

# endif
