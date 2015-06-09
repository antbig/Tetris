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
	Fichier avec la liste des callback pour le jeux
**/
#ifndef TETRIS_CALLBACK
#define TETRIS_CALLBACK

#include <userint.h>
/**
	Callback sur le bouton pour quitter le jeux
**/
int CVICALLBACK CALLBACK_CLOSE (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

/**
	Callback sur le bouton Jouer/Stop
**/
int CVICALLBACK CALLBACK_JOUER (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

/**
	Callback sur le timer du jeux
**/
int CVICALLBACK TimerCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

/**
	Callback sur le panel, permet d'obtenir les fleches
**/
int CVICALLBACK PANEL_CALLBACK (int panel, int event, void *callbackData, int eventData1, int eventData2);

/**
	Callback sur le mouvement de la souris pour déplacer la fenetre
**/
int CVICALLBACK OnMouseMoveEvent (int panel, int message, unsigned int* wParam, unsigned int* lParam, void* callbackData);

/**
	Callback sur le save
**/
int CVICALLBACK CALLBACK_SAVEDATA (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

#endif