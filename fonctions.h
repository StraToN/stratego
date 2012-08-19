# ifndef H_FONCTIONS
# define H_FONCTIONS

    # include "constantes.h"
    # include "Piece.h"
    # include <string>
    
    char idToChar(int id);
    int charToId(char c);
    string charToName(char c);
    string getColorValue(bool col);
    bool isInArea(bool player,int ordonnee);
    Piece* createPiece(int id,bool col);
    char intToChar(int i);
    int charToInt(char c);
    std::string intToString(int i);
    
# endif
