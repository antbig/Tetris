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

#ifndef TETRIS_FILEMANAGER
#define TETRIS_FILEMANAGER

#include "Structure.h"
/**
	Pour sauvegarder la partie dans un fichier
**/
void File_save_game(void);

/**
	Pour restorer la partie
**/
void File_restor_game(void);

/**
	Pour obtenir le profil d'un joueur
**/
void File_get_user(char *username[50], User_profil *newProfil);

/**
	Pour sauvegarder le profil d'un utilisateur
**/
void File_save_user(User_profil *Profil);


#endif