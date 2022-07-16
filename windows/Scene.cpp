//
// Created by infini on 15/07/22.
//

#include <iostream>
#include <vector>

#include "../utils/consts.hpp"
#include "../utils/tilemap.hpp"
#include "../modeles/Creature.h"
#include "../modeles/Personnage.h"
#include "Scene.h"

using namespace sf;

int Scene::scene1(sf::RenderWindow& window){
    Music music;
    View view;
    if(!music.openFromFile("./assets/audio/Town.ogg")){
        perror("'Town.ogg' load error");
        return -1;
    }
    music.setVolume(0.8);
    music.setLoop(true);
    music.play();

    Personnage perso;
    perso.loadTexture("./assets/sprites/actors/actor1.png");
    perso.sprite.setPosition(150, 150);
    std::vector<Creature *> p_list;
    for(int i = 0; i < 3; i++) p_list.push_back(new Personnage());
    for(int i = 0; i < p_list.size(); i++) p_list[i]->loadTexture("./assets/sprites/actors/actor"+ to_string((i+2)) +".png");
    p_list[0]->sprite.setPosition(230, 230);
    p_list[1]->sprite.setPosition(290, 250);
    p_list[2]->sprite.setPosition(150, 150);

    const int level[] =
            {
                    65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65,
                    65, 65, 65, 65, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 65,
                    65, 1, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 65,
                    65, 1, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 65, 65,
                    65, 1, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 65, 65,
                    65, 1, 3, 3, 1, 3, 3, 65, 3, 3, 3, 3, 3, 3, 1, 65,
                    65, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 65,
                    65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65,
                    65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65,
                    65, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 65,
                    65, 1, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 65,
                    65, 1, 3, 3, 65, 3, 3, 1, 3, 65, 65, 65, 3, 3, 65, 65,
                    65, 1, 3, 3, 1, 3, 3, 1, 3, 65, 65, 65, 3, 3, 65, 65,
                    65, 1, 3, 3, 1, 3, 3, 65, 3, 65, 65, 65, 3, 3, 1, 65,
                    65, 1, 1, 1, 1, 1, 1, 1, 1, 65, 65, 65, 1, 1, 65, 65,
                    65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65,
            };

    TileMap map("./assets/sprites/map/map1.png", level);
    if (!map.load())
        return -1;

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){

            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }

            /*if (Mouse::isButtonPressed(Mouse::Right))
            {
                if(p_list.size() > 0)
                    p_list.pop_back();
            }*/

            Vector2f MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                std::cout<< "X: " << MousePos.x << " - Y: " << MousePos.y <<std::endl;
            }

            perso.setCible(p_list);
            perso.move(event, map);

        }


        for (int i = 0; i < p_list.size(); ++i) {
            p_list[i]->setCible(perso);
            p_list[i]->move(map);
        }

        view.reset(FloatRect(0,0, SCREEN_W, SCREEN_H));
        Vector2f viewPos(SCREEN_W/2, SCREEN_H/2);
        // viewPos.x = (sprPerso.getPosition().x + 24) - (SCREEN_W/2);
        // viewPos.y = (sprPerso.getPosition().y + 24) - (SCREEN_H/2);
        viewPos.x = (perso.sprite.getPosition().x + 24) - (SCREEN_W/2);
        viewPos.y = (perso.sprite.getPosition().y + 24) - (SCREEN_H/2);
        if(viewPos.x <= 0) viewPos.x = 0;
        if(viewPos.y <= 0) viewPos.y = 0;
        view.reset(FloatRect(viewPos.x,viewPos.y, SCREEN_W, SCREEN_H));

        window.setView(view);

        window.clear();

        window.draw(map);
        //window.draw(sprPerso);
        for (int i = 0; i < p_list.size(); ++i) {
            window.draw(p_list[i]->sprite);
        }
        window.draw(perso.sprite);

        window.display();
    }
}