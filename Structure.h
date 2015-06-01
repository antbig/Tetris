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
	Ce fichier contient les différentes structures utilisées dans le programme
**/

/**
	Les couleur possible
**/
enum Color {Empty, Red, Green, Blue, Purple, Yellow, Aqua, Orange};

/*** Forme standare d'une piece
	{0 , 0, 0, 0},
	{0 , 0, 0, 0},
	{0 , 0, 0, 0},
	{0 , 0, 0, 0}
	
	0=> vide;
	1=> piece;
***/
typedef unsigned char COMPNENT[4][4];

/**
	Une piece 
	Composée de 
		- 4 COMPNENT pour chaque orientation
		- La couleur des block
**/
typedef struct
{
	COMPNENT	orientation[4];
	enum Color	couleur;
}Piece;