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

#include <utility.h>
#include <ansi_c.h>
#include "GameManager.h"
#include "SoundManager.h"
#include "GuiManager.h"
#include "Structure.h"

//La liste des pieces à venir
//0=> Piece actuel
//1=> Piece Suivante
static char				Game_Pieces[9] = {-1,-1,-1,-1,-1,-1,-1,-1};

static unsigned char	Game_MAP[24][12];

static unsigned char	Game_etat = WAITING;

static PieceActuel		Game_Piece_Actuel;

/**
	Pour initialiser la partie
**/
void Game_init(void) {
	//On prepare l'interface
	Gui_init();
	
	//On lance la musique
	//Start_Background_Musique(); 
	
	//On definit l'interval du timer
	Gui_Timer_set_interval(0.4);

}

/**
	Pour debuter une partie
**/
void Game_start(void) {
	if(Game_etat == INGAME) return;
	
	
	srand(clock());
	//On initialise la liste des pieces
	for(int i =0; i<9; i++) {
		Game_Pieces[i] = -1;
	}
	
	Game_Pieces[0] = rand()%7;
	Game_Pieces[1] = rand()%7;
	Game_generate_piece();
	
	for(int x =0; x<12; x++) {
		for(int y =0; y<24; y++) {
			Game_MAP[y][x] = 0;
		}
	}
	
	//On initialise la piece actuel
	Game_Piece_Actuel.piece_type = Game_Pieces[0];
	Game_Piece_Actuel.x = 4;
	Game_Piece_Actuel.y = 0;
	Game_Piece_Actuel.orientation = 0;
	
	//On lance le timer
	Gui_Timer_enable();
	
	Gui_update_display();
	Gui_update_falling_piece();
	Gui_update_next_piece();
	
	Game_etat = INGAME;
}

/**
	Pour arreter une partie
**/
void Game_stop(void) {
	if(Game_etat == WAITING) return;
	Game_etat = WAITING;
	Gui_Timer_disable();
}

/**
	Pour regarder si la partie est perdu
**/
void Game_set_lose(void) {
	Game_etat = LOSE;
	
	Gui_update_display();
	Gui_update_falling_piece();
	printf("Fin de la partie");
}

/**
	Pour obtenir l'etat de la partie
**/
int Game_get_etat(void) {
	return Game_etat;
}

/**
	Pour obtenir la disposition des blocs
**/
unsigned char Game_get_MAP(int x, int y) {
	return Game_MAP[x][y];
}

/**
	Pour obtenir le type de la piece suivante
**/
char Game_get_next_piece(void) {
	return Game_Pieces[1];
}

/**
	Pour obtenir la piece actuel
**/
PieceActuel Game_get_piece(void) {
	return Game_Piece_Actuel;
}

/**
	Pour passer à la piece suivante 
**/
void Game_change_piece(void) {

	int color = Pieces[Game_Piece_Actuel.piece_type].couleur;
	//On fige la piece actuel sur le terrain
	for(int x = 0; x<4; x++) {
		for(int y = 0; y<4; y++) {
			if(Pieces[Game_Piece_Actuel.piece_type].orientation[Game_Piece_Actuel.orientation][y][x] != 0) { //ce n'est pas du vide
				if(Game_Piece_Actuel.x + x <12 && Game_Piece_Actuel.x +x >0 && Game_Piece_Actuel.y + y <24  && Game_Piece_Actuel.y + y > 0) { //La piece est dans la terrain d'affichage
					Game_MAP[Game_Piece_Actuel.y + y][Game_Piece_Actuel.x + x] = color;
				}
			}
		}
	}
	//On actualise l'affichage static
	Gui_update_display();
	
	//On décale la liste des pieces
	for(int i = 0; i<8;i++) {
		Game_Pieces[i] = Game_Pieces[i+1];
	}
	Game_Pieces[8] = -1;
	//On regarde si il y a besoin de regenerer la liste des pieces à venir
	if(Game_Pieces[2] == -1) {
		Game_generate_piece();
	}
	Game_Piece_Actuel.piece_type = Game_Pieces[0];
	Game_Piece_Actuel.x = 4;
	Game_Piece_Actuel.y = 0;
	Game_Piece_Actuel.orientation = 0;
	
	//On ragarde si le joueur n'a pas perdu
	for(int x = 0; x<4; x++) {
		for(int y = 0; y<4; y++) {
			if(Pieces[Game_Piece_Actuel.piece_type].orientation[Game_Piece_Actuel.orientation][x][y] != 0) { //ce n'est pas du vide
				if(Game_Piece_Actuel.x + x <12 && Game_Piece_Actuel.x +x >0 && Game_Piece_Actuel.y + y <24  && Game_Piece_Actuel.y + y > 0) { //Le carre est dans le terrain d'affichage
					if(Game_MAP[Game_Piece_Actuel.y + y][Game_Piece_Actuel.x + x] != 0) {
						Game_set_lose();
						return;
					}
				}
			}
		}
	}
	
	//On regarde si la piece peux descendre d'un
	if(Game_check_collision()) {
		Game_set_lose();
		return;
	}
	
	//On affiche la piece
	Gui_update_falling_piece();
	Gui_update_next_piece();
}

/**
	Pour generer le groupe de piece suivant
**/
void Game_generate_piece(void) {
	if(Game_Pieces[2] != -1) return; //On evite les problemes si la liste n'est pas vide
	
	srand(clock()+95);
	char done = 0;
	while(done < 6) {
		int pieceType = rand()%7;
		char allow = 1;
		for(int i = 2; i<9;i++) {
			if(Game_Pieces[i] == pieceType)
				allow = 0;
		}	
		if(allow) {
			done++;
			Game_Pieces[done+1] = pieceType;
		}
		//printf("allow: %d, pieceType: %d, done: %d\n",allow, pieceType,done);
		//GetKey();
	}
}

/**
	Pour faire descendre une piece
**/
void Game_Piece_fall(void) {
	//1 -> on affiche la piece
	Game_Piece_Actuel.y += 1;
	Gui_update_display();
	Gui_update_falling_piece();
	//2 -> on regarde si il y a pas de colision
	if(Game_check_collision()) {
		Game_change_piece();
	}
}

/**
	Pour décaler une piece vers la droite
**/
void Game_Piece_move_right(void) {
	//On regarde si la piece ne va pas sortir du champ
	if(Game_Piece_Actuel.x >=11) return;
	for(int x = 3; x>=0; x--) {
		for(int y = 0; y<4; y++) {
			if(Pieces[Game_Piece_Actuel.piece_type].orientation[Game_Piece_Actuel.orientation][y][x] != 0) { //ce n'est pas du vide
				if(Game_Piece_Actuel.x + x >=10) return;
			}
		}
	}
	Game_Piece_Actuel.x += 1;
	Gui_update_display();
	Gui_update_falling_piece();
	if(Game_check_collision()) {
		Game_change_piece();
	}
}

/**
	Pour décaler une piece vers la gauche
**/
void Game_Piece_move_left(void) {
	//On regarde si la piece ne va pas sortir du champ
	if(Game_Piece_Actuel.x <= 0) return;
	for(int x = 0; x<4; x++) {
		for(int y = 0; y<4; y++) {
			if(Pieces[Game_Piece_Actuel.piece_type].orientation[Game_Piece_Actuel.orientation][y][x] != 0) { //ce n'est pas du vide
				if(Game_Piece_Actuel.x - x <0 ) return;
			}
		}
	}
	Game_Piece_Actuel.x -= 1;
	Gui_update_display();
	Gui_update_falling_piece();
	if(Game_check_collision()) {
		Game_change_piece();
	}
}

/**
	Pour faire tourner une piece
**/
void Game_Piece_rotation(void) {
	Game_Piece_Actuel.orientation += 1;
	if(Game_Piece_Actuel.orientation >3) Game_Piece_Actuel.orientation = 0;
	Gui_update_display();
	Gui_update_falling_piece();
	if(Game_check_collision()) {
		Game_change_piece();
	}
}

/**
	Pour verifier si la piece n'est pas au plus bas de sa capacité
**/
int Game_check_collision(void) {
	
	for(int x = 0; x<4; x++) {
		for(int y = 3; y>=0; y--) {
			if(Pieces[Game_Piece_Actuel.piece_type].orientation[Game_Piece_Actuel.orientation][y][x] != 0) { //ce n'est pas du vide
				if(Game_Piece_Actuel.x + x <12 && Game_Piece_Actuel.x +x >0 && Game_Piece_Actuel.y + y <24  && Game_Piece_Actuel.y + y > 0) { //La piece est dans la terrain d'affichage
					if(Game_Piece_Actuel.y + y +1 >22) { //La piece est en bas
						return 1;
					}
					if(Game_MAP[Game_Piece_Actuel.y + y+1][Game_Piece_Actuel.x + x] != 0) {
						return 1;
					}
					
				}
			}
		}
	}
	
	return 0;
}
