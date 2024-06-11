#include "game.h"

Game::Game()
{
    threadLvgl = new ThreadLvgl(30);
    threadLvgl->lock(); /* -------------------------------------- */

    window =  lv_obj_create(lv_scr_act());

    static lv_style_t style_window;
    lv_style_init(&style_window);
    lv_style_set_bg_color(&style_window, lv_color_hex(0x000000)); // C'est sensé être noir
    lv_style_set_bg_opa(&style_window, LV_OPA_100);
    lv_style_set_border_width(&style_window, 2);
    lv_style_set_border_color(&style_window, lv_color_black());
    lv_style_set_radius(&style_window, 0);


    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, 5);
    lv_style_set_bg_opa(&style, LV_OPA_0);
    lv_style_set_bg_color(&style, lv_palette_lighten(LV_PALETTE_GREY, 2));
    lv_style_set_border_width(&style, 1);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_pad_all(&style, 10);

    lv_style_set_text_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_text_letter_space(&style, 3);
    lv_style_set_text_line_space(&style, 20);
    //lv_style_set_text_decor(&style, LV_TEXT_DECOR_UNDERLINE);


    lv_obj_set_size(window, 480, 272);
    lv_obj_set_pos(window, 0, 0);

    lv_obj_add_style(window, &style_window, 0);

    // Désactiver le scroller horizontal
    lv_obj_clear_flag(window, LV_OBJ_FLAG_SCROLLABLE);
    // Désactiver le scroller vertical
    lv_obj_set_scrollbar_mode(window, LV_SCROLLBAR_MODE_OFF);

    vaisseau = new Vaisseau(window);
    projectile = new Projectile(window);

    canvasUltime = lv_canvas_create(window);

    lv_canvas_set_buffer(canvasUltime, cbufultime, CANVAS_ULTIME_WIDTH, CANVAS_ULTIME_HEIGHT, LV_IMG_CF_INDEXED_1BIT);
    lv_canvas_set_palette(canvasUltime, 1, lv_color_make(255, 0, 0));
    lv_canvas_set_palette(canvasUltime, 0, lv_color_make(0, 0, 0));
    lv_obj_set_pos(canvasUltime, 450, (SCREEN_HEIGHT/2)-75);

    
    lv_style_init(&styleGameOver);
    lv_style_set_text_font(&styleGameOver, LV_FONT_MONTSERRAT_32);  // Changer la police si nécessaire
    lv_style_set_text_color(&styleGameOver, lv_color_white());

    gameover_label = lv_label_create(window);
    lv_obj_add_style(gameover_label, &style, 0);

    lv_obj_add_flag(gameover_label, LV_OBJ_FLAG_HIDDEN);
    


    c0_ultime.full = 0; // Transparent
    c1_ultime.full = 1; // White

    resetUltime();
    
    for (short i=0; i<MAX_ENNEMIS; i++) {
        ennemies.emplace_back(window, -15 + i*40);
    }

    isReset = false;
    gameIsDone = false;
    counterEnemyDeath = 0;
    round = 1;
    bareUltime = 99;
    isUltimeReady = false;
    score = 0;
    speedEnnemy = 500;

    round_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(round_label, &style, 0);
    lv_label_set_text(round_label, "Round: 0");

    score_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(score_label, &style, 0);
    lv_label_set_text(score_label, "Score: 0");

    lv_obj_align(round_label, LV_ALIGN_TOP_MID, -100, 0);  // Ajuster les positions selon vos besoins
    lv_obj_align(score_label, LV_ALIGN_TOP_MID, 100, 0);   // Ajuster les positions selon vos besoins

    update_round_label();
    update_score_label();

    gameThread.start(callback(this, &Game::run));
    ennemiThread.start(callback(this, &Game::ennemiThreadFct));
    entrees.start(callback(this, &Game::lecture_entrees));

    threadLvgl->unlock(); /* ------------------------------------ */
}

Game::~Game()
{
    
}

void Game::run()
{
    while (1)
    {
        threadLvgl->lock(); /* -------------------------------------- */
        //lecture_entrees();
        vaisseauPos[0] = dx;
        vaisseauPos[1] = dy;

        
        if (gameIsDone) {
            show_game_over(round, score);
            if (isReset) {
                reset();
            }
        }
        else {
            if (vaisseau->isActive()) {
                vaisseau->setPos(vaisseauPos);
                if (vaisseauIsAttack && !projectile->isActive()) {
                    vaisseau->getPos(positionProjectile);
                    projectile->setPos(positionProjectile);
                    projectile->setActive();
                }

                if (vaisseauIsUltime && isUltimeReady && !projectile->isActiveUltime()) {
                    resetUltime();
                    vaisseau->getPos(positionProjectile);
                    projectile->setPosUltime(positionProjectile);
                    projectile->setActiveUltime();
                    isUltimeReady = false;
                    bareUltime = 99;
                }
                    
                if (projectile->isActive()) {
                    projectile->fire();
                }

                if (projectile->isActiveUltime()){
                    projectile->fireUltime();
                }

                for (auto& enemy : ennemies) {
                    if (enemy.visible) {
                        if (checkCollision(enemy, *projectile) | checkCollisionUltime(enemy, *projectile)) {
                            if (projectile->isActive()) {
                                projectile->deactivate();
                                enemy.pointDeVie -=1;
                            }
                            else if (projectile->isActiveUltime()) {
                                projectile->deactivateUltime();
                                enemy.pointDeVie -=3;
                            }
                            if (enemy.pointDeVie <= 0) {
                                enemy.pointDeVie = 0;
                                enemy.hide();
                                score += 100;
                                counterEnemyDeath++;
                                update_score_label();
                            }
                            updateUltime();
                                
                            }
                        if (checkCollisionBtwShipAndEnemy(enemy, *vaisseau)) {
                            gameIsDone = true;
                            enemy.hide();
                            vaisseau->deactivate();
                        }
                    }
                }
                if (counterEnemyDeath == MAX_ENNEMIS) {
                    round++;
                    for (auto &enemy : ennemies) {
                        enemy.resetPosition(-15 + (counterEnemyDeath-1)*40,0);
                        /*if (round%2 == 0) {
                            enemy.maxPointDeVie +=1;
                        }*/

                        counterEnemyDeath -=1;
                    }
                    update_round_label();
                    speedEnnemy -= 50;
                    if (speedEnnemy <= 50) {
                        speedEnnemy =  50;
                    }
                }    
            }
        }
        
        threadLvgl->unlock(); /* ------------------------------------ */

        ThisThread::sleep_for(20ms);
    }
}

// Vérifie si un projectile touche un ennemi
bool Game::checkCollision(const Ennemi& enemy, const Projectile& projectile) {
    if (!enemy.isVisible() || !projectile.isActive()) {
        return false;
    }

    short ex = enemy.getX();
    short ey = enemy.getY();
    short ew = 34;
    short eh = 20;

    short px = projectile.getX();
    short py = projectile.getY();
    short pw = 4;
    short ph = 10;

    return px < ex + ew && px + pw > ex && py < ey + eh && py + ph > ey;
}

// Vérifie si l'ultime touche un ennemi
// A faire (faire class projectile Ultime)
bool Game::checkCollisionUltime(const Ennemi& enemy, const Projectile& projectile) {
    if (!enemy.isVisible() || !projectile.isActiveUltime()) {
        return false;
    }

    short ex = enemy.getX();
    short ey = enemy.getY();
    short ew = 34;
    short eh = 20;

    short px = projectile.getUltimeX();
    short py = projectile.getUltimeY();
    short pw = 10;
    short ph = 10;

    return px < ex + ew && px + pw > ex && py < ey + eh && py + ph > ey;

    return false;
}
// -----------------------------------------

// Vérifie si un ennemi touche le vaisseau
bool Game::checkCollisionBtwShipAndEnemy(const Ennemi& enemy, const Vaisseau& vaisseau) {
    if (!enemy.isVisible() || !vaisseau.isActive()) {
        return false;
    }

    short ex = enemy.getX();
    short ey = enemy.getY();
    short ew = 34;
    short eh = 20;

    short px = vaisseau.getX();
    short py = vaisseau.getY();
    short pw = 30;
    short ph = 30;

    return px < ex + ew && px + pw > ex && py < ey + eh && py + ph > ey;
}

void Game::ennemiThreadFct() {
    while (1) {
        threadLvgl->lock(); /* -------------------------------------- */

        if (!gameIsDone) {
            for (auto& enemy : ennemies) {
                if (!enemy.isOutofScreen || !enemy.isVisible()) {
                    enemy.move();
                }
            }
        }
        
        threadLvgl->unlock(); /* ------------------------------------ */
        
        ThisThread::sleep_for(speedEnnemy);
    }
}

void Game::lecture_entrees()
{
    DigitalIn joyUp(D7);
    DigitalIn joyDown(D6);
    DigitalIn joyLeft(D5);
    DigitalIn joyRight(D4);

    DigitalIn bpStart(D2);
    DigitalIn bpUltime(D3);


    if (!joyUp) {
        dy = -3;
    }
    else if (!joyDown) {
        dy = 3;
    }
    else {
        dy = 0;
    }

    if (!joyLeft) {
        dx = -3;
    }
    else if (!joyRight) {
        dx = 3;
    }
    else {
        dx = 0;
    }
    if (!bpStart) {
        vaisseauIsAttack = true;
        if (!bpUltime) {
            isReset = true;
        }
    }
    else {
        vaisseauIsAttack = false;
    }
    if (!bpUltime) {
        vaisseauIsUltime = true;
        if (!bpStart) {
            isReset = true;
        }
    }
    else {
        vaisseauIsUltime = false;
    }
}

void Game::updateUltime()
{
    if (bareUltime > 0 && !isUltimeReady) {
        for (short j=bareUltime; j>=bareUltime-10; j--) {
            for (short i=1; i<5; i++) {
                lv_canvas_set_px_color(canvasUltime, i, j, c1_ultime);
            }
        }
    }

    bareUltime -= 10;
    if (bareUltime <= 0) {
        bareUltime = 0;
        isUltimeReady = true;
    }
}

void Game::resetUltime()
{
    lv_canvas_fill_bg(canvasUltime, c0_ultime, LV_OPA_COVER);

    for (short j=0; j<100; j++) {
        for (short i=0; i<6; i+=5) {
            lv_canvas_set_px_color(canvasUltime, i, j, c1_ultime);
        }
        if (j == 0) {
            lv_canvas_set_px_color(canvasUltime, 0, j, c1_ultime);
            lv_canvas_set_px_color(canvasUltime, 1, j, c1_ultime);
            lv_canvas_set_px_color(canvasUltime, 2, j, c1_ultime);
            lv_canvas_set_px_color(canvasUltime, 3, j, c1_ultime);
            lv_canvas_set_px_color(canvasUltime, 4, j, c1_ultime);
            lv_canvas_set_px_color(canvasUltime, 5, j, c1_ultime);
        }
        else if (j == 99) {
            lv_canvas_set_px_color(canvasUltime, 0, j, c1_ultime);
            lv_canvas_set_px_color(canvasUltime, 1, j, c1_ultime);
            lv_canvas_set_px_color(canvasUltime, 2, j, c1_ultime);
            lv_canvas_set_px_color(canvasUltime, 3, j, c1_ultime);
            lv_canvas_set_px_color(canvasUltime, 4, j, c1_ultime);
            lv_canvas_set_px_color(canvasUltime, 5, j, c1_ultime);
        }
    }
}

void Game::update_round_label()
{
    if (round_label != NULL) {
        char buf[32];
        snprintf(buf, sizeof(buf), "Round: %d", round);
        lv_label_set_text(round_label, buf);
    }
}

void Game::update_score_label()
{
    if (score_label != NULL) {
        char buf[32];
        snprintf(buf, sizeof(buf), "Score: %d", score);
        lv_label_set_text(score_label, buf);
    }
}

void Game::show_game_over(int nbround, int nbscore)
{
    // Nettoyer l'écran
    //lv_obj_clean(lv_scr_act());
    lv_obj_clear_flag(gameover_label, LV_OBJ_FLAG_HIDDEN);

    // Créer un message pour le GameOver avec le round et le score
    snprintf(buffGameOver, sizeof(buffGameOver), "Game Over\nRound: %d\nScore: %d \nPresser les deux boutons pour relancer", nbround, nbscore);

    // Créer un label GameOver avec un style différent si nécessaire
    
    lv_label_set_text(gameover_label, buffGameOver);

    // Centrer le texte dans le label GameOver
    lv_obj_set_width(gameover_label, 300);  // Définir la largeur du label sur la largeur de l'écran
    lv_obj_set_style_text_align(gameover_label, LV_TEXT_ALIGN_CENTER, 0);

    // Centrer le label GameOver
    lv_obj_align(gameover_label, LV_ALIGN_CENTER, 0, 0);

}

void Game::reset()
{
    resetUltime();
    gameIsDone = false;
    counterEnemyDeath = 0;
    round = 1;
    bareUltime = 99;
    isUltimeReady = false;
    score = 0;
    speedEnnemy = 500;
    int i=0;

    lv_obj_add_flag(gameover_label, LV_OBJ_FLAG_HIDDEN);
    update_round_label();

    for (auto &enemy : ennemies) {
        enemy.resetPosition(-15 + i*40,0);
        i++;
    }
    vaisseau->reset();
    isReset = false;
}