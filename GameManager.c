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

#include <userint.h>
#include <utility.h>
#include <ansi_c.h>
#include "GameManager.h"
#include "SoundManager.h"
#include "GuiManager.h"
#include "Structure.h"
#include "FileManager.h"

//La liste des pieces a venir
//0=> Piece actuelle
//1=> Piece Suivante
static char				Game_Pieces[9] = {-1,-1,-1,-1,-1,-1,-1,-1};

static unsigned char	Game_MAP[24][12];

static unsigned char	Game_etat = WAITING;

static Piece_S			Game_Piece_Actuel;

static Piece_S			Game_piece_ghost;

static char				needProcessingTimer = 0;

static long				score = 0;

static User_profil		user;

static int				level = 1;

static long				lignes_eclatees = 0;

static Score			highscores[10];



/**
	Pour initialiser la partie
**/
void Game_init(void) {
	int 	valid = 0;
	Get_highscore(highscores);
	char	username[50];

	while(!valid) {
		if(PromptPopup ("Identification", "Entrez votre pseudo", username, 40) != 0) {
			exit(0);
		}
		if(username[0] == 0) {
			MessagePopup ("Erreur", "Merci de rentrer un pseudo valide");
		} else valid = 1;
	}
	
	File_get_user(username, &user);
	
	//On prepare l'interface
	Gui_init();

	//On definit l'intervalle du timer
	Gui_Timer_set_interval(0.6);

}

/**
	Pour reprendre une partie sauvegarde
**/
void Game_start_backup(void) {
	if(Game_etat == INGAME) return;
	score = user.backup_score;
	if(user.backup_level == 0) {
		level = 1;
		score = 0;
	} else {
		level = user.backup_level;
		Game_set_score(user.backup_score);
	}
	
	//On initialise la liste des pieces
	srand(clock());
	for(int i =0; i<9; i++) {
		Game_Pieces[i] = -1;
	}
	
	Game_Pieces[0] = rand()%7;
	Game_Pieces[1] = rand()%7;
	Game_generate_piece();

	memcpy ( Game_MAP, user.backup_MAP, sizeof(Game_MAP)+1 ) ; 
	
	Game_start();
}

/**
	Pour debuter une nouvelle partie
**/
void Game_start_new(void) {
	
	//if(Game_etat == INGAME) return;
	
	Gui_Timer_disable();
	
	score = 0;
	
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
	
	Game_start();
}

/**
	Pour lancer la partie
**/
void Game_start(void) {
	
	//On initialise la piece actuelle
	Game_Piece_Actuel.piece_type = Game_Pieces[0];
	Game_Piece_Actuel.x = 4;
	Game_Piece_Actuel.y = 0;
	Game_Piece_Actuel.orientation = 0;
	
	
	//On initialise la piece fantome
	Game_piece_ghost = Game_Piece_Actuel;
	
	//On lance la musique
	if(user.musique)
		Start_Background_Musique(); 
	
	
	Gui_set_boutton_ingame();
	//On lance le timer
	Gui_Timer_enable();
	
	Gui_display_level();
	
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
	Pour mettre en pause une partie
**/
void Game_pause(void) {
	Gui_Timer_disable();
	Game_etat = PAUSE;
	Gui_set_boutton_pause();
	
	//user.hightScore		= 0;
	user.backup_score	= score;
	user.backup_level	= level;
	user.musique		= Sound_isEnable();
	
	File_save_user(&user);
	
}

/**
	Pour quitter la pause
**/
void Game_quit_pause(void) {
	Game_etat = INGAME;
	Gui_Timer_enable();
	Gui_set_boutton_ingame();
}

/**
	Pour indiquer que la partie est perdue
**/
void Game_set_lose(void) {
	Game_etat = WAITING;
	
	Gui_Timer_disable();
	
	Gui_update_display();
	
	Gui_update_falling_piece();
	
	//On remplit l'Ã©cran de toutes les couleurs
	for(int x =0; x<12; x++) {
		for(int y =0; y<24; y++) {
			Game_MAP[y][x] = (rand() % 7 + 1);
		}
		
	}
	
	user.backup_level = 0; //pour indiquer que la sauvegarde ne doit pas etre effectué sur cette partie
	Gui_set_boutton_lose();
	Gui_update_display();
	File_save_user(&user);
	MessagePopup ("Dommage", "Vous avez perdu");
	
	for(int i = 9; i >= 0; i--)
	{
		if(score >= highscores[i].score)
		{
			if(i == 9)
			{
				strcpy(highscores[i].username, user.username); 
				strcat(highscores[i].username, "\n");
				highscores[i].score = score;
			}
			else
			{
				highscores[i+1] = highscores[i];
				strcpy(highscores[i].username, user.username); 
				strcat(highscores[i].username, "\n");
				highscores[i].score = score;
			}
		}
	}
	Popup_highscores();
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
	return Game_MAP[y][x];
}

/**
	pour definir la piece
**/
void Game_set_MAP(int x, int y, unsigned char val) {
	Game_MAP[y][x] = val;
}

/**
	Pour obtenir le type de la piece id
**/
char Game_get_next_piece(int id) {
	return Game_Pieces[id];
}

/**
	Pour definir le type de la piece id
**/
void Game_set_next_piece(int id, char val) {
	Game_Pieces[id] = val;
}

/**
	Pour obtenir la piece actuelle
**/
Piece_S Game_get_piece(void) {
	return Game_Piece_Actuel;
}

/**
	Pour avoir le score
**/
long Game_get_score(void) {
	return score;
}

/**
	Pour definir le score
**/
void Game_set_score(long s) {
	score = s;
	Gui_set_score(score);
}

/**
	Pour passer a la piece suivante 
**/
void Game_change_piece(void) {

	int color = Pieces[Game_Piece_Actuel.piece_type].couleur;
	//On fige la piece actuelle sur le terrain
	for(int x = 0; x<4; x++) {
		for(int y = 0; y<4; y++) {
			if(Pieces[Game_Piece_Actuel.piece_type].orientation[Game_Piece_Actuel.orientation][y][x] != 0) { //ce n'est pas du vide
				if(Game_Piece_Actuel.x + x <11 && Game_Piece_Actuel.x +x >0 && Game_Piece_Actuel.y + y <24  && Game_Piece_Actuel.y + y > 0) { //La piece est dans la terrain d'affichage
					Game_MAP[Game_Piece_Actuel.y + y][Game_Piece_Actuel.x + x] = color;
				}
			}
		}
	}
	
	//On actualise l'affichage statique
	Gui_update_display();
	
	//On ragarde s'il y a des lignes
	Game_check_complete_line();
	
	//On decale la liste des pieces
	for(int i = 0; i<8;i++) {
		Game_Pieces[i] = Game_Pieces[i+1];
	}
	Game_Pieces[8] = -1;
	//On regarde s'il y a besoin de regenerer la liste des pieces aÂ  venir
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
	
	//On regarde si la piece peut descendre d'un
	if(Game_check_collision()) {
		Game_set_lose();
		return;
	}
	
	//On affiche la piece
	Gui_update_falling_piece();
	Gui_update_next_piece();
}

/**
	Pour generer le groupe de pieces suivant
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
	
	Game_update_ghost_piece();
	
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
	Pour decaler une piece vers la droite
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
	
	Game_update_ghost_piece();
	
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
	Pour decaler une piece vers la gauche
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
	
	Game_update_ghost_piece();
	
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
	
	Piece_S testPosition = Game_Piece_Actuel;
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
	
	Game_update_ghost_piece();
	
	Gui_update_falling_piece();
	if(Game_check_collision()) {
		Game_change_piece();
	}
}

/**
	Pour verifier que la piece est dans une position correcte
**/
int Game_check_position(Piece_S piece) {
	
	for(int x = 0; x<4; x++) {
		for(int y = 0; y<4; y++) {
			if(Pieces[piece.piece_type].orientation[piece.orientation][y][x] != 0) { //ce n'est pas du vide
				if(piece.x + x <11 && piece.x + x >0 && piece.y + y <23  && piece.y + y > 0) { //Le carre est dans le terrain d'affichage
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
	Pour verifier si la piece n'est pas au plus bas de sa capacite
**/
int Game_check_collision(void) {
	
	for(int x = 0; x<4; x++) {
		for(int y = 3; y>=0; y--) {
			if(Pieces[Game_Piece_Actuel.piece_type].orientation[Game_Piece_Actuel.orientation][y][x] != 0) { //ce n'est pas du vide
				if(Game_Piece_Actuel.x + x <11 && Game_Piece_Actuel.x +x >0 && Game_Piece_Actuel.y + y <23  && Game_Piece_Actuel.y + y > 0) { //La piece est dans le terrain d'affichage
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
	Pour detecter les lignes completes
**/
void Game_check_complete_line(void) {
		
	int count = 0;
	int line = 0;
	
	int y = 3;
	
	while(y>=0) {
		count = 0;
		if(Game_Piece_Actuel.y + y < 23 && Game_Piece_Actuel.y + y > 0) {
			for(int x = 1; x<11; x++) {
				if(Game_MAP[Game_Piece_Actuel.y + y][x] != 0) count++;
			}
			if(count == 10) {//La ligne est complete
				Game_remove_line(Game_Piece_Actuel.y + y);
				line++;
			} else y--;
		} else y--;
	}
	if(line !=0) {
		score += 10*(line*line);
		Gui_set_score(score);
		Update_leveling(line);

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

/**
	Pour actualiser la piece fantome
**/
void Game_update_ghost_piece(void) {
	Gui_clear_old_piece(Game_piece_ghost);
	Game_piece_ghost = Game_Piece_Actuel;
	while(Game_check_position(Game_piece_ghost)) {
		Game_piece_ghost.y +=1;
	}
	Game_piece_ghost.y -=1;
	
	Gui_display_gosth(Game_piece_ghost);
}

/**
	Pour mettre à jour le niveau
**/

void Update_leveling(int lignes)
{
	if(level <= 9)
	{
		lignes_eclatees += lignes;
		if(lignes_eclatees >= (10 + (5*(level-1))))
		{
			level++;
			lignes_eclatees -= (10 + (5*(level-1)));
			Gui_Timer_set_interval(0.6 - ((double)(level)/(double)(10))*0.5);
		}
	}
	Gui_display_level();
}

/**
	Pour renvoyer le niveau atteint par le joueur
**/
int Get_level()
{
	return level;
}

/**
	Pour renvoyer les lignes restantes avant le prochain niveau
**/
int Get_lignes_restantes(void)
{
	return ((10 + (5*(level-1))) - lignes_eclatees)	;
}

/**
	Pour afficher la Pop-up des high scores
**/
void Popup_highscores(void)
{
	Update_highscore(highscores);
	char str[1000];
	sprintf(str,"1. \t%s\t%d\n2. \t%s\t%d\n3. \t%s\t%d\n4. \t%s\t%d\n5. \t%s\t%d\n6. \t%s\t%d\n7. \t%s\t%d\n8. \t%s\t%d\n9. \t%s\t%d\n10.\t%s\t%d",
					highscores[0].username,
					highscores[0].score,
					highscores[1].username,
					highscores[1].score,
					highscores[2].username,
					highscores[2].score,
					highscores[3].username,
					highscores[3].score,
					highscores[4].username,
					highscores[4].score,
					highscores[5].username,
					highscores[5].score,
					highscores[6].username,
					highscores[6].score,
					highscores[7].username,
					highscores[7].score,
					highscores[8].username,
					highscores[8].score,
					highscores[9].username,
					highscores[9].score); 
	MessagePopup ("Highscores", str);

	
}
