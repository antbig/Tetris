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
#include <windows.h>
#include "toolbox.h"
#include <ansi_c.h>
#include <userint.h>
#include <cvirte.h>	
#include "CallBack.h"
#include "GuiManager.h"
#include "GameManager.h"
#include "Structure.h"
#include "FileManager.h"
#include "SoundManager.h"

extern int gPostHndl;

/**
	Callback sur le bouton pour quitter le jeu
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
		if(Game_get_etat() == WAITING) {
			Game_start();
			SetCtrlAttribute (panel, control, ATTR_LABEL_TEXT , "STOP");
		} else if(Game_get_etat() == INGAME) {
			Game_stop();
			SetCtrlAttribute (panel, control, ATTR_LABEL_TEXT , "JOUER");
			File_save_game();
		} else {
			
		}
		
	}
	return 0;
}

/**
	Callback sur le timer du jeu
**/
int CVICALLBACK TimerCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			if(Game_get_etat() != INGAME) return 0;
			Game_Piece_fall();
		break;
	}
	return 0;
}

/**
	Callback sur le panel, permet d'obtenir les fleches
**/
int CVICALLBACK PANEL_CALLBACK (int panel, int event, void *callbackData, int eventData1, int eventData2) {
	if(Game_get_etat() != INGAME) return 0;
	switch (event)
	{
		case EVENT_KEYPRESS:
			if(eventData1 == VAL_RIGHT_ARROW_VKEY ) {
				
				Game_Piece_move_right();
				
			} else if(eventData1 == VAL_LEFT_ARROW_VKEY ) {
				
				Game_Piece_move_left();
				
			} else if(eventData1 == VAL_UP_ARROW_VKEY ) {

				Game_Piece_rotation();
			} else if(eventData1 == VAL_DOWN_ARROW_VKEY ) {
				Game_Piece_fall();
			}
			
		break;
	}
	return 0;
}

/**
	Callback sur le mouvement de la souris pour deplacer la fenetre
**/
int CVICALLBACK OnMouseMoveEvent (int panel, int message, unsigned int* wParam, unsigned int* lParam, void* callbackData) {
	static HWND hWnd	= 0;
	static int	bFirst	= TRUE;
	
	switch(message) {
		case EVENT_NEWHANDLE:
			gPostHndl = *wParam;
			hWnd = (HWND)*wParam;
		break;
		case WM_MOUSEMOVE:
			if(bFirst) {
				GetPanelAttribute(panel, ATTR_SYSTEM_WINDOW_HANDLE, (int*)&hWnd);
				bFirst = FALSE;
			}
			int LeftBtnDown;
			GetGlobalMouseState(NULL, NULL, NULL, &LeftBtnDown, NULL, NULL);
			if(LeftBtnDown) {
				SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
			}
		break;
	}
	return(0);
}


/**
	Callback sur le save
**/
int CVICALLBACK CALLBACK_SAVEDATA (int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	if(event = 34) {
		//printf("click");
	}
	return 0;
}

/**
	Callback sur le a musique
**/
int CVICALLBACK CALLBACK_MUSIQUE (int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	switch(event) {
		case EVENT_COMMIT:
			Toggle_musique();
		break;
	}
	
	return 0;
}
