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
	Param�tres :
		char *username[]	=> Nom du joueur dont on veut retrouver le profil
		User_profil			=> Pointeur vers le profil cible vers lequel on transf�re les donn�es dans le fichier de sauvegarde
**/
void File_get_user(char *username[50], User_profil *newProfil);

/**
	Pour sauvegarder le profil d'un utilisateur
	Param�tre :
		User_profil *Profil	=> Profil de joueur � sauvegarder
**/
void File_save_user(User_profil *Profil);

/**
	Pour r�cup�rer le fichier de high-score
	Param�tre :
		Score *scores		=> Pointeur vers un tableau de Score qui prendra les valeurs des highscores
**/
Get_highscore(Score *scores);

/**
	Pour r��crire le fichier de high-score
	Param�tre :
		Score* scores		=> Pointeur vers le tableau de Score � sauvegarder
**/
void Update_highscore(Score* scores);



#endif
