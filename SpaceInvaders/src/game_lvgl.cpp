#include "game_lvgl.h"


lv_obj_t* pin_labels[NUM_PINS];


// Fonction principale
void launch_game(lv_obj_t * window)
{  

    static lv_style_t style_window;
    lv_style_init(&style_window);
    lv_style_set_bg_color(&style_window, lv_color_hex(0x000000)); // C'est sensé être noir
    lv_style_set_bg_opa(&style_window, LV_OPA_100);
    lv_style_set_border_width(&style_window, 2);
    lv_style_set_border_color(&style_window, lv_color_black());
    lv_style_set_radius(&style_window, 0);

    lv_obj_set_size(window, 480, 272);
    lv_obj_set_pos(window, 0, 0);

    lv_obj_add_style(window, &style_window, 0);

    // Désactiver le scroller horizontal
    lv_obj_clear_flag(window, LV_OBJ_FLAG_SCROLLABLE);
    // Désactiver le scroller vertical
    lv_obj_set_scrollbar_mode(window, LV_SCROLLBAR_MODE_OFF);
    
}

void lecture_entrees(short *dx, short *dy, bool *isAttack, bool *isUltime)
{
    DigitalIn joyUp(D7);
    DigitalIn joyDown(D6);
    DigitalIn joyLeft(D5);
    DigitalIn joyRight(D4);

    DigitalIn bpStart(D2);
    DigitalIn bpUltime(D3);


    if (!joyUp) {
        *dy = -2;
    }
    else if (!joyDown) {
        *dy = 2;
    }
    else {
        *dy = 0;
    }

    if (!joyLeft) {
        *dx = -2;
    }
    else if (!joyRight) {
        *dx = 2;
    }
    else {
        *dx = 0;
    }
    if (!bpStart) {
        *isAttack = true;
    }
    else {
        *isAttack = false;
    }
    if (!bpUltime) {
        *isUltime = true;
    }
    else {
        *isUltime = false;
    }
}
