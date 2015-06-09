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
  Fichier pour la gestion du son du jeu
**/
#ifndef TETRIS_SOUNDMANAGER
#define TETRIS_SOUNDMANAGER

/**
  Fonction pour lancer la musique en arriere plan
**/
short Start_Background_Musique(void);

short Play_Move_Sound(void); 

/**
	Pour arreter la musique
**/
void Stop_musique(void);

/**
	Pour activer/desactiver la musique
**/
void Toggle_musique(void);

#endif
