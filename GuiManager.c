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

#include <windows.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "GuiManager.h"
#include "GameManager.h"
#include "Utils.h"
#include "Structure.h"

static int panelHandle;

static int IMG_Empty, IMG_Red, IMG_Green, IMG_Blue, IMG_Purple, IMG_Yellow, IMG_Aqua, IMG_Orange;


/**
	Fonction pour initialiser l'interface
**/
void Gui_init(void) {
	
	if ((panelHandle = LoadPanel (0, "Interface.uir", PANEL)) < 0)
		return;
	Gui_remove_Border(panelHandle, PANEL_BACKGROUND);
	
	/**
		On sauvegarde les blocs dans des variables
	**/
	GetBitmapFromFile("images/Empty.bmp", &IMG_Empty);
	GetBitmapFromFile("images/Red.bmp", &IMG_Red);
	GetBitmapFromFile("images/Green.bmp", &IMG_Green);
	GetBitmapFromFile("images/Blue.bmp", &IMG_Blue);
	GetBitmapFromFile("images/Purple.bmp", &IMG_Purple);
	GetBitmapFromFile("images/Yellow.bmp", &IMG_Yellow);
	GetBitmapFromFile("images/Aqua.bmp", &IMG_Aqua);
	GetBitmapFromFile("images/Orange.bmp", &IMG_Orange);
	
	/**
		On rend transparent le bloc Empty²
	**/
	MakeColorTransparent(IMG_Empty, VAL_RED);
	
	/**
		On rend le background de la table transparent  
	**/
	SetTableCellRangeAttribute (panelHandle, PANEL_TABLE, MakeRect (1, 1, 22, 10), ATTR_TEXT_BGCOLOR, VAL_TRANSPARENT);
	SetCtrlAttribute(panelHandle, PANEL_TABLE, ATTR_TABLE_BGCOLOR, VAL_TRANSPARENT);  
	
	SetTableCellRangeAttribute (panelHandle, PANEL_TABLE_NEXT, MakeRect (1, 1, 4, 4), ATTR_TEXT_BGCOLOR, VAL_TRANSPARENT);
	SetCtrlAttribute(panelHandle, PANEL_TABLE_NEXT, ATTR_TABLE_BGCOLOR, VAL_TRANSPARENT);  
	
	/**
		On affiche la grille vide du jeux
	**/
	InsertTableRows (panelHandle, PANEL_TABLE, -1, 22, VAL_CELL_PICTURE);
	InsertTableColumns (panelHandle, PANEL_TABLE, -1, 10, VAL_CELL_PICTURE);
	
	for (int width = 1; width <= 10; width++)
	{
		for (int height = 1; height <= 22; height++)
		{
			SetTableCellAttribute(panelHandle, PANEL_TABLE, MakePoint(width,height), ATTR_CTRL_VAL, IMG_Empty);
		}
	}
	
	for (int width = 1; width <= 4; width++)
	{
		for (int height = 1; height <= 4; height++)
		{
			SetTableCellAttribute(panelHandle, PANEL_TABLE_NEXT, MakePoint(width,height), ATTR_CTRL_VAL, IMG_Empty);
		}
	}

}

/**
	Fonction pour afficher l'interface
**/
void Gui_display(void) {
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
}

/**
	Pour supprimer la bordure de la fenetre
**/
void Gui_remove_Border(int panel, int image) {
	
	HWND hwnd;
	GetPanelAttribute(panel, ATTR_SYSTEM_WINDOW_HANDLE, (int*)&hwnd);
	
	int hasTitleBar;
	GetPanelAttribute(panel, ATTR_TITLEBAR_VISIBLE, &hasTitleBar);
	
	int titleBarHeight = (hasTitleBar)?GetSystemMetrics(SM_CYCAPTION):0;
	
	RECT clientRect, windowRect;
	GetClientRect(hwnd, &clientRect);
	GetWindowRect(hwnd, &windowRect);
	
	int Top = ((windowRect.bottom - windowRect.top - titleBarHeight) - clientRect.bottom)/2 + titleBarHeight;
	int Left= (windowRect.right - windowRect.left - clientRect.right)/2;
	
	int PictureWidth, PictureHeight;
	GetCtrlAttribute(panel, image, ATTR_WIDTH, &PictureWidth);
	GetCtrlAttribute(panel, image, ATTR_HEIGHT, &PictureHeight);
	
	HRGN hOriginalRgn = CreateRectRgn(Left, Top, PictureWidth+Left, PictureHeight+Top);
	SetWindowRgn(hwnd, hOriginalRgn, TRUE);
	
	//InstallWinMsgCallback(panel, WM_MOUSEMOVE, OnMouseMove, VAL_MODE_INTERCEPT, NULL, &gPostHndl); 
	/** TODO
		mettre en place le callback pour bouger la fenetre
	**/
	if(hOriginalRgn) DeleteObject(hOriginalRgn);
	

}

/**
	Pour recuperer l'interface
**/
int Gui_get_Interface(void) {
		return panelHandle;
}


/**
	Pour obtenir l'image à partir de la couleur
**/
int Gui_get_IMG(int color) {
	
	int returnColor;
	
	switch(color) {
		case RED:
			returnColor = IMG_Red;
		break;
		case GREEN:
			returnColor = IMG_Green;
		break;
		case BLUE:
			returnColor = IMG_Blue;
		break;
		case PURPLE:
			returnColor = IMG_Purple;
		break;
		case YELLOW:
			returnColor = IMG_Yellow;
		break;
		case AQUA:
			returnColor = IMG_Aqua;
		break;
		case ORANGE:
			returnColor = IMG_Orange;
		break;
		default:
			returnColor = IMG_Empty;
		break;
	}
	return returnColor;
}


/**
	Pour rafraichir les cases
**/
void Gui_update_display(void) {
	
	for (int width = 1; width <= 10; width++)
	{
		for (int height = 1; height <= 22; height++)
		{
			SetTableCellAttribute(panelHandle, PANEL_TABLE, MakePoint(width,height), ATTR_CTRL_VAL, Gui_get_IMG(Game_get_MAP(height,width)));
		}
	}
}

/**
	Pour rafraichir les cases de la piece en mouvement
**/
void Gui_update_falling_piece(void) {
	
	PieceActuel Piece_Actuel = Game_get_piece();
	
	for(int x = 0; x<4; x++) {
		for(int y = 0; y<4; y++) {
			if(Pieces[Piece_Actuel.piece_type].orientation[Piece_Actuel.orientation][x][y] != 0) { //ce n'est pas du vide
				if(Piece_Actuel.x + x <12 && Piece_Actuel.x +x >0 && Piece_Actuel.y + y <24  && Piece_Actuel.y + y > 0) { //La piece est dans la terrain d'affichage
					SetTableCellAttribute(panelHandle, PANEL_TABLE, MakePoint(Piece_Actuel.x + x, Piece_Actuel.y + y), ATTR_CTRL_VAL, Gui_get_IMG(Pieces[Piece_Actuel.piece_type].couleur));
				}
			}
		}
	}
}

/**
	Pour afficher la piece suivante
**/
void Gui_update_next_piece(void)  {
	char piece = Game_get_next_piece();
	for(int x = 1; x<=4; x++) {
		for(int y= 1; y<=4; y++) {
			if(Pieces[piece].orientation[0][x-1][y-1])
				SetTableCellAttribute(panelHandle, PANEL_TABLE_NEXT, MakePoint(x, y), ATTR_CTRL_VAL, Gui_get_IMG(Pieces[piece].couleur));
			else
				SetTableCellAttribute(panelHandle, PANEL_TABLE_NEXT, MakePoint(x, y), ATTR_CTRL_VAL, IMG_Empty);
		}
	}
}

/**
	Pour activer le timer
**/
void Gui_Timer_enable(void) {
	SetCtrlAttribute (panelHandle, PANEL_GAME_TIMER, ATTR_ENABLED, 1);
}

/**
	Pour desactiver le timer
**/
void Gui_Timer_disable(void) {
	SetCtrlAttribute (panelHandle, PANEL_GAME_TIMER, ATTR_ENABLED, 0);
}

/**
	Pour savoir si le timer est activé
**/
int Gui_Timer_isEnable(void) {
	int isEnable;
	GetCtrlAttribute (panelHandle, PANEL_GAME_TIMER, ATTR_ENABLED, &isEnable);
	return isEnable;
}

/**
	Pour definir l'interval du timer
**/
void Gui_Timer_set_interval(double interval) {
	SetCtrlAttribute (panelHandle, PANEL_GAME_TIMER, ATTR_INTERVAL, interval);
}
