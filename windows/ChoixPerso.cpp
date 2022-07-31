//
// Created by infini on 19/07/22.
//

#include <iostream>
#include <vector>
#include "ChoixPerso.h"

using namespace std;
using namespace sf;

std::string getType(int i){
    if(i <= 2) return "Soldat";
    else if(i <= 4) return "Druide";
    else if(i <= 6) return "Ouvrier";
    else if(i <= 8) return "Religieux";
}

void PersoSelect::load(int i){
    if(!textureFace.loadFromFile("./assets/sprites/actors/a_"+ to_string(i) +".png")){
        perror("Load erreur");
    }

    type = getType(i);
    textureFace.setSmooth(true);
    spriteFace.setTexture(textureFace);
    spriteFace.setScale(Vector2f(0.7f, 0.8f));
    spriteFace.setPosition(280, 60);

    int posX = i > 4 ? i - 5 : i - 1;
    int posY = i > 4 ? 1 :  0;

    if(!textureMini.loadFromFile("./assets/sprites/actors/faces.png", IntRect((posX * 144), (posY * 144),  144, 144))){
        perror("Load erreur");
    }
    textureMini.setSmooth(true);
    spriteMini.setTexture(textureMini);
    spriteMini.setScale(Vector2f(0.45f, 0.45f));

    rectangle.setSize(Vector2f(75, 75));
    rectangle.setFillColor(Color::White);

    rectangle.setPosition(0,0);
    spriteMini.setPosition(3,3);
}

void PersoSelect::setPosition(float x, float y){
    rectangle.setPosition(x, y);
    spriteMini.setPosition(x+3, y+3);
}

bool PersoSelect::onMouseEnter(RenderWindow& window){
    Vector2i mousePosition = sf::Mouse::getPosition(window);

    FloatRect boundingBox = rectangle.getGlobalBounds();

    Vector2f point(mousePosition.x, mousePosition.y);
    if (boundingBox.contains(point))
        return true;
    else return false;
}

int ChoixPerso::choix(RenderWindow& window){
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

    Text txtTitle;
    Text txtType;

    txtTitle.setFont(fonTeko);
    txtTitle.setString(L"Selectionnez un personnage");
    txtTitle.setCharacterSize(64);
    txtTitle.setFillColor(Color::Yellow);
    txtTitle.setPosition(50, -15);

    txtType.setFont(fonSkranji);
    txtType.setString(L"Type");
    txtType.setCharacterSize(28);
    txtType.setFillColor(Color::Yellow);
    txtType.setPosition(350, 340);

    Texture textureback;
    if(!textureback.loadFromFile("./assets/sprites/bgChoix.png")){
        perror("Load erreur");
    }
    Sprite spriteBack;
    spriteBack.setTexture(textureback);

    vector<PersoSelect *> list;
    PersoSelect* select = NULL;
    int index = 0;

    for (int i = 1; i <= 8; ++i) {
        select = new PersoSelect();
        select->load(i);
        int y = i > 4 ? i - 5 : i - 1;
        int x = i > 4 ? 2 :  1;
        select->setPosition((x * 75), (y * 75) + 80);
        list.push_back(select);
    }

    list[index]->rectangle.setFillColor(Color::Red);

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
            }
            for (int i = 0; i < 8; ++i) {
                if(i != index)
                    list[i]->rectangle.setFillColor(Color::White);
                if(list[i]->onMouseEnter(window)){
                    list[i]->rectangle.setFillColor(Color::Red);
                    index = i;
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        return i+1;
                    }
                }
            }
        }

        txtType.setString(list[index]->type);

        window.clear(Color::Black);
        window.draw(spriteBack);
        window.draw(txtTitle);
        for (int i = 0; i < 8; ++i) {
            window.draw(list[i]->rectangle);
            window.draw(list[i]->spriteMini);
        }
        window.draw(list[index]->spriteFace);
        window.draw(txtType);
        window.display();
    }

    return 0;
}