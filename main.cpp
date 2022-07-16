//
// Created by infini on 12/07/22.
//
#include <SFML/Graphics.hpp>

#include "windows/Menu.h"
#include "windows/Scene.h"
#include "utils/consts.hpp"
#include "utils/tilemap.hpp"
#include "modeles/Personnage.h"

using namespace sf;

int main(){
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), "RPG");

    if(Menu::menu(window) == 1){
        Scene::scene1(window);
    }

    return 0;
}