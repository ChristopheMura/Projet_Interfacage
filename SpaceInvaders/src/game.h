#ifndef GAME_H
#define GAME_H

#include <threadLvgl.h>
#include <vector>

#include "mbed.h"
#include "lvgl.h"

#include "vaisseau.h"
#include "projectile.h"
#include "ennemi.h"

#define MAX_ENNEMIS 8

#define CANVAS_ULTIME_WIDTH 6
#define CANVAS_ULTIME_HEIGHT 100



class Game
{
public:
    Game();
    ~Game();

    void run();                 // Thread boucle du jeu
    void ennemiThreadFct();     // Thread deplacement des ennemis

    void reset(); // Fonction pour reset le jeu

    void lecture_entrees();
    void updateUltime();
    void resetUltime();

    bool checkCollision(const Ennemi& enemy, const Projectile& projectile);
    bool checkCollisionUltime(const Ennemi& enemy, const Projectile& projectile);
    bool checkCollisionBtwShipAndEnemy(const Ennemi& enemy, const Vaisseau& vaisseau);

    void update_round_label();
    void update_score_label();
    void show_game_over(int nbround, int nbscore);

private:
    bool gameIsDone;
    short dx, dy;
    bool vaisseauIsAttack = false;
    bool vaisseauIsUltime = false;
    short vaisseauPos[2];
    short positionProjectile[2];
    short counterEnemyDeath;
    short round;

    short bareUltime = 99;
    bool isUltimeReady;

    short score;
    short speedEnnemy;

    bool isReset;

    char buffGameOver[128];
    lv_style_t styleGameOver;

    lv_obj_t * window;
    lv_obj_t *canvasUltime;
    lv_color_t cbufultime[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(CANVAS_ULTIME_WIDTH, CANVAS_ULTIME_HEIGHT)];
    lv_color_t c0_ultime;
    lv_color_t c1_ultime;

    Vaisseau *vaisseau;
    Projectile *projectile;
    std::vector<Ennemi> ennemies;
    ThreadLvgl *threadLvgl;
    Thread ennemiThread;
    Thread gameThread;
    Thread entrees;

    lv_obj_t * round_label;
    lv_obj_t * score_label;
    lv_obj_t * gameover_label;
};

#endif