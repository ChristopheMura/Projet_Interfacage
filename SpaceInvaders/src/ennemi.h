#ifndef ENNEMI_H
#define ENNEMI_H

#include "lvgl.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define CANVAS_ENNEMI_WIDTH 34
#define CANVAS_ENNEMI_HEIGHT 20

class Ennemi
{
public:
    Ennemi(lv_obj_t *windows, short pPosX);
    ~Ennemi();

    void move();
    void draw(void);
    short getX() const { return posX; }
    short getY() const { return posY; }
    bool isVisible() const { return visible; }
    lv_obj_t* getCanvas() { return canvas; }
    void hide(void);
    void resetPosition(short newX, short newY);

private:
    short posX;
    short posY;
    short velocityX;
    short velocityY;
    lv_obj_t *canvas;
    lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(CANVAS_ENNEMI_WIDTH, CANVAS_ENNEMI_HEIGHT)];
    

public:
    bool isOutofScreen;
    bool isDestroy;
    bool visible;
    short pointDeVie;
    short maxPointDeVie;

};

#endif