# ifndef H_LISTPIECE
# define H_LISTPIECE

    # include "Piece.h"
    # include <list>

    class ListPiece{
    	private:
            // attributs
    		list<Piece*>* pieces;
    	public:
            // constructeurs et destructeur
    		ListPiece();
    		ListPiece(int size);
    		~ListPiece();
    		// methodes
    		int size();
    		void add(Piece* p);
    		Piece* remove();
    		void fill(int qte,int type,bool col);
    		Piece* get(int index);
    		void clear();
    		// exception
    		class BadIndexException{};
    };

# endif
