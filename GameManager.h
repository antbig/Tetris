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

/**
	Fichier de gestion de la partie.
**/
#ifndef TETRIS_GAMEMANAGER
#define TETRIS_GAMEMANAGER
/**
	Pour initialiser la partie
**/
void Game_init(void);

/**
	Pour debuter une partie
**/
void Game_start(void);

/**
	Pour arreter une partie
**/
void Game_stop(void);

/**
	Pour obtenir le type de la piece suivante
**/
char Game_get_next_piece(void);

/**
	Pour obtenir le type de la piece actuel
**/
char Game_get_piece(void);

/**
	Pour passer à la piece suivante 
**/
void Game_change_piece(void);

/**
	Pour generer le groupe de piece suivant
**/
void Game_generate_piece(void);

#endif