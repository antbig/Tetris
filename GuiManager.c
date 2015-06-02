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
#include <cvirte.h>		
#include <userint.h>
#include "GuiManager.h"

static int panelHandle;

/**
	Fonction pour initialiser l'interface
**/
void Gui_init(void) {
	
	if ((panelHandle = LoadPanel (0, "Interface.uir", PANEL)) < 0)
		return;
	Gui_remove_Border(panelHandle, PANEL_BACKGROUND);
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