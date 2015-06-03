/******************************************************
**													 **
**  PROJET TETRIS 2015								 **
**													 **
**   Par Leonard Antoine <antoine.leonard@u-psud.fr> **
**    et David   Pierre  <pierre.david1@u-psud.fr>   **
**													 **
**	 tous droits réservés							 **
** 													 **
*******************************************************/

#include "GameManager.h"
#include "SoundManager.h"
#include "GuiManager.h"

static unsigned char Game_Pieces[9];

static unsigned char Game_MAP[24][12];

static unsigned char Game_etat = 0;

/**
	Pour initialiser la partie
**/
void Game_init(void) {
	//On prepare l'interface
	Gui_init();
	
	//On lance la musique
	//Start_Background_Musique(); 
	
	//On initialise la liste de pieces
	Game_generate_piece();
}

/**
	Pour debuter une partie
**/
void Game_start(void) {
	
	
}

/**
	Pour arreter une partie
**/
void Game_stop(void) {
	
	
}

/**
	Pour obtenir le type de la piece suivante
**/
char Game_get_next_piece(void) {
	return 0;
}

/**
	Pour obtenir le type de la piece actuel
**/
char Game_get_piece(void) {
	return 0;
}

/**
	Pour passer à la piece suivante 
**/
void Game_change_piece(void) {
	
}

/**
	Pour generer le groupe de piece suivant
**/
void Game_generate_piece(void) {
	
}