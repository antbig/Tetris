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
#define PANEL_TABLE				3
#define PANEL_JOUER				4
#define PANEL_CLOSE				5


/**
	Fonction pour initialiser l'interface
**/
void Gui_init(void);

/**
	Fonction pour afficher l'interface
**/
void Gui_display(void);

/**
	Pour supprimer la bordure de la fenetre
**/
void Gui_remove_Border(int panel, int image);

/**
	Pour recuperer l'interface
**/
int Gui_get_Interface(void);

/**
	Pour rafraichir les cases
**/
void Gui_update_display(void);


#endif
