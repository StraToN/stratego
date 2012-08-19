CPP=g++
CFLAGS=-Wall -O3 `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_net -lSDL_image -lSDL_ttf

all: client serveur

client: Client.cpp
	${CPP} $(CFLAGS) ${LDFLAGS} Client.cpp -o client

serveur: Serveur.cpp
	${CPP} $(CFLAGS) ${LDFLAGS} Serveur.cpp -o serveur

clean: 
	rm -rf client serveur
