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

#include <ansi_c.h>
#include "FileManager.h"
#include "GameManager.h"
#include "Utils.h"

/**
	Pour sauvegarder la partie dans un fichier
**/
void File_save_game(void) {
	
	FILE *save;
	
	save = fopen("save.dat","w");
	
	for(int y=0; y<24; y++) {
		for(int x = 0; x<12; x++) {
			fprintf(save,"%d",Game_get_MAP(x,y));
		}
		fprintf(save,"\n");
	}
	fprintf(save, "%d\n", Game_get_score());
	
	for(int x = 0; x<9; x++) {
		int val = (Game_get_next_piece(x) != -1)?Game_get_next_piece(x):9;
		fprintf(save,"%d",val);
	}
	fprintf(save,"\n");
	
	
	fclose(save);
}

/**
	Pour restorer la partie
**/
void File_restor_game(void) {
	FILE *save;
	char linebuffer[30];
	int counter = 0;
	save = fopen("save.dat","r");
	//printf("\n");
	while (fgets(linebuffer, 30, save)!=0){
		if(counter <24) {
			for(int d = 0; d<12; d++) {
				
				//printf
				if(linebuffer[d] != 32) {
					//printf("x:%d y:%d v:%d \n",d/2, counter, linebuffer[d]);
					Game_set_MAP(d, counter, Char_to_Int(linebuffer[d]));
				}
				//
			}
		}
		if(counter == 24) Game_set_score((long)strtol(linebuffer, NULL, 10));
		/*
		if(counter == 25) {
			for(int a= 0; a<9; a++) {
				int val = Char_to_Int(linebuffer[a]);
				if(val == 9 && a >=3)
					Game_set_next_piece(a,(val !=9)?val:-1);
			}
				
		}*/
		
		//printf("\n");
		counter++;
	}
	
	fclose(save);
}
