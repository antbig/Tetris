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

#include <windows.h>
#include <mmsystem.h>

#include "SoundManager.h"

static short MusiqueEnable = 0;

/**
  Fonction pour lancer la musique en arriere plan
**/
short Start_Background_Musique(void) {
	waveOutSetVolume(0,0xFF00FF00);
	UINT flags = 0;
	
	flags |= SND_ASYNC | SND_LOOP;  //Lecture en boucle
	flags |= SND_NOSTOP; //On ne stoppe pas la musique en cours
	MusiqueEnable = 1;
	return sndPlaySound("musique/background.wav", flags);  
	
}

/**
	Pour arreter la musique
**/
void Stop_musique(void) {
	sndPlaySound(NULL, 0);
	MusiqueEnable = 0;
}

/**
	Fonction pour joueur le son lors du deplacement d'une piece
**/
short Play_Move_Sound(void) {
	UINT flags = 0;
	
	flags |= SND_ASYNC;  //Lecture en boucle
	flags |= SND_NOSTOP; //On ne stoppe pas la musique en cours
	
	return sndPlaySound("musique/moveEvent.wav", flags);  
}

/**
	Pour activer/desactiver la musique
**/
void Toggle_musique(void) {
	if(MusiqueEnable) {
		Stop_musique();
	} else {
		Start_Background_Musique();
	}
}

/**********

waveOutSetVolume(0,0xFFFFFFFF); Pour changer le volume
	=> XXXX     XXXX
	   Droite   Gauche
************/


