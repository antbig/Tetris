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
	Fichier pour gerer l'interface graphique
**/
#ifndef TETRIS_GUIMANAGER
#define TETRIS_GUIMANAGER





#define PANEL					1
#define PANEL_BACKGROUND		2

/**
	Fonction pour initialiser l'interface
**/
void Gui_init(void);

/**
	Pour supprimer la bordure de la fenetre
**/
void Gui_remove_Border(int panel, int image);


#endif