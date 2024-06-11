#ifndef VAISSEAU_H
#define VAISSEAU_H

#include "lvgl.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define CANVAS_VAISSEAU_WIDTH 30
#define CANVAS_VAISSEAU_HEIGHT 30

class Vaisseau
{
public:
    Vaisseau(lv_obj_t *windows);
    ~Vaisseau();

    void setPos(short *pos);
    void getPos(short *pos);
    void draw(void);
    short getX() const { return posX; }
    short getY() const { return posY; }
    bool isActive() const { return active; }
    lv_obj_t* getCanvas() { return canvas; }
    void deactivate(void);
    void updateUltime();
    void reset();


private:
    short posX;
    short posY;
    lv_obj_t *canvas;
    lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(CANVAS_VAISSEAU_WIDTH, CANVAS_VAISSEAU_HEIGHT)];
    bool active;
};


#endif