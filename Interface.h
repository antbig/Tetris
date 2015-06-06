/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2015. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_BACKGROUND                 2       /* control type: picture, callback function: (none) */
#define  PANEL_TABLE_NEXT                 3       /* control type: table, callback function: (none) */
#define  PANEL_TABLE                      4       /* control type: table, callback function: (none) */
#define  PANEL_JOUER                      5       /* control type: command, callback function: CALLBACK_JOUER */
#define  PANEL_CLOSE                      6       /* control type: picture, callback function: CALLBACK_CLOSE */
#define  PANEL_GAME_TIMER                 7       /* control type: timer, callback function: TimerCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CALLBACK_CLOSE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CALLBACK_JOUER(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
