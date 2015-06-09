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
/**
	Fichier avec les fonctions utiles
**/
#include <userint.h>
#include <ansi_c.h>
#include "Utils.h"
/**
	http://forums.ni.com/t5/LabWindows-CVI/Displaying-transparent-images/td-p/162428
	
	Fonction pour rendre une couleur transparente
**/
void MaskBitsOfColor (unsigned char *bits, int rowBytes, int color, int width, int height, unsigned char *mask)
{
	int i, j, maskRowSize = ((width + 15) / 16 * 2);
	for (i = 0; i < height; ++i)
	for (j = 0; j < width; ++j)
	{
		if (*(int *)(bits + i * rowBytes + 4 * j) == color)
			mask[maskRowSize * i + j / 8] &= ~(1 << (7 - (j & 0x7)));
	}
}
void MakeColorTransparent(int bitmap, int color)
{
	 unsigned char *bits = NULL, *mask = NULL;
	 int width, height, rowBytes, pixelDepth = 32;
	 int maskSize, maskRowSize, hasMask;
	 
	 GetBitmapInfo(bitmap, NULL, NULL, &maskSize);
	 GetBitmapData(bitmap, NULL, NULL, &width, &height, NULL, NULL, NULL);
	 
	 rowBytes = 4 * width;
	 maskRowSize = ((width + 15) / 16 * 2);
	 hasMask = maskSize > 0;
	 maskSize = maskRowSize * height;
	 mask = malloc(maskRowSize * height);
	 
	 bits = malloc(rowBytes * height);
	 
	 if (hasMask)
	  GetBitmapData(bitmap, NULL, NULL, NULL, NULL, NULL, bits, mask);
	 else
	 {
	  memset(mask, 0xff, maskSize);
	  GetBitmapData(bitmap, NULL, NULL, NULL, NULL, NULL, bits, NULL);
	 }
	 
	 MaskBitsOfColor (bits, rowBytes, color, width, height, mask);
	 
	 SetBitmapData (bitmap, rowBytes, pixelDepth, NULL, NULL, mask);
	 free(mask);
	 free(bits);
}
