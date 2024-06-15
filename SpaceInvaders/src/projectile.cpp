#include "projectile.h"

Projectile::Projectile(lv_obj_t *windows)
{
    canvas = lv_canvas_create(windows/*lv_scr_act()*/); // Création du canvas du projectile
    canvasUltime = lv_canvas_create(windows);   //Création du canvas du projectile ultime

    // Initialisation des atributs
    posX = 0;
    posY = 0;
    ultimePosX = 0;
    ultimeposY = 0;
    active = false;
    activeUltime = false;

    // Initialisation du canvas du projectile
    lv_canvas_set_buffer(canvas, cbuf, CANVAS_PROJECTILE_WIDTH, CANVAS_PROJECTILE_HEIGHT, LV_IMG_CF_INDEXED_1BIT);
    lv_canvas_set_palette(canvas, 1, lv_color_make(127, 0, 255));
    lv_canvas_set_palette(canvas, 0, lv_color_make(0, 0, 0));
    lv_obj_set_pos(canvas, posX, posY);

    // Initialisation du canvas du projectile ultime
    lv_canvas_set_buffer(canvasUltime, cbufUltime, CANVAS_PROJECTILE_ULTIME_WIDTH, CANVAS_PROJECTILE_ULTIME_HEIGHT, LV_IMG_CF_INDEXED_1BIT);
    lv_canvas_set_palette(canvasUltime, 1, lv_color_make(255, 0, 0));
    lv_canvas_set_palette(canvasUltime, 0, lv_color_make(0, 0, 0));
    lv_obj_set_pos(canvasUltime, ultimePosX, ultimeposY);

    // Désactive les projectils pour éviter qu'il ne soient visible au lancement sans avoir préalablement tiré
    deactivate();
    deactivateUltime();

}

// Ces méthodes permettent de définir la position des projectiles
void Projectile::setPos(short pos[2])
{
    posX = pos[0]+13;
    posY = pos[1]+4;

    lv_obj_set_pos(canvas, posX, posY);
}

void Projectile::setPosUltime(short pos[2])
{
    ultimePosX = pos[0]+10;
    ultimeposY = pos[1];
    lv_obj_set_pos(canvasUltime, ultimePosX, ultimeposY);
}
// ----------------------------------------------------------------------------
// Ces méthodes permettent de désactiver les projectiles
void Projectile::deactivate(void)
{
    lv_obj_add_flag(canvas, LV_OBJ_FLAG_HIDDEN);
    active = false;
}

void Projectile::deactivateUltime(void)
{
    lv_obj_add_flag(canvasUltime, LV_OBJ_FLAG_HIDDEN);
    activeUltime = false;
}
// ----------------------------------------------------------------------------
// Ces méthodes permettent de déplacer les projectiles
void Projectile::fire()
{
    posY -= 5;

    if (posY <= -50) {
        active = false;
    }

    lv_obj_set_pos(canvas, posX, posY);
}

void Projectile::fireUltime()
{
    ultimeposY -= 7;

    if (ultimeposY <= -50) {
        activeUltime = false;
    }

    lv_obj_set_pos(canvasUltime, ultimePosX, ultimeposY);
}
// ----------------------------------------------------------------------------
// Ces méthodes permettnt de déssiner les projectiles
void Projectile::draw()
{
    lv_color_t c0;
    lv_color_t c1;

    c0.full = 0; // Transparent
    c1.full = 1; // White

    lv_canvas_fill_bg(canvas, c0, LV_OPA_0);
    
    lv_canvas_set_px_color(canvas, 1, 0, c1);
    lv_canvas_set_px_color(canvas, 2, 0, c1);

    for (uint8_t y = 1; y < CANVAS_PROJECTILE_HEIGHT-1; y++) {
        for (uint8_t x = 0; x < CANVAS_PROJECTILE_WIDTH; x++) {
            lv_canvas_set_px_color(canvas, x, y, c1);
        }
    }

    lv_canvas_set_px_color(canvas, 1, 9, c1);
    lv_canvas_set_px_color(canvas, 2, 9, c1);
}

void Projectile::drawUltime()
{
    lv_color_t c0;
    lv_color_t c1;

    c0.full = 0; // Transparent
    c1.full = 1; // White

    lv_canvas_fill_bg(canvasUltime, c0, LV_OPA_0);

    int cx = 5;
    int cy = 5;
    // Rayon du cercle
    int radius = 4;

    // Dessiner le cercle pixel par pixel
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                lv_canvas_set_px(canvasUltime, cx + x, cy + y, c1);
            }
        }
    }
}
// ----------------------------------------------------------------------------
// Ces méthodes permettent de savoir si les projectiles sont actives
void Projectile::setActive()
{
    draw();
    lv_obj_clear_flag(canvas, LV_OBJ_FLAG_HIDDEN);
    active = true;
}

void Projectile::setActiveUltime()
{
    drawUltime();
    lv_obj_clear_flag(canvasUltime, LV_OBJ_FLAG_HIDDEN);
    activeUltime = true;
}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------