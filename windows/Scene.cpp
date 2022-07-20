//
// Created by infini on 15/07/22.
//

#include <iostream>
#include <vector>

#include "../utils/consts.hpp"
#include "../utils/distribution.h"
#include "../utils/tilemap.hpp"
#include "../modeles/Creature.h"
#include "../modeles/Personnage.h"
#include "../modeles/Batiment.h"
#include "../modeles/Bouclier.h"
#include "../modeles/Epee.h"
#include "../modeles/Hache.h"
#include "../modeles/Massue.h"
#include "../modeles/Piece.h"
#include "Scene.h"

using namespace sf;

int getIndex(vector<Creature*> list, Creature* perso){
    std::vector<Creature*>::iterator itr = std::find(list.begin(), list.end(), perso);

    if (itr != list.cend()) {
        return std::distance(list.begin(), itr);
    }

    return -1;
}

Scene::Scene():batiment(){}

void Scene::setView(Personnage * personnage){
    view.reset(FloatRect(0,0, SCREEN_W, SCREEN_H));
    Vector2f viewPos(SCREEN_W/2, SCREEN_H/2);
    // viewPos.x = (sprPerso.getPosition().x + 24) - (SCREEN_W/2);
    // viewPos.y = (sprPerso.getPosition().y + 24) - (SCREEN_H/2);
    viewPos.x = (personnage->sprite.getPosition().x + 24) - (SCREEN_W/2);
    viewPos.y = (personnage->sprite.getPosition().y + 24) - (SCREEN_H/2);
    if(viewPos.x <= 0) viewPos.x = 0;
    if(viewPos.y <= 0) viewPos.y = 0;
    if(viewPos.x + SCREEN_W >= TILE_SIZE_X * TILE_WIDTH) viewPos.x = (TILE_SIZE_X * TILE_WIDTH) - SCREEN_W;
    if(viewPos.y + SCREEN_H >= TILE_SIZE_Y * TILE_HEIGHT) viewPos.y = (TILE_SIZE_Y * TILE_HEIGHT) - SCREEN_H;
    view.reset(FloatRect(viewPos.x,viewPos.y, SCREEN_W, SCREEN_H));
}

void Scene::createLevel1(){
    pieces.push_back(new Piece(1,1, 12, 22));
    pieces.push_back(new Piece(12,1, 5, 14));
    pieces.push_back(new Piece(12,14, 5, 9));
    pieces.push_back(new Piece(16,1, 10, 9));
    pieces.push_back(new Piece(19,9, 7, 6));
    pieces.push_back(new Piece(19,14, 7, 9));
    pieces.push_back(new Piece(25,11, 26, 20));
    pieces.push_back(new Piece(50,6, 13, 16));
    pieces.push_back(new Piece(62,6, 12, 16));
    pieces.push_back(new Piece(50,6, 10, 8));
    pieces.push_back(new Piece(65,22, 10, 11));
    pieces.push_back(new Piece(1,27, 13, 22));
    pieces.push_back(new Piece(13,28, 13, 21));
    pieces.push_back(new Piece(50,33, 12, 16));
    pieces.push_back(new Piece(61,13, 13, 16));

    batiment.setPiece(pieces);
}

sf::Vector2f Scene::randomPosition(){

    int sizePieces = pieces.size();
    int index = Gen::distNumber(0, sizePieces - 1);
    Piece * piece = pieces[index];
    int Xmin, Xmax, Ymin, Ymax;
    Xmin = static_cast<int>(piece->getPosition().x) + TILE_SIZE_X + 5;
    Xmax = (piece->getLongueur() + static_cast<int>(piece->getPosition().x)) - (PERSO_WIDTH + TILE_SIZE_X);
    Ymin = static_cast<int>(piece->getPosition().y) + TILE_SIZE_Y + 5;
    Ymax = (piece->getLargeur() + static_cast<int>(piece->getPosition().y)) - (PERSO_HEIGHT + TILE_SIZE_Y);

    //std::cout<< index + 1 << " X : " << Xmin << " - " << Xmax << " Y : " << Ymin << " - "  << Ymax <<std::endl;

    float x = (float) Gen::distNumber(Xmin,  Xmax);
    float y = (float) Gen::distNumber(Ymin,  Ymax);

    sf::Vector2f pos(x, y);

    return pos;
}

int Scene::scene1(sf::RenderWindow& window, int choix){

    Music music;
    View mapView;
    View progressView;

    Texture texProgress;
    Sprite sprProgress;
    RectangleShape progress;

    Texture texArme;
    Sprite sprArme;

    if(!music.openFromFile("./assets/audio/Town.ogg")){
        perror("'Town.ogg' load error");
        return -1;
    }
    music.setVolume(0.8);
    music.setLoop(true);
    music.play();

    createLevel1();

    if(!texProgress.loadFromFile("./assets/sprites/progress.png")){
        perror("'Progress' load error");
        return -1;
    }

    sprProgress.setTexture(texProgress);
    sprProgress.setPosition(5, 5);
    sprProgress.setScale(0.8f, 0.8f);

    progress.setPosition(55, 18);
    progress.setFillColor(Color::Red);
    progress.setSize(Vector2f(115, 25));

    if(!texArme.loadFromFile("./assets/sprites/armes.png")){
        perror("'Armes' load error");
        return -1;
    }

    sprArme.setTexture(texArme);
    sprArme.setTextureRect(IntRect(48, 20, 40, 30));
    sprArme.setScale(0.8f, 0.8f);
    sprArme.setPosition(20, 15);

    Personnage perso;
    perso.load(choix);
    perso.sprite.setPosition(150, 775);
    perso.setNiveauHabilite(5);
    perso.setNiveauSante(100);
    perso.getSac()->addOutil(new Bouclier);
    perso.getSac()->addOutil(new Epee);
    perso.getSac()->addOutil(new Hache);
    perso.getSac()->addOutil(new Massue);


    sf::CircleShape PersoPosition(60.f);
    PersoPosition.setFillColor(sf::Color::Red);

    std::vector<Creature *> p_list;
    Personnage * second = NULL;

    for(int i = 0; i < PERSO_NOMBRE; i++){
        second = new Personnage();;
        int number = Gen::distNumber(2, 8);
        second->load(number);
        Vector2f position = randomPosition();
        //std::cout<< "PERSO :" << i + 1 << " X: " << position.x << " - Y: " << position.y << " TEXT : " << number <<std::endl;
        second->sprite.setPosition(position);
        second->setNiveauHabilite(3);
        second->setNiveauSante(50);
        second->getSac()->addOutil(new Bouclier);
        second->getSac()->addOutil(new Epee);
        p_list.push_back(second);
    }

    TileMap map("./assets/sprites/map/map2.png", level);
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

            Vector2f MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                std::cout<< "X: " << MousePos.x << " - Y: " << MousePos.y <<std::endl;
            }

            if(Keyboard::isKeyPressed(Keyboard::Space) && perso.getCible() != NULL){
                int index = getIndex(p_list, perso.getCible());
                Battle::battle(window, perso, (Personnage*)perso.getCible(), index);
            }

            perso.setCible(p_list);
            perso.move(event, map);
            PersoPosition.setPosition(perso.getPosition().x, perso.getPosition().y);
        }


        for (int i = 0; i < p_list.size(); ++i) {
            p_list[i]->setCible(perso);
            p_list[i]->move(map);
        }

        setView(&perso);
        window.setView(view);

        window.clear();

        window.draw(map);
        //window.draw(sprPerso);
        for (int i = 0; i < p_list.size(); ++i) {
            window.draw(p_list[i]->sprite);
        }
        window.draw(perso.sprite);

        mapView.reset(FloatRect(0,0, SCREEN_W * 4, SCREEN_H * 4));
        mapView.setViewport(FloatRect(0.79f, 0.79f, 0.20f, 0.20f));

        window.setView(mapView);

        window.draw(map);
        window.draw(PersoPosition);

        progressView.reset(FloatRect(0,0, SCREEN_W, SCREEN_H));
        window.setView(progressView);

        window.draw(progress);
        window.draw(sprProgress);
        window.draw(sprArme);

        window.display();
    }
}