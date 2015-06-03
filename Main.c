/******************************************************
**													 **
**  PROJET TETRIS 2015								 **
**													 **
**   Par Leonard Antoine <antoine.leonard@u-psud.fr> **
**    et David   Pierre  <pierre.david1@u-psud.fr>   **
**													 **
**	 tous droits r�serv�s							 **
** 													 **
*******************************************************/


#include <ansi_c.h>
#include <utility.h>
#include "soundManager.h"
#include "Structure.h"
#include "GuiManager.h" 
#include "GameManager.h" 


/**
  Fonction principale du programme
**/
void main(void) {
	
	Game_init();//On initialise le jeux
	
	Gui_display();

}
