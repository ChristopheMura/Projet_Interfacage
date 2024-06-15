#ifndef GAME_H
#define GAME_H

#include <threadLvgl.h>
#include <vector>

#include "mbed.h"
#include "lvgl.h"

#include "vaisseau.h"
#include "projectile.h"
#include "ennemi.h"

#define MAX_ENNEMIS 8               // On définir le nombre max d'ennemis

#define CANVAS_ULTIME_WIDTH 6       // On définie la largeur du canvas d'ultime
#define CANVAS_ULTIME_HEIGHT 100    // On définie la hauteur du canvas d'ultime


class Game
{
public:
    Game();     // Contructeur de la classe Game
    ~Game();    // Destructeur de la classe Game

    void lecture_entrees();     // Tache pour lire les entrées
    void run();                 // Tache boucle du jeu
    void ennemiThreadFct();     // Tache deplacement des ennemis

    void reset(); // Fonction pour reset le jeu

    void updateUltime();    // Méthode pour mettre à jour l'ultime
    void resetUltime();     // Méthode pour reset l'ultime

    // Méthodes pour gérer toutes les collisions
    bool checkCollision(const Ennemi& enemy, const Projectile& projectile);
    bool checkCollisionUltime(const Ennemi& enemy, const Projectile& projectile);
    bool checkCollisionBtwShipAndEnemy(const Ennemi& enemy, const Vaisseau& vaisseau);

    // Méthodes de mise à jour des labels
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

    char buffGameOver[128];     // Buffer pour ecrire dans le label GameOver

    lv_obj_t * window;          // Création de la fenetre principale du jeu

    // Création des élément pour afficher le canvas de la bare d'ultime
    lv_obj_t *canvasUltime;
    lv_color_t cbufultime[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(CANVAS_ULTIME_WIDTH, CANVAS_ULTIME_HEIGHT)];
    lv_color_t c0_ultime;
    lv_color_t c1_ultime;

    Vaisseau *vaisseau;             // Création d'un objet vaisseau
    Projectile *projectile;         // Création d'un objet projectile
    std::vector<Ennemi> ennemies;   // Création des ennemis

    // Thread
    ThreadLvgl *threadLvgl;     // Thread d'affiche pour LVGL
    Thread ennemiThread;        // Thread de gestion des déplacement des ennemis
    Thread gameThread;          // Thread de gestion du jeu
    Thread entrees;             // Thread de gestion des entrées

    lv_obj_t * round_label;     // Création d'un objet round_label
    lv_obj_t * score_label;     // Création d'un objet score_label
    lv_obj_t * gameover_label;  // Création d'un objet gameover_label
};

#endif