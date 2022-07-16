//
// Created by infini on 15/07/22.
//
#include <iostream>

#include "../utils/consts.hpp"
#include "Menu.h"

using namespace sf;

int Menu::menu(RenderWindow& window){

    Music music;
    if(!music.openFromFile("./assets/audio/Castle.ogg")){
        perror("'Castle.ogg' load error");
        return -1;
    }
    music.setVolume(0.8);
    music.setLoop(true);
    music.play();

    SoundBuffer soundUpBuffer;
    if(!soundUpBuffer.loadFromFile("./assets/audio/Up.ogg")){
        perror("'Up.ogg' load error");
        return -1;
    }
    Sound soundUp;
    soundUp.setBuffer(soundUpBuffer);

    Font fonTeko;
    Font fonSkranji;

    if(!fonTeko.loadFromFile("./assets/fonts/teko/Teko-Regular.ttf")){
        perror("'fonTeko' load error");
        return -1;
    }

    if(!fonSkranji.loadFromFile("./assets/fonts/skranji/Skranji-Regular.ttf")){
        perror("'fonTeko' load error");
        return -1;
    }

    Texture texGate;
    Texture texMenu;
    Texture texCadre;

    if(!texGate.loadFromFile("./assets/sprites/bg/gate.png")){
        perror("'texGate' load error");
        return -1;
    }

    if(!texMenu.loadFromFile("./assets/sprites/menu.png")){
        perror("'texMenu' load error");
        return -1;
    }

    if(!texCadre.loadFromFile("./assets/sprites/cadre.png")){
        perror("'texCadre' load error");
        return -1;
    }

    texGate.setSmooth(true);
    texMenu.setSmooth(true);
    texCadre.setSmooth(true);

    Sprite sprBg;
    Sprite sprMenu;
    Sprite sprCadre;

    sprBg.setTexture(texGate);
    sprBg.scale(Vector2f(0.8, 0.7));

    sprMenu.setTexture(texMenu);
    sprMenu.setPosition((SCREEN_W / 2) - (180/2) + 30, (SCREEN_H / 3) + 50);

    sprCadre.setTexture(texCadre);
    sprCadre.setColor(Color::Green);
    sprCadre.scale(Vector2f(0.6, 0.5));
    sprCadre.setPosition((SCREEN_W / 2) - (300/2) + 30, 0);

    Text txtTitle;
    Text txtPlay;
    Text txtSetting;
    Text txtExit;

    txtTitle.setFont(fonTeko);
    txtTitle.setString(L"RPG Game");
    txtTitle.setCharacterSize(64);
    txtTitle.setFillColor(Color::Green);
    txtTitle.setPosition((SCREEN_W/2) - 64, 30);

    txtPlay.setFont(fonSkranji);
    txtPlay.setString(L"Jouer");
    txtPlay.setCharacterSize(28);
    txtPlay.setFillColor(Color::White);
    txtPlay.setPosition((SCREEN_W/2) - 8, (SCREEN_H / 3) + 60);

    txtSetting.setFont(fonSkranji);
    txtSetting.setString(L"Paramètres");
    txtSetting.setCharacterSize(24);
    txtSetting.setFillColor(Color::White);
    txtSetting.setPosition((SCREEN_W/2) - 35, (SCREEN_H / 3) + 108);

    txtExit.setFont(fonSkranji);
    txtExit.setString(L"Quitter");
    txtExit.setCharacterSize(28);
    txtExit.setFillColor(Color::White);
    txtExit.setPosition((SCREEN_W/2) - 16, (SCREEN_H / 3) + 150);


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

            Vector2i MousePos = Mouse::getPosition(window);

            if(txtPlay.getGlobalBounds().contains(MousePos.x, MousePos.y)){
                txtPlay.setCharacterSize(32);
                txtPlay.setFillColor(Color::Green);
                txtPlay.setPosition((SCREEN_W/2) - 20, (SCREEN_H / 3) + 60);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    soundUp.play();
                    std::cout<< "Clique : Play" <<std::endl;
                    //window.close();
                    return 1;
                }
            }
            else{
                txtPlay.setCharacterSize(28);
                txtPlay.setFillColor(Color::White);
                txtPlay.setPosition((SCREEN_W/2) - 10, (SCREEN_H / 3) + 60);
            }

            if(txtSetting.getGlobalBounds().contains(MousePos.x, MousePos.y)){
                txtSetting.setCharacterSize(28);
                txtSetting.setFillColor(Color::Green);
                txtSetting.setPosition((SCREEN_W/2) - 45, (SCREEN_H / 3) + 108);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    soundUp.play();
                    std::cout<< "Clique : Setting" <<std::endl;
                }
            }
            else{
                txtSetting.setCharacterSize(24);
                txtSetting.setFillColor(Color::White);
                txtSetting.setPosition((SCREEN_W/2) - 35, (SCREEN_H / 3) + 108);
            }

            if(txtExit.getGlobalBounds().contains(MousePos.x, MousePos.y)){
                txtExit.setCharacterSize(32);
                txtExit.setFillColor(Color::Green);
                txtExit.setPosition((SCREEN_W/2) - 22, (SCREEN_H / 3) + 150);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    soundUp.play();
                    std::cout<< "Clique : Exit" <<std::endl;
                    window.close();
                    return 0;
                }
            }
            else{
                txtExit.setCharacterSize(28);
                txtExit.setFillColor(Color::White);
                txtExit.setPosition((SCREEN_W/2) - 12, (SCREEN_H / 3) + 150);
            }
        }
        window.clear(Color::Black);

        window.draw(sprBg);
        window.draw(sprCadre);
        window.draw(sprMenu);
        window.draw(txtTitle);
        window.draw(txtPlay);
        window.draw(txtSetting);
        window.draw(txtExit);
        window.display();
    }
    return 0;
}
