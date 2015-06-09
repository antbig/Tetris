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

#ifndef TETRIS_UTILS
#define TETRIS_UTILS

/**
	http://forums.ni.com/t5/LabWindows-CVI/Displaying-transparent-images/td-p/162428
	
	Fonction pour rendre une couleur transparente
**/
void MaskBitsOfColor (unsigned char *bits, int rowBytes, int color, int width, int height, unsigned char *mask);
void MakeColorTransparent(int bitmap, int color);

/**
	Pour convertir un char en int
**/
int Char_to_Int(char d);

/**
	Pour savoir si un fichier existe
**/
int File_exist(char *filename);

#endif
