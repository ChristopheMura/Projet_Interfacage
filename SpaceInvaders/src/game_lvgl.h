
#ifndef GAME_LVGL_H
#define GAME_LVGL_H


/*********************
 *      INCLUDES
 *********************/
#include "mbed.h"
#include "lvgl.h"
//#include "../examples/lv_examples.h"

const PinName PINS[] = {D2, D3, D4, D5, D6, D7};

const short NUM_PINS = sizeof(PINS) / sizeof(PinName);

/*********************
 *      DEFINES
 *********************/
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define CANVAS_VAISSEAU_WIDTH 30
#define CANVAS_VAISSEAU_HEIGHT 30

/**********************
 *      TYPEDEFS
 **********************/



/**********************
 * GLOBAL PROTOTYPES
 **********************/
void launch_game(lv_obj_t * window);

void lecture_entrees(short *dx, short *dy, bool *isAttack, bool *isUltime);

/**********************
 *      MACROS
 **********************/


#endif /*LV_DEMO_WIDGETS_H*/
