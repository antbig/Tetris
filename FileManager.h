/******************************************************
**													 **
**  PROJET TETRIS 2015								 **
**													 **
**   Par Leonard Antoine <antoine.leonard@u-psud.fr> **
**    et David   Pierre  <pierre.david1@u-psud.fr>   **
**													 **
**	 tous droits rÃ©servÃ©s							 **
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
	Paramètres :
		char *username[]	=> Nom du joueur dont on veut retrouver le profil
		User_profil			=> Pointeur vers le profil cible vers lequel on transfère les données dans le fichier de sauvegarde
**/
void File_get_user(char *username[50], User_profil *newProfil);

/**
	Pour sauvegarder le profil d'un utilisateur
	Paramètre :
		User_profil *Profil	=> Profil de joueur à sauvegarder
**/
void File_save_user(User_profil *Profil);

/**
	Pour récupérer le fichier de high-score
	Paramètre :
		Score *scores		=> Pointeur vers un tableau de Score qui prendra les valeurs des highscores
**/
Get_highscore(Score *scores);

/**
	Pour réécrire le fichier de high-score
	Paramètre :
		Score* scores		=> Pointeur vers le tableau de Score à sauvegarder
**/
void Update_highscore(Score* scores);



#endif
