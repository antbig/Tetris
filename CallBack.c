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
#include <userint.h>
#include <cvirte.h>	
#include "CallBack.h"
#include "GuiManager.h"
#include "GameManager.h"

/**
	Callback sur le bouton pour quitter le jeux
**/
int CVICALLBACK CALLBACK_CLOSE (int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	if( event == EVENT_LEFT_CLICK_UP)
			QuitUserInterface (0);
	
	return 0;
}

/**
	Callback sur le bouton Jouer/Stop
**/
int CVICALLBACK CALLBACK_JOUER (int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	if(event == 34) {//Click
		
	}
	return 0;
}
