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
#include "../modeles/Feu.h"
#include "../modeles/Glace.h"
#include "../modeles/Foudre.h"
#include "../modeles/CleTeleportation.h"
#include "../modeles/PotionRegeneration.h"
#include "../modeles/Piece.h"
#include "Scene.h"
#include "../modeles/Soldat.h"
#include "../modeles/Druide.h"
#include "../modeles/Ouvrier.h"
#include "../modeles/Religieux.h"

#include "../data/Parser.h"

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

Vector2f updateProgress(Vector2f& rect , Personnage & perso){
    Vector2f tmp = rect;
    tmp.x = (tmp.x * perso.getNiveauSante()) / 100.f;
    return tmp;
}

int Scene::scene1(sf::RenderWindow& window, int choix){

    Clock timer;
    Music music;
    View mapView;
    View progressView;

    Texture texProgress;
    Sprite sprProgress;
    RectangleShape progress;

    Font font;
    if(!font.loadFromFile("./assets/fonts/console/Inconsolata-Bold.ttf")){
        perror("'Inconsolata' load error");
    }

    Text text;
    text.setFont(font);
    text.setFillColor(Color::Yellow);
    text.setCharacterSize(25);
    text.setPosition(480, 10);

    bool displaySave = false;
    Text textSave;
    textSave.setFont(font);
    textSave.setString("Sauvegarge Reuissie !!!");
    textSave.setFillColor(Color::Red);
    textSave.setCharacterSize(25);
    textSave.setPosition(160, 220);

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
    Vector2f rect(115, 25);
    progress.setSize(rect);

    std::vector<Creature *> liste_load;

    Personnage perso;

    if(choix != 200){
        perso.load(choix);
        perso.sprite.setPosition(150, 775);
        perso.setNiveauSante(100);
    }else{
        Creature * tmpPerso = liste_load[liste_load.size() - 1];
        perso.sprite = tmpPerso->sprite;
        perso.setNiveauSante(tmpPerso->getNiveauSante());
    }

    perso.setNiveauHabilite(5);
    perso.getSac()->addOutil(new Bouclier);
    perso.getSac()->addOutil(new Epee);
    perso.getSac()->addOutil(new Hache);
    perso.getSac()->addOutil(new Massue);
    perso.getSac()->addOutil(new Glace);
    perso.getSac()->addOutil(new Feu);
    perso.getSac()->addOutil(new Foudre);
    perso.getSac()->addOutil(new PotionRegeneration);
    perso.getSac()->addOutil(new CleTeleportation);



    sf::CircleShape PersoPosition(60.f);
    PersoPosition.setFillColor(sf::Color::Red);

    std::vector<CircleShape> CreaturesPosition;
    std::vector<Creature *> p_list;
    Personnage * second = NULL;
    int persoType = 0;

    if(choix != 200){
        for(int i = 0; i < PERSO_NOMBRE; i++){
            CircleShape circle(50);
            circle.setFillColor(Color::Blue);
            persoType = Gen::distNumber(1, 4);
            switch (persoType) {
                case 1:
                    second = new Soldat();
                    break;
                case 2:
                    second = new Druide();
                    break;
                case 3:
                    second = new Ouvrier();
                    break;
                case 4:
                    second = new Religieux();
                    break;
            }

            /*int number = Gen::distNumber(2, 8);
            second->load(number);*/
            Vector2f position = randomPosition();
            //std::cout<< "PERSO :" << i + 1 << " X: " << position.x << " - Y: " << position.y << " TEXT : " << number <<std::endl;
            second->sprite.setPosition(position);

            p_list.push_back(second);

            circle.setPosition(position);
            CreaturesPosition.push_back(circle);
        }
    }else{
        liste_load.pop_back();
        p_list = liste_load;
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
                case sf::Event::TextEntered:
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                        //std::cout<< "Ctrl S" <<endl;
                        std::vector<Creature *> liste_save;
                        for(int i = 0; i < p_list.size(); i++){
                            liste_save.push_back(p_list[i]);
                        }
                        liste_save.push_back(&perso);

                        Parser::save(liste_save);
                        displaySave = true;

                        std::cout<< "Saved !!!" <<endl;
                    }

                    break;
                default:
                    break;
            }

            if(timer.getElapsedTime().asSeconds() >= 5){
                displaySave = false;
                timer.restart();
            }

            progress.setSize(updateProgress(rect, perso));

            Vector2f MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                std::cout<< "X: " << MousePos.x << " - Y: " << MousePos.y <<std::endl;
            }

            if(Keyboard::isKeyPressed(Keyboard::Space) && perso.getCible() != NULL){
                int index = getIndex(p_list, perso.getCible());
                int issue = Battle::battle(window, perso, (Personnage*)perso.getCible(), index);
                Creature * creature = p_list[index];
                CircleShape creaturePos = CreaturesPosition[index];

                switch (issue) {
                    case 1:
                        //std::remove(p_list.begin(), p_list.end(), creature);
                        //std::remove(CreaturesPosition.begin(), CreaturesPosition.end(), creaturePos);
                        return 0;
                        break;
                    case 2:
                        std::remove(p_list.begin(), p_list.end(), creature);
                        //std::remove(CreaturesPosition.begin(), CreaturesPosition.end(), creaturePos);
                        break;
                    case 100:
                        perso.sprite.setPosition(randomPosition());
                        break;
                    default:
                        break;
                }

                std::cout<< "Enémi : " << p_list.size() <<endl;
                text.setString(L"Enémi:" + to_string(p_list.size()));
            }

            perso.setCible(p_list);
            perso.move(event, map);
            PersoPosition.setPosition(perso.getPosition().x, perso.getPosition().y);
        }


        for (int i = 0; i < p_list.size(); ++i) {
            p_list[i]->setCible(perso);
            p_list[i]->move(map);
            CreaturesPosition[i].setPosition(p_list[i]->sprite.getPosition());
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

        for (int i = 0; i < CreaturesPosition.size(); ++i) {
            window.draw(CreaturesPosition[i]);
        }

        progressView.reset(FloatRect(0,0, SCREEN_W, SCREEN_H));
        window.setView(progressView);

        window.draw(progress);
        window.draw(sprProgress);
        window.draw(text);
        if(displaySave)
            window.draw(textSave);

        if(perso.getOutil() != NULL){
            perso.getOutil()->spriteMini.setScale(0.8, 0.8);
            perso.getOutil()->spriteMini.setPosition(21, 18);
            window.draw(perso.getOutil()->spriteMini);
            perso.getOutil()->spriteMini.setScale(1, 1);
        }

        window.display();
    }
}