#include "ennemi.h"

Ennemi::Ennemi(lv_obj_t *windows, short pPosX)
{
    canvas = lv_canvas_create(windows); // Création du canvas de l'ennemi

    // Initialisation des atributs de l'ennemi
    posX = pPosX;
    posY = 0;
    velocityX = 40;
    velocityY = 25;
    isDestroy = false;
    isOutofScreen = false;
    pointDeVie = 1;
    maxPointDeVie = 1;
    visible = true;

    // Initialisation du canvas
    lv_canvas_set_buffer(canvas, cbuf, CANVAS_ENNEMI_WIDTH, CANVAS_ENNEMI_HEIGHT, LV_IMG_CF_INDEXED_1BIT);
    lv_canvas_set_palette(canvas, 1, lv_color_make(255, 255, 0));
    lv_canvas_set_palette(canvas, 0, lv_color_make(0, 0, 0));
    lv_obj_set_pos(canvas, posX, posY);

    draw(); // On dessine l'ennemi
    
}

Ennemi::~Ennemi()
{

}

// Cette méthode permet de déplacement l'ennemi
void Ennemi::move()
{
    posX += velocityX;
    if (posX > 425) {
        velocityX *= -1;
        posX = 425;
        posY += velocityY;
    }
    else if (posX < -15) {
        velocityX *= -1;
        posX = -15;
        posY += velocityY;
    }
    if (posY > 225) {
        isOutofScreen = true;
    }
    lv_obj_set_pos(canvas, posX, posY);
}
// Cette méthode permet de dessiner l'ennemi
void Ennemi::draw(void)
{
    lv_color_t c0;
    lv_color_t c1;

    c0.full = 0; // Transparent
    c1.full = 1; // White

    lv_canvas_fill_bg(canvas, c0, LV_OPA_0);

    // Première rangée
    lv_canvas_set_px_color(canvas, 10, 0, c1);
    lv_canvas_set_px_color(canvas, 11, 0, c1);
    lv_canvas_set_px_color(canvas, 12, 0, c1);
    lv_canvas_set_px_color(canvas, 22, 0, c1);
    lv_canvas_set_px_color(canvas, 23, 0, c1);
    lv_canvas_set_px_color(canvas, 24, 0, c1);

    // Deuxième rangée
    for (uint8_t x = 10; x < 26; x++) {
        lv_canvas_set_px_color(canvas, x, 1, c1);
    }

    // Deuxième rangée
    for (uint8_t x = 6; x < 30; x++) {
        lv_canvas_set_px_color(canvas, x, 2, c1);
    }

    // Troisième rangée
    for (uint8_t x = 5; x < 31; x++) {
        lv_canvas_set_px_color(canvas, x, 3, c1);
    }

    // Troisième rangée
    for (uint8_t x = 4; x < 32; x++) {
        lv_canvas_set_px_color(canvas, x, 4, c1);
    }

    // Quatrième rangée
    for (uint8_t x = 2; x < 34; x+=2) {
        if (x != 10 && x != 24) {
            lv_canvas_set_px_color(canvas, x, 6, c1);
        }
    }

    // Cinquième rangée
    for (uint8_t x = 2; x < 34; x+=2) {
        lv_canvas_set_px_color(canvas, x, 8, c1);
    }

    // Sixième rangée
    lv_canvas_set_px_color(canvas, 4, 10, c1);
    lv_canvas_set_px_color(canvas, 6, 10, c1);
    lv_canvas_set_px_color(canvas, 10, 10, c1);
    lv_canvas_set_px_color(canvas, 12, 10, c1);
    lv_canvas_set_px_color(canvas, 22, 10, c1);
    lv_canvas_set_px_color(canvas, 24, 10, c1);
    lv_canvas_set_px_color(canvas, 28, 10, c1);
    lv_canvas_set_px_color(canvas, 30, 10, c1);

    // Septième rangée
    lv_canvas_set_px_color(canvas, 10, 12, c1);
    lv_canvas_set_px_color(canvas, 12, 12, c1);
    lv_canvas_set_px_color(canvas, 22, 12, c1);
    lv_canvas_set_px_color(canvas, 24, 12, c1);

    // Huitième rangée
    for (uint8_t x = 8; x < 14; x+=2) {
        lv_canvas_set_px_color(canvas, x, 14, c1);
    }
    for (uint8_t x = 20; x < 26; x+=2) {
        lv_canvas_set_px_color(canvas, x, 14, c1);
    }

    // Neuvième rangée
    for (uint8_t x = 4; x < 8; x+=2) {
        lv_canvas_set_px_color(canvas, x, 16, c1);
    }
    for (uint8_t x = 26; x < 30; x+=2) {
        lv_canvas_set_px_color(canvas, x, 16, c1);
    }

    // Dixième rangée
    lv_canvas_set_px_color(canvas, 0, 18, c1);
    lv_canvas_set_px_color(canvas, 2, 18, c1);
    lv_canvas_set_px_color(canvas, 30, 18, c1);
    lv_canvas_set_px_color(canvas, 32, 18, c1);
}

// Cette méthode permet de cacher l'ennemi
void Ennemi::hide(void) 
{
    lv_obj_add_flag(canvas, LV_OBJ_FLAG_HIDDEN);
    visible = false;
}

// Cette méthode permet de reset la position de l'ennemi
void Ennemi::resetPosition(short newX, short newY)
{
    posX = newX;
    posY = newY;
    lv_obj_set_pos(canvas, posX, posY);
    lv_obj_clear_flag(canvas, LV_OBJ_FLAG_HIDDEN);
    visible = true;
    pointDeVie = maxPointDeVie;
    velocityX = 40;
}