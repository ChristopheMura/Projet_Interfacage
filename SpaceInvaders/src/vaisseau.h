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

    void setPos(short *pos);                // Permet de définir la position du vaisseau
    void getPos(short *pos);                // Permet de retourner la position du vaisseau
    void draw(void);                        // Permet de dessiner le vaisseau dans le canvas
    short getX() const { return posX; }     // permet de retourner la position en X du vaisseau
    short getY() const { return posY; }     // Permet de retourner la position en Y du vaisseau
    bool isActive() const { return active; }// Permet de savoir si le vaisseau est actif ou non
    lv_obj_t* getCanvas() { return canvas; }// Permet de reoutrner le canvas du vaisseau
    void deactivate(void);                  // Permet de désactiver le vaisseau
    void reset();                           // Permet de remettre à 0 les atributs du vaisseau


private:
    short posX;
    short posY;
    lv_obj_t *canvas;
    lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(CANVAS_VAISSEAU_WIDTH, CANVAS_VAISSEAU_HEIGHT)];
    bool active;
};


#endif