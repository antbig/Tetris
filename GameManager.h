/******************************************************
**													 **
**  PROJET TETRIS 2015								 **
**													 **
**   Par Leonard Antoine <antoine.leonard@u-psud.fr> **
**    et David   Pierre  <pierre.david1@u-psud.fr>   **
**													 **
**	 tous droits reserves							 **
** 													 **
*******************************************************/

/**
	Fichier de gestion de la partie.
**/
#ifndef TETRIS_GAMEMANAGER
#define TETRIS_GAMEMANAGER

#include "Structure.h"
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
	Pour regarder si la partie est perdue
**/
void Game_set_lose(void);

/**
	Pour obtenir l'etat de la partie
**/
int Game_get_etat(void);

/**
	Pour obtenir la disposition des blocs
**/
unsigned char Game_get_MAP(int x, int y);

/**
	pour definir la piece
**/
void Game_set_MAP(int x, int y, unsigned char val);

/**
	Pour obtenir le type de la piece id
**/
char Game_get_next_piece(int id);

/**
	Pour definir le type de la piece id
**/
void Game_set_next_piece(int id, char val);

/**
	Pour obtenir le type de la piece actuelle
**/
Piece_S Game_get_piece(void);

/**
	Pour avoir le score
**/
long Game_get_score(void);

/**
	Pour definir le score
**/
void Game_set_score(long s);

/**
	Pour passer Ã  la piece suivante 
**/
void Game_change_piece(void);

/**
	Pour generer le groupe de pieces suivant
**/
void Game_generate_piece(void);

/**
	Pour faire descendre une piece
**/
void Game_Piece_fall(void);

/**
	Pour decaler une piece vers la droite
**/
void Game_Piece_move_right(void);

/**
	Pour decaler une piece vers la droite
**/
void Game_Piece_move_left(void);

/**
	Pour faire tourner une piece
**/
void Game_Piece_rotation(void);

/**
	Pour verifier que la piece est dans une position correcte
**/
int Game_check_position(Piece_S piece);

/**
	Pour verifier si la piece n'est pas au plus bas de sa capacite
**/
int Game_check_collision(void);

/**
	Pour detetcter les lignes completes
**/
void Game_check_complete_line(void);

/**
	Pour supprimer une ligne
**/
void Game_remove_line(int line);

/**
	Pour actualiser la piece fantome
**/
void Game_update_ghost_piece(void);

/**
	Pour mettre à jour le niveau
**/
void Update_leveling(int lignes);

/**
	Pour renvoyer le niveau atteint par le joueur
**/
int Get_level();

#endif
