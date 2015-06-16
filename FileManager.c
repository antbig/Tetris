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
#include "Structure.h"

/**
	Pour sauvegarder la partie dans un fichier
**/
void File_save_game(void) {
	
	FILE *save;
	
	save = fopen("save.dat","w");
	//On sauvegarde le terrain
	for(int y=0; y<24; y++) {
		for(int x = 0; x<12; x++) {
			fprintf(save,"%d",Game_get_MAP(x,y));
		}
		fprintf(save,"\n");
	}
	//on sauvegarde le score
	fprintf(save, "%d\n", Game_get_score());
	/*
	for(int x = 0; x<9; x++) {
		int val = (Game_get_next_piece(x) != -1)?Game_get_next_piece(x):9;
		fprintf(save,"%d",val);
	}*/
	fprintf(save,"\n");
	
	
	fclose(save);
}

/**
	Pour restorer la partie
**/
void File_restor_game(void) {
	
	if(!File_exist("save.dat")) return;
	
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

/**
	Pour obtenir le profil d'un joueur
	Param�tres :
		char *username[]	=> Nom du joueur dont on veut retrouver le profil
		User_profil			=> Pointeur vers le profil cible vers lequel on transf�re les donn�es dans le fichier de sauvegarde
**/
void File_get_user(char *username[50], User_profil *newProfil) {
	char fileProfil[200] = "userData/";
	
	
		
	strcat(fileProfil, username);
	strcat(fileProfil, ".dat");  
	
	strcpy(newProfil->username, username);
	
	if(!File_exist(fileProfil)) {
		newProfil->hightScore	= 0;
		newProfil->backup_score	= 0;
		newProfil->backup_level	= 1;
		newProfil->musique		= 1;
		return;
	} 
	
	FILE *save;
	char linebuffer[30];
	int counter = 0;
	save = fopen(fileProfil,"rd");
	
	while (fgets(linebuffer, 30, save)!=0){
		
		if(counter == 1) {
			newProfil->musique		= Char_to_Int(linebuffer[0]);
		}
		
		if(counter == 2) {
			newProfil->backup_level		= Char_to_Int(linebuffer[0]);
		}
		if(counter >=3 && counter < 27) {
			for(int d = 0; d<12; d++) {
				if(linebuffer[d] != 32) {
					newProfil->backup_MAP[counter-3][d] = Char_to_Int(linebuffer[d]);
				}
			}
		}
		if(counter == 27) {
			newProfil->backup_score		= (long)strtol(linebuffer, NULL, 10);
		}
		
		counter++;
	}
	
	
	fclose(save);

}

/**
	Pour sauvegarder le profil d'un utilisateur
	Param�tre :
		User_profil *Profil	=> Profil de joueur � sauvegarder
**/
void File_save_user(User_profil *Profil) {
	char fileProfil[200] = "userData/";
	
	strcat(fileProfil, Profil->username);
	strcat(fileProfil, ".dat"); 
	
	FILE *save;
	save = fopen(fileProfil,"w");
	
	fprintf(save,"%s\n",Profil->username);
	
	fprintf(save,"%d\n",Profil->musique);
	
	fprintf(save,"%d\n",Profil->backup_level);
	
	if(Profil->backup_level == 0) { 
		for(int y=0; y<24; y++) {
			for(int x = 0; x<12; x++) {
				fprintf(save,"%d",0);
			}
			fprintf(save,"\n");
		}
		fprintf(save,"%d\n",0);
	} else {
		for(int y=0; y<24; y++) {
			for(int x = 0; x<12; x++) {
				fprintf(save,"%d",Game_get_MAP(x,y));
			}
			fprintf(save,"\n");
		}
		fprintf(save,"%d\n",Game_get_score());
	}
	
	
	
	fclose(save);
}

/**
	Pour r�cup�rer le fichier de high-score
	Param�tre :
		Score *scores		=> Pointeur vers un tableau de Score qui prendra les valeurs des highscores
**/
Get_highscore(Score *scores)
{
	FILE *save;
	char linebuffer[50];
	int counter = 0;
	save = fopen("highscore.dat","rd");
	
	while(fgets(linebuffer, 20, save) && counter < 20)
	{
		if((counter%2) == 0)
		{
			strcpy(scores[counter/2].username, linebuffer);
		}
		else if(counter%2)
		{
			scores[counter/2].score				= (long)strtol(linebuffer, NULL, 10);	
		}
		counter ++;
	}
	
	
	
	fclose(save);
	return scores;
}

/**
	Pour r��crire le fichier de high-score
	Param�tre :
		Score* scores		=> Pointeur vers le tableau de Score � sauvegarder
**/
void Update_highscore(Score* scores)
{
	FILE *save;
	save = fopen("highscore.dat", "w");
	
	for(int i = 0; i < 10; i++)
	{
		fprintf(save, "%s%d\n", scores[i].username, scores[i].score);	
	}
	
	fclose(save);
	
}














	

