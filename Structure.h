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
#ifndef TETRIS_STRUCTURE
#define TETRIS_STRUCTURE
/**
	Les couleur possible
**/
#define EMPTY	0
#define RED		1
#define GREEN	2
#define BLUE	3
#define PURPLE	4
#define YELLOW	5
#define AQUA	6
#define ORANGE	7

/**
	L'etat de la partie
**/
#define WAITING 	0 //En attente du debut de la partie
#define INGAME		1 //En jeux
#define PAUSE		2 //En pause
#define LOSE		3 //Jeux perdu
#define PROCESSING	4 //traitement en cours, on bloque les mouvements

/*** Forme standare d'une piece
{	{0 , 0, 0, 0},
	{0 , 0, 0, 0},
	{0 , 0, 0, 0},
	{0 , 0, 0, 0}
}
	
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
	int			couleur;
}Piece;

/**
	La piece actuel
**/
typedef struct
{
	int piece_type;
	int x;
	int y;
	int orientation;
}PieceActuel;

/**
	Le liste de toutes les pieces du jeux
**/
static Piece Pieces[7] = {
	
	//Le I
	{
		{
			{	{0 , 1, 0, 0},
				{0 , 1, 0, 0},
				{0 , 1, 0, 0},
				{0 , 1, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 0, 0, 0},
				{1 , 1, 1, 1},
				{0 , 0, 0, 0}
			},
			{	{0 , 1, 0, 0},
				{0 , 1, 0, 0},
				{0 , 1, 0, 0},
				{0 , 1, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 0, 0, 0},
				{1 , 1, 1, 1},
				{0 , 0, 0, 0}
			}
		},
		AQUA
	},
	
	//Le O
	{
		{
			{	{0 , 0, 0, 0},
				{0 , 1, 1, 0},
				{0 , 1, 1, 0},
				{0 , 0, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 1, 1, 0},
				{0 , 1, 1, 0},
				{0 , 0, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 1, 1, 0},
				{0 , 1, 1, 0},
				{0 , 0, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 1, 1, 0},
				{0 , 1, 1, 0},
				{0 , 0, 0, 0}
			}
		},
		YELLOW
	},
	
	//Le T
	{
		{
			{	{0 , 0, 0, 0},
				{0 , 1, 0, 0},
				{1 , 1, 1, 0},
				{0 , 0, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 1, 0, 0},
				{1 , 1, 0, 0},
				{0 , 1, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 0, 0, 0},
				{1 , 1, 1, 0},
				{0 , 1, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 1, 0, 0},
				{0 , 1, 1, 0},
				{0 , 1, 0, 0}
			}
		},
		PURPLE
	},
	
	//Le S
	{
		{
			{	{0 , 0, 0, 0},
				{0 , 1, 1, 0},
				{1 , 1, 0, 0},
				{0 , 0, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{1 , 0, 0, 0},
				{1 , 1, 0, 0},
				{0 , 1, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 0, 0, 0},
				{0 , 1, 1, 0},
				{1 , 1, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 1, 0, 0},
				{0 , 1, 1, 0},
				{0 , 0, 1, 0}
			}
		},
		GREEN
	},
	
	//Le Z
	{
		{
			{	{0 , 0, 0, 0},
				{1 , 1, 0, 0},
				{0 , 1, 1, 0},
				{0 , 0, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 1, 0, 0},
				{1 , 1, 0, 0},
				{1 , 0, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 0, 0, 0},
				{1 , 1, 0, 0},
				{0 , 1, 1, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 0, 1, 0},
				{0 , 1, 1, 0},
				{0 , 1, 0, 0}
			}
		},
		RED
	},
	
	//Le J
	{
		{
			{	{0 , 0, 0, 0},
				{1 , 0, 0, 0},
				{1 , 1, 1, 0},
				{0 , 0, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 1, 0, 0},
				{0 , 1, 0, 0},
				{1 , 1, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 0, 0, 0},
				{1 , 1, 1, 0},
				{0 , 0, 1, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 1, 1, 0},
				{0 , 1, 0, 0},
				{0 , 1, 0, 0}
			}
		},
		BLUE
	},
	
	//Le L
	{
		{
			{	{0 , 0, 0, 0},
				{0 , 0, 1, 0},
				{1 , 1, 1, 0},
				{0 , 0, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{1 , 1, 0, 0},
				{0 , 1, 0, 0},
				{0 , 1, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 0, 0, 0},
				{1 , 1, 1, 0},
				{1 , 0, 0, 0}
			},
			{	{0 , 0, 0, 0},
				{0 , 1, 0, 0},
				{0 , 1, 0, 0},
				{0 , 1, 1, 0}
			}
		},
		ORANGE
	}
	
};

#endif
