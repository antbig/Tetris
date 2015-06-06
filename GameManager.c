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

static char				needProcessingTimer = 0;

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
	for(int x =2; x<11; x++) {
		for(int y =22; y>18; y--) {
			Game_MAP[y][x] = rand()%6 +1;
		}
	}
	
	//On initialise la piece actuel
	//Game_Piece_Actuel.piece_type = Game_Pieces[0];
	Game_Piece_Actuel.piece_type = 0;//pour le test
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
				if(Game_Piece_Actuel.x + x <11 && Game_Piece_Actuel.x +x >0 && Game_Piece_Actuel.y + y <24  && Game_Piece_Actuel.y + y > 0) { //La piece est dans la terrain d'affichage
					Game_MAP[Game_Piece_Actuel.y + y][Game_Piece_Actuel.x + x] = color;
				}
			}
		}
	}
	Game_check_complete_line();
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
	//unsigned int timeSpend = clock();
	if(Game_etat != INGAME) {
		needProcessingTimer = 1;
		return;
	}
	needProcessingTimer = 0;
	Game_etat = PROCESSING_T;
	//1 -> on affiche la piece
	Gui_clear_old_piece(Game_Piece_Actuel);
	Game_Piece_Actuel.y += 1;
	//Gui_update_display();
	Gui_update_falling_piece();
	//2 -> on regarde si il y a pas de colision
	if(Game_check_collision()) {
		Game_change_piece();
	}
	if(Game_etat == PROCESSING_T)
		Game_etat = INGAME;
	//printf("time=%d\n",clock()-timeSpend);
}

/**
	Pour décaler une piece vers la droite
**/
void Game_Piece_move_right(void) {
	Game_etat = PROCESSING;
	//On regarde si la piece ne va pas sortir du champ
	if(Game_Piece_Actuel.x >=11) {
		Game_etat = INGAME;
		return;
	}
	for(int x = 3; x>=0; x--) {
		for(int y = 0; y<4; y++) {
			if(Pieces[Game_Piece_Actuel.piece_type].orientation[Game_Piece_Actuel.orientation][y][x] != 0) { //ce n'est pas du vide
				if(Game_Piece_Actuel.x + x >=10) {
					Game_etat = INGAME;
					return;
				} else if(Game_MAP[Game_Piece_Actuel.y + y][Game_Piece_Actuel.x + x + 1] != 0) {
					Game_etat = INGAME;
					return;
				}
			}
		}
	}
	Gui_clear_old_piece(Game_Piece_Actuel);
	Game_Piece_Actuel.x += 1;
	//Gui_update_display();
	Gui_update_falling_piece();
	if(Game_check_collision()) {
		Game_change_piece();
	}
	if(Game_etat == PROCESSING)
		Game_etat = INGAME;
	if(needProcessingTimer)
		Game_Piece_fall();
}

/**
	Pour décaler une piece vers la gauche
**/
void Game_Piece_move_left(void) {
	Game_etat = PROCESSING;
	//On regarde si la piece ne va pas sortir du champ
	if(Game_Piece_Actuel.x <= 0)  {
		Game_etat = INGAME;
		return;
	}
	for(int x = 0; x<4; x++) {
		for(int y = 0; y<4; y++) {
			if(Pieces[Game_Piece_Actuel.piece_type].orientation[Game_Piece_Actuel.orientation][y][x] != 0) { //ce n'est pas du vide
				if(Game_Piece_Actuel.x-1 + x <1 )  {
					Game_etat = INGAME;
					return;
				} else if(Game_MAP[Game_Piece_Actuel.y + y][Game_Piece_Actuel.x + x - 1] != 0) {
					Game_etat = INGAME;
					return;
				}
			}
		}
	}
	Gui_clear_old_piece(Game_Piece_Actuel);
	Game_Piece_Actuel.x -= 1;
	//Gui_update_display();
	Gui_update_falling_piece();
	if(Game_check_collision()) {
		Game_change_piece();
	}
	if(Game_etat == PROCESSING)
		Game_etat = INGAME;
	if(needProcessingTimer)
		Game_Piece_fall();
}

/**
	Pour faire tourner une piece
**/
void Game_Piece_rotation(void) {
	
	int newOrientation = Game_Piece_Actuel.orientation + 1;
	if(newOrientation >3) newOrientation = 0;
	
	PieceActuel testPosition = Game_Piece_Actuel;
	testPosition.orientation = newOrientation;
	
	if(!Game_check_position(testPosition)) {

		if(Game_Piece_Actuel.x >=5) { //On tente une correction vers la gauche
			testPosition.x -=1;
			if(!Game_check_position(testPosition)) {
				testPosition.x +=2;
				if(!Game_check_position(testPosition)) {
					testPosition.y +=1;
					if(!Game_check_position(testPosition)) {
						testPosition.x -=2;
						if(!Game_check_position(testPosition)) {
							return;
						}
					}
				}
			}
		} else { //On tente une correction vers la droite
			testPosition.x +=1;
			if(!Game_check_position(testPosition)) {
				testPosition.x -=2;
				if(!Game_check_position(testPosition)) {
					testPosition.y +=1;
					if(!Game_check_position(testPosition)) {
						testPosition.x -=2;
						if(!Game_check_position(testPosition)) {
							return;
						}
					}
				}
			}
		}
	}
	
	Gui_clear_old_piece(Game_Piece_Actuel);
	Game_Piece_Actuel = testPosition;
	//Gui_update_display();
	Gui_update_falling_piece();
	if(Game_check_collision()) {
		Game_change_piece();
	}
}

/**
	Pour verifier que la piece est dans une position correcte
**/
int Game_check_position(PieceActuel piece) {
	
	for(int x = 0; x<4; x++) {
		for(int y = 0; y<4; y++) {
			if(Pieces[piece.piece_type].orientation[piece.orientation][y][x] != 0) { //ce n'est pas du vide
				if(piece.x + x <11 && piece.x + x >0 && piece.y + y <24  && piece.y + y > 0) { //Le carre est dans le terrain d'affichage
					if(Game_MAP[piece.y + y][piece.x + x] != 0) {
						return 0;
					}
				} else return 0;
			}
		}
	}
	return 1;
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

/**
	Pour detetcter les lignes completes
**/
void Game_check_complete_line(void) {
		
	int count = 0;
	
	int y = 3;
	
	while(y>=0) {
		count = 0;
		if(Game_Piece_Actuel.y + y < 23 && Game_Piece_Actuel.y + y > 0) {
			for(int x = 1; x<11; x++) {
				if(Game_MAP[Game_Piece_Actuel.y + y][x] != 0) count++;
			}
			if(count == 10) {//La line est complete
				Game_remove_line(Game_Piece_Actuel.y + y);
				/** TODO
					score
				**/
			} else y--;
		} else y--;
	}
}

/**
	Pour supprimer une ligne
**/
void Game_remove_line(int line) {
	for(int y = line; y>1; y--) {
		for(int x = 1; x<11; x++) {
			Game_MAP[y][x] = Game_MAP[y-1][x];
		}
	}
	for(int x = 1; x<11; x++) {
		Game_MAP[0][x] = 0;
	}
	Gui_update_display();
}
