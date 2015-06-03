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
#include "Utils.h"

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
	
	SetTableCellAttribute(panelHandle, PANEL_TABLE, MakePoint(1,1), ATTR_CTRL_VAL, IMG_Blue);
	
	 
	
	
	
	
	
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
	if(hOriginalRgn) DeleteObject(hOriginalRgn);
	

}

/**
	Pour recuperer l'interface
**/
int Gui_get_Interface(void) {
		return panelHandle;
}

/**
	Pour rafraichir les cases
**/
void Gui_update_display(void) {
	
	
	
	for (int width = 1; width <= 10; width++)
	{
		for (int height = 1; height <= 22; height++)
		{
			SetTableCellAttribute(panelHandle, PANEL_TABLE, MakePoint(width,height), ATTR_CTRL_VAL, IMG_Aqua);
		}
	}
}
