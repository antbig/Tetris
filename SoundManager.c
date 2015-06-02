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

#include <windows.h>
#include <mmsystem.h>

#include "SoundManager.h"

/**
  Fonction pour lancer la musique en arriere plan
**/
short Start_Background_Musique(void) {
	waveOutSetVolume(0,0xFF00FF00);
	UINT flags = 0;
	
	flags |= SND_ASYNC | SND_LOOP;  //Lecture en boucle
	flags |= SND_NOSTOP; //On ne stop pas la musique en cours
	
	return sndPlaySound("musique/background.wav", flags);  
	
}

/**
	Fonction pour joueur le son lors du déplacement d'une piece
**/
short Play_Move_Sound(void) {
	UINT flags = 0;
	
	flags |= SND_ASYNC;  //Lecture en boucle
	flags |= SND_NOSTOP; //On ne stop pas la musique en cours
	
	return sndPlaySound("musique/moveEvent.wav", flags);  
}

/**********

waveOutSetVolume(0,0xFFFFFFFF); Pour changer le volume
	=> XXXX     XXXX
	   Droite   Gauche
************/


