//
// Created by infini on 20/07/22.
//

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Battle.h"
#include "../utils/distribution.h"


using namespace std;
using namespace sf;

int Battle::battle(RenderWindow& window, Personnage& principale, Personnage* secondaire, int index){
    cout<< "Index == >  " << index <<endl;
    int issue = 0;
    int outilIndex = 0;

    int main = Gen::distNumber(0, 1);
    Vector2f position;
    RectangleShape tourIndic(Vector2f(136 , 179));
    tourIndic.setFillColor(Color::Red);

    RectangleShape rectangle(sf::Vector2f(210.f, 100.f));
    rectangle.setFillColor(Color::Black);
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(Color::White);
    rectangle.setPosition(380, 15);

    Font font;
    if(!font.loadFromFile("./assets/fonts/console/Inconsolata-Regular.ttf")){
        perror("'Inconsolata' load error");
    }
    Text text;
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setCharacterSize(12);
    text.setString(L"\t\t===  Log  ===\n> Enémie -> Coup d'épée 50");
    text.setPosition(384, 18);

    secondaire->sprite_face.setPosition(15, 15);
    secondaire->sprite_face.setScale(0.4, 0.5);
    principale.sprite_face.setPosition(450, 210);
    principale.sprite_face.setScale(0.4, 0.5);

    secondaire->text_vie.setString(L"Vie : ");
    secondaire->text_vie.setCharacterSize(20);
    secondaire->text_vie.setPosition(170, 40);

    secondaire->text_habilite.setString(L"Habilité : ");
    secondaire->text_habilite.setCharacterSize(20);
    secondaire->text_habilite.setPosition(170, 90);

    secondaire->text_arme.setString(L"Arme : ");
    secondaire->text_arme.setCharacterSize(20);
    secondaire->text_arme.setPosition(170, 140);

    principale.text_vie.setString(L"Vie : ");
    principale.text_vie.setCharacterSize(20);
    principale.text_vie.setPosition(300, 240);

    principale.text_habilite.setString(L"Habilité : ");
    principale.text_habilite.setCharacterSize(20);
    principale.text_habilite.setPosition(300, 290);

    principale.text_arme.setString(L"Arme : ");
    principale.text_arme.setCharacterSize(20);
    principale.text_arme.setPosition(300, 340);

    for(int i = 0; i < principale.getSac()->getOutils().size(); i++){
        principale.getSac()
            ->getOutils()[i]
            ->setPosition(20 + (i * 36), 240);
    }
    cout<< " == > 1" <<endl;
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

            if(Keyboard::isKeyPressed(Keyboard::Escape)){
                return issue;
            }

            for (int i = 0; i < principale.getSac()->getOutils().size(); ++i) {
                if(i != outilIndex)
                    principale.getSac()
                            ->getOutils()[i]->setRectColor(Color::White);
                if(principale.getSac()->getOutils()[i]->onMouseEnter(window)){
                    principale.getSac()
                            ->getOutils()[i]->setRectColor(Color::Red);
                    outilIndex = i;
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        principale.setOutil(outilIndex);
                    }
                }

                if(Keyboard::isKeyPressed(Keyboard::A) && main == 1){
                    principale.attack(secondaire);
                    main = 0;
                }
            }
        }

        if(main == 0){
            position.x = 13;
            position.y = 13;
        }else if(main == 1){
            position.x = 448;
            position.y = 208;
        }

        tourIndic.setPosition(position);

        principale.updateInfo();
        secondaire->updateInfo();

        window.clear(Color::Black);

        window.draw(tourIndic);

        window.draw(secondaire->sprite_face);
        window.draw(secondaire->text_vie);
        window.draw(secondaire->text_habilite);
        window.draw(secondaire->text_arme);
        window.draw(rectangle);
        window.draw(text);

        window.draw(principale.sprite_face);
        window.draw(principale.text_vie);
        window.draw(principale.text_habilite);
        window.draw(principale.text_arme);

        for(int i = 0; i < principale.getSac()->getOutils().size(); i++){
            window.draw(principale.getSac()->getOutils()[i]->rectangle);
            window.draw(principale.getSac()->getOutils()[i]->spriteMini);
        }

        window.display();
    }
}