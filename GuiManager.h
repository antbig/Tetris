/******************************************************
**													 **
**  PROJET TETRIS 2015								 **
**													 **
**   Par Leonard Antoine <antoine.leonard@u-psud.fr> **
**    et David   Pierre  <pierre.david1@u-psud.fr>   **
**													 **
**	 tous droits rÃƒÂ©servÃƒÂ©s							 **
** 													 **
*******************************************************/

/**
	Fichier pour gerer l'interface graphique
**/
#ifndef TETRIS_GUIMANAGER
#define TETRIS_GUIMANAGER


#include "Structure.h"


#define PANEL					1
#define PANEL_BACKGROUND		2
#define PANEL_TABLE_NEXT		3
#define PANEL_TABLE				4
#define PANEL_JOUER				5
#define PANEL_CLOSE				6
#define PANEL_GAME_TIMER		7
#define PANEL_SCORE				8
#define PANEL_MUSIQUE			9
#define PANEL_REPRENDRE			10
#define PANEL_MSG_LEVEL			11
#define PANEL_MSG_OBJECTIF		12

static int gPostHndl = -1;  

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
	Paramètre :
		Int panel		=> L'identifiant du panel dont on veut retirer la bordure
		Int image		=> L'identifiant du contrôle qui représente la nouvelle fenêtre
**/
void Gui_remove_Border(int panel, int image);

/**
	Pour recuperer l'interface
	Renvoie :
		L'identifiant du panel
**/
int Gui_get_Interface(void);

/**
	Pour obtenir l'image aÂ  partir de la couleur
	Paramètre :
		Int color		=> La couleur de la pièce que l'on veut obtenir
	Renvoie :
		Int				=> Un entier correspondant à l'identifiant de la pièce
**/
int Gui_get_IMG(int color);

/**
	Pour rafraichir les cases
**/
void Gui_update_display(void);

/**
	Pour rafraichir les cases de la piece en mouvement
**/
void Gui_update_falling_piece(void);

/**
	Pour afficher la piece suivante
**/
void Gui_update_next_piece(void);

/**
	Pour activer le timer
**/
void Gui_Timer_enable(void);

/**
	Pour desactiver le timer
**/
void Gui_Timer_disable(void);

/**
	Pour savoir si le timer est actif
	Renvoie :
		Int				=> Un booléen indiquant si le timer est actif (0 non, 1 oui)
**/
int Gui_Timer_isEnable(void);

/**
	Pour definir l'intervalle du timer
	Paramètre :
		Double interval	=> La nouvelle valeur entre 2 ticks de timer
**/
void Gui_Timer_set_interval(double interval);

/**
	Pour supprimer l'ancienne piece
	Paramètre :
		Piece_S piece	=> La pièce à effacer
**/
void Gui_clear_old_piece(Piece_S piece);

/**
	Pour afficher le score
	Paramètre :
		Int score		=> La nouvelle valeur du score à afficher
**/
void Gui_set_score(int score);

/**
	Pour afficher la piece fantome
	Paramètre :
		Piece_S piece	=> La pièce dont il faut afficher le fantôme
**/
void Gui_display_gosth(Piece_S piece);

/**
	Pour mettre le bouton avec le texte en cours de partie
**/
void Gui_set_boutton_ingame(void);

/**
	Pour mettre les boutons avec le texte en pause
**/
void Gui_set_boutton_pause(void);

/**
	Pour mettre les boutons avec le texte lors d'une defaite
**/
void Gui_set_boutton_lose(void);

/**
	Pour afficher le niveau
**/
void Gui_display_level(void);

#endif
