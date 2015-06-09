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
	Fichier avec les fonctions pour gerer les sauvegardes
**/

#include "FileManager.h"

/**
	Pour sauvegarder la partie dans un fichier
**/
void File_save_game(void) {
	
	unsigned char	Game_MAP[24][12];
	for(int x = 0; x<12; x++) {
		for(int y=0; y<24; y++) {
			Game_MAP[y][x] = Game_get_MAP(y,x);
		}
	}
	
	ArrayToFile("save.dat", Game_MAP, VAL_UNSIGNED_CHAR
}
