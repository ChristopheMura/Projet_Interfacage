#ifndef ENNEMI_H
#define ENNEMI_H

#include "lvgl.h"

#define SCREEN_WIDTH 480        // On définie la largeur du canvas d'ultime
#define SCREEN_HEIGHT 272       // On définie la hauteur du canvas d'ultime

#define CANVAS_ENNEMI_WIDTH 34  // On définie la largeur du canvas ennemis
#define CANVAS_ENNEMI_HEIGHT 20 // On définie la hauteur du canvas ennemis

class Ennemi
{
public:
    Ennemi(lv_obj_t *windows, short pPosX);
    ~Ennemi();

    void move();                                // Méthode pour deplacer l'énnemis
    void draw(void);                            // Méthode pour dessiner l'ennemis dans le canvas
    short getX() const { return posX; }         // Méthode pour retourner la position X de l'ennemi
    short getY() const { return posY; }         // Méthode pour retourner la position Y de l'ennemi
    bool isVisible() const { return visible; }  // Méthode pour savoir si l'ennemi est visible ou non
    lv_obj_t* getCanvas() { return canvas; }    // Méthode pour retourner le canvas de l'ennemi
    void hide(void);                            // Méthode pour ne plus afficher l'ennemi
    void resetPosition(short newX, short newY); // Méthode pour reset la position de l'ennemi

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