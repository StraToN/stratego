/*

Definitions de constantes :
    - identifiants
    - caracteres d'affichage
    - noms
    - couleurs

Definitions pour la compilation conditionnelle

*/

# ifndef H_CONSTANTES
# define H_CONSTANTES
	
	// definition des identifiants
	# define VIDE 0
	# define PIECE 1
	# define UNITE 2
	# define CACHEE 3
	# define BOMBE 4
	# define ESPION 5
	# define ECLAIREUR 6
	# define DEMINEUR 7
	# define SERGENT 8
	# define LIEUTENANT 9
	# define CAPITAINE 10
	# define COMMANDANT 11
	# define COLONEL 12
	# define GENERAL 13
	# define MARECHAL 14
	# define DRAPEAU 15
	
	// definition des caracteres d'affichages
	# define C_VIDE ' '
	# define C_CACHEE '?'
	# define C_BOMBE 'B'
	# define C_ESPION '0'
	# define C_ECLAIREUR '1'
	# define C_DEMINEUR '2'
	# define C_SERGENT '3'
	# define C_LIEUTENANT '4'
	# define C_CAPITAINE '5'
	# define C_COMMANDANT '6'
	# define C_COLONEL '7'
	# define C_GENERAL '8'
	# define C_MARECHAL '9'
	# define C_DRAPEAU 'D'
	
	// definition des noms
	# define N_BOMBE "Bombe"
	# define N_ESPION "Espion"
	# define N_ECLAIREUR "Eclaireur"
	# define N_DEMINEUR "Demineur"
	# define N_SERGENT "Sergent"
	# define N_LIEUTENANT "Lieutenant"
	# define N_CAPITAINE "Capitaine"
	# define N_COMMANDANT "Commandant"
	# define N_COLONEL "Colonel"
	# define N_GENERAL "General"
	# define N_MARECHAL "Marechal"
	# define N_DRAPEAU "Drapeau"
	
	// definition des quantites de chaque piece
	# define QTE_BOMBE 6
	# define QTE_ESPION 1
	# define QTE_ECLAIREUR 8
	# define QTE_DEMINEUR 5
	# define QTE_SERGENT 4
	# define QTE_LIEUTENANT 4
	# define QTE_CAPITAINE 4
	# define QTE_COMMANDANT 3
	# define QTE_COLONEL 2
	# define QTE_GENERAL 1
	# define QTE_MARECHAL 1
	# define QTE_DRAPEAU 1
	
	// definition des couleurs
	# define RED true
	# define BLUE false
	
	# define RED_VALUE "rouge"
	# define BLUE_VALUE "bleu"
	
	# define C_RED 'r'
	# define C_BLUE 'b'
	
	// définition du caractère d'information de début de partie
	# define C_GO 'g'
	
/*************************************************************************/

/* ajouter ou supprimer des commentaires // selon les besoins */
	
//  # define WINDOWS
//  # define LINUX
//  # define DEBUG

/*************************************************************************/
	
	# include <iostream>
	# include <string>

	using namespace std;
	
	const int NB_PIECES_DIFFERENTES=12;
	const int TAILLE_PLATEAU=10;
	
# endif
