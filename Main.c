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


#include <ansi_c.h>
#include <utility.h>
#include "soundManager.h"
#include "Structure.h"


/**
  Fonction principale du programme
**/
void main(void) {

	Start_Background_Musique();

	GetKey();
	
	Play_Move_Sound();
	
	GetKey(); 
}
