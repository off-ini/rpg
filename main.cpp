//
// Created by infini on 12/07/22.
//
#include <SFML/Graphics.hpp>

#include "windows/Menu.h"
#include "windows/Scene.h"
#include "utils/consts.hpp"
#include "utils/tilemap.hpp"
#include "modeles/Personnage.h"
#include "data/Parser.h"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), "RPG");
    Scene scene;

    if (Menu::menu(window) == 1) {
        scene.scene1(window);
    }

    //Parser::test();

    return 0;
}