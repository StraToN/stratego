CPP=g++-4.2 
CFLAGS= -Wall -ansi -pedantic `sdl-config --cflags` -g 
LDFLAGS= `sdl-config --libs` -lSDL_net -lSDL_image -lSDL_ttf 
EXEC= Strategwar 

OBJ  =  Serveur.o PlateauChar.o Client.o fonctions.o Box.o ListPiece.o Plateau.o AffichageTexte.o Affichage.o Piece.o Unite.o Bombe.o Drapeau.o Espion.o Eclaireur.o Demineur.o Sergent.o Lieutenant.o Capitaine.o Commandant.o Colonel.o General.o Marechal.o 


all: ${EXEC} 

${EXEC}: ${OBJ} main.o 
	${CPP} $(CFLAGS) ${OBJ} main.o -o ${EXEC} ${LDFLAGS} 

main.o: main.cpp
	${CPP} $(CFLAGS)-c main.cpp -o main.o 

Piece.o: Piece.cpp Piece.h
	$(CPP) $(CFLAGS) -c Piece.cpp -o Piece.o

Unite.o: Unite.cpp Unite.h
	$(CPP) $(CFLAGS) -c Unite.cpp -o Unite.o

Bombe.o: Bombe.cpp Bombe.h
	$(CPP) $(CFLAGS) -c Bombe.cpp -o Bombe.o

Drapeau.o: Drapeau.cpp Drapeau.h
	$(CPP) $(CFLAGS) -c Drapeau.cpp -o Drapeau.o

Espion.o: Espion.cpp Espion.h
	$(CPP) $(CFLAGS) -c Espion.cpp -o Espion.o

Eclaireur.o: Eclaireur.cpp Eclaireur.h
	$(CPP) $(CFLAGS) -c Eclaireur.cpp -o Eclaireur.o

Demineur.o: Demineur.cpp Demineur.h
	$(CPP) $(CFLAGS) -c Demineur.cpp -o Demineur.o

Sergent.o: Sergent.cpp Sergent.h
	$(CPP) $(CFLAGS) -c Sergent.cpp -o Sergent.o

Lieutenant.o: Lieutenant.cpp Lieutenant.h
	$(CPP) $(CFLAGS) -c Lieutenant.cpp -o Lieutenant.o

Capitaine.o: Capitaine.cpp Capitaine.h
	$(CPP) $(CFLAGS) -c Capitaine.cpp -o Capitaine.o

Commandant.o: Commandant.cpp Commandant.h
	$(CPP) $(CFLAGS) -c Commandant.cpp -o Commandant.o

Colonel.o: Colonel.cpp Colonel.h
	$(CPP) $(CFLAGS) -c Colonel.cpp -o Colonel.o

General.o: General.cpp General.h
	$(CPP) $(CFLAGS) -c General.cpp -o General.o

Marechal.o: Marechal.cpp Marechal.h
	$(CPP) $(CFLAGS) -c Marechal.cpp -o Marechal.o

Affichage.o: Affichage.cpp Affichage.h
	$(CPP) $(CFLAGS) -c Affichage.cpp -o Affichage.o

AffichageTexte.o: AffichageTexte.cpp AffichageTexte.h
	$(CPP) $(CFLAGS) -c AffichageTexte.cpp -o AffichageTexte.o
	
Plateau.o: Plateau.cpp Plateau.h
	$(CPP) $(CFLAGS) -c Plateau.cpp -o Plateau.o

ListPiece.o: ListPiece.cpp ListPiece.h
	$(CPP) $(CFLAGS) -c ListPiece.cpp -o ListPiece.o
	
Box.o: Box.cpp Box.h
	$(CPP) $(CFLAGS) -c Box.cpp -o Box.o

fonctions.o: fonctions.cpp fonctions.h
	$(CPP) $(CFLAGS) -c fonctions.cpp -o fonctions.o
	
Client.o: Client.cpp Client.h
	$(CPP) $(CFLAGS) -c Client.cpp -o Client.o
	
PlateauChar.o: PlateauChar.cpp PlateauChar.h
	$(CPP) $(CFLAGS) -c PlateauChar.cpp -o PlateauChar.o
	
Serveur.o: Serveur.cpp Serveur.h
	$(CPP) $(CFLAGS) -c Serveur.cpp -o Serveur.o

clean: 
	rm -rf $(OBJ) main.o $(EXEC)
