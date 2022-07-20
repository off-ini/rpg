//
// Created by infini on 12/07/22.
//
#include <SFML/Graphics.hpp>

#include "windows/Menu.h"
#include "windows/ChoixPerso.h"
#include "windows/Scene.h"
#include "utils/consts.hpp"

using namespace sf;

int main(){
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), "RPG");
    Scene scene;
    int perso;

    if(Menu::menu(window) == 1){
        perso = ChoixPerso::choix(window);
        scene.scene1(window, perso);
    }

    return 0;
}