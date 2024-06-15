#include "vaisseau.h"

Vaisseau::Vaisseau(lv_obj_t *windows)
{
    canvas = lv_canvas_create(windows/*lv_scr_act()*/); // Création du canvas du vaisseau

    // Initialisation de la position X et Y
    posX = SCREEN_WIDTH / 2 - CANVAS_VAISSEAU_WIDTH / 2;
    posY = SCREEN_HEIGHT - CANVAS_VAISSEAU_HEIGHT;

    // Initialisation du canvas
    lv_canvas_set_buffer(canvas, cbuf, CANVAS_VAISSEAU_WIDTH, CANVAS_VAISSEAU_HEIGHT, LV_IMG_CF_INDEXED_1BIT);
    lv_canvas_set_palette(canvas, 1, lv_color_make(127, 0, 255));
    lv_canvas_set_palette(canvas, 0, lv_color_make(0, 0, 0));
    lv_obj_set_pos(canvas, posX, posY);

    active = true;
    draw();
}

// Cette méthode permet de définir la position du vaisseau
void Vaisseau::setPos(short *pos)
{
    posX += pos[0];
    posY += pos[1];
    if (posX >= 430) {
        posX = 430;
    }
    if (posX <= -16) {
        posX = -16;
    }
    if (posY >= 225) {
        posY = 225;
    }
    if (posY <= 205) {
        posY = 205;
    }

    lv_obj_set_pos(canvas, posX, posY);
}

// Cette méthode permet de retourner par passage par reference la position du vaisseau (Utilisé pour placer les projectiles)
void Vaisseau::getPos(short *pos)
{
    pos[0] = posX;
    pos[1] = posY;
}

// Cette méthode permet de dessiner le vaisseau dans le canvas
void Vaisseau::draw(void)
{
    lv_color_t c0;
    lv_color_t c1;

    c0.full = 0; // Transparent
    c1.full = 1; // White

    lv_canvas_fill_bg(canvas, c0, LV_OPA_0);

    /* Draw the spaceship (an enlarged representation) */
    // Body
    for (uint8_t y = 6; y < 24; y++) {
        for (uint8_t x = 10; x < 20; x++) {
            lv_canvas_set_px_color(canvas, x, y, c1);
        }
    }

    // Left wing
    for (uint8_t y = 15; y < 24; y++) {
        for (uint8_t x = 4; x < 10; x++) {
            lv_canvas_set_px_color(canvas, x, y, c1);
        }
    }

    // Right wing
    for (uint8_t y = 15; y < 24; y++) {
        for (uint8_t x = 20; x < 26; x++) {
            lv_canvas_set_px_color(canvas, x, y, c1);
        }
    }

    // Cockpit
    for (uint8_t y = 2; y < 6; y++) {
        for (uint8_t x = 12; x < 18; x++) {
            lv_canvas_set_px_color(canvas, x, y, c1);
        }
    }

    // Left Reactor
    for (uint8_t y = 24; y < 26; y++) {
        for (uint8_t x = 6; x < 8; x++) {
            lv_canvas_set_px_color(canvas, x, y, c1);
        }
    }

    // Right Reactor
    for (uint8_t y = 24; y < 26; y++) {
        for (uint8_t x = 22; x < 24; x++) {
            lv_canvas_set_px_color(canvas, x, y, c1);
        }
    }
}

// Cette méthode permet de désactiver le vaisseau
void Vaisseau::deactivate(void)
{
    lv_obj_add_flag(canvas, LV_OBJ_FLAG_HIDDEN);
    active = false;
}

// Cette méthode permet de remettre à 0 les attributs du vaisseau
void Vaisseau::reset()
{
    lv_obj_clear_flag(canvas, LV_OBJ_FLAG_HIDDEN);
    active = true;
}