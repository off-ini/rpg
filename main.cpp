//
// Created by infini on 12/07/22.
//
#include <SFML/Graphics.hpp>

#include "windows/Menu.h"
#include "windows/ChoixPerso.h"
#include "windows/Scene.h"
#include "utils/consts.hpp"
//#include "data/Parser.h"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(SCREEN_W, SCREEN_H), "RPG");
    Scene scene;
    int status;
    int perso;

    bool running = true;

    while (running){
        status = Menu::menu(window);
        if(status == 1){
            perso = ChoixPerso::choix(window);
            scene.scene1(window, perso);
        }else if(status == 2){
            //scene.scene1(window, 200);
        }else{
            running = false;
        }
    }


    //Parser::test();

    return 0;
}