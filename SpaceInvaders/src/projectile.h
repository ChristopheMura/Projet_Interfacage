#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "lvgl.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define CANVAS_PROJECTILE_WIDTH 4
#define CANVAS_PROJECTILE_HEIGHT 10

#define CANVAS_PROJECTILE_ULTIME_WIDTH 10
#define CANVAS_PROJECTILE_ULTIME_HEIGHT 10

class Projectile
{
public:
    Projectile(lv_obj_t *windows);
    ~Projectile();

    void setPos(short pos[2]);
    void setPosUltime(short pos[2]);

    void draw();
    void drawUltime();

    void setActive();
    void setActiveUltime();

    void fire();
    void fireUltime();

    void deactivate(void);
    void deactivateUltime(void);

    short getX() const { return posX; }
    short getY() const { return posY; }
    short getUltimeX()const { return ultimePosX; }
    short getUltimeY() const { return ultimeposY; }

    lv_obj_t* getCanvas() { return canvas; }
    lv_obj_t* getCanvasUltime() { return canvasUltime; }

    bool isActive() const { return active; }
    bool isActiveUltime() const { return activeUltime; }

private:
    short posX;
    short posY;
    short ultimePosX;
    short ultimeposY;

    lv_obj_t *canvas;
    lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(CANVAS_PROJECTILE_WIDTH, CANVAS_PROJECTILE_HEIGHT)];

    lv_obj_t *canvasUltime;
    lv_color_t cbufUltime[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(CANVAS_PROJECTILE_ULTIME_WIDTH, CANVAS_PROJECTILE_ULTIME_HEIGHT)];

    bool active;
    bool activeUltime;
};

#endif