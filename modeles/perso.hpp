//
// Created by infini on 15/07/22.
//

#ifndef RPG_PERSO_HPP
#define RPG_PERSO_HPP

#include <random>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../utils/consts.hpp"
#include "../utils/tilemap.hpp"

using namespace sf;

class Perso {
public:
    Perso(): anim(0, Down) {

        if(!texture.loadFromFile("./assets/sprites/actors/actor1.png")){
            perror("'texture' load error");
        }
        texture.setSmooth(true);

        sprite.setTexture(texture);
        sprite.setPosition(150,150);
    }

    void move(Event& event, TileMap& map){
        if(event.type == Event::KeyPressed) updateAnim = true;
        else updateAnim = false;

        if(Keyboard::isKeyPressed(Keyboard::Down)  || Keyboard::isKeyPressed(Keyboard::S)){
            if(!map.isTileWall(sprite.getPosition(), Down, PERSO_WIDTH, PERSO_HEIGHT, speed)){
                sprite.move(0, speed);
            }
            anim.y = Down;
        }else if(Keyboard::isKeyPressed(Keyboard::Left)  || Keyboard::isKeyPressed(Keyboard::Q)){
            if(!map.isTileWall(sprite.getPosition(), Left, PERSO_WIDTH, PERSO_HEIGHT, speed)){
                sprite.move(-speed, 0);
            }
            anim.y = Left;
        }else if(Keyboard::isKeyPressed(Keyboard::Right)  || Keyboard::isKeyPressed(Keyboard::D)){
            if(!map.isTileWall(sprite.getPosition(), Right, PERSO_WIDTH, PERSO_HEIGHT, speed)){
                sprite.move(speed, 0);
            }
            anim.y = Right;
        }else if(Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Z)){
            if(!map.isTileWall(sprite.getPosition(), Up, PERSO_WIDTH, PERSO_HEIGHT, speed)){
                sprite.move(0, -speed);
            }
            anim.y = Up;
        }

        if(updateAnim){
            if(m_time.getElapsedTime().asMilliseconds() >= 100){
                anim.x++;
                if(anim.x * PERSO_WIDTH >= texture.getSize().x)
                    anim.x = 0;
                m_time.restart();
            }
        }
        sprite.setTextureRect(IntRect(anim.x * PERSO_WIDTH, anim.y * PERSO_HEIGHT, PERSO_WIDTH , PERSO_HEIGHT));
    }

    void i_move(TileMap& map){
        //bool moving = true;

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> gen(0, 3);

        if(m_i_time.getElapsedTime().asMilliseconds() >= 100){
            if(anim.y == Down)
            {
                updateAnim = true;
                if(!map.isTileWall(sprite.getPosition(), Down, PERSO_WIDTH, PERSO_HEIGHT, speed)){
                    sprite.move(0, speed);
                } else{
                    updateAnim = false;
                    anim.y = gen(rng);
                }

            }
            else if(anim.y == Left){
                updateAnim = true;
                if(!map.isTileWall(sprite.getPosition(), Left, PERSO_WIDTH, PERSO_HEIGHT, speed)){
                    sprite.move(-speed, 0);
                }else{
                    updateAnim = false;
                    anim.y = gen(rng);
                }
            }
            else if(anim.y == Right)
            {
                updateAnim = true;
                if(!map.isTileWall(sprite.getPosition(), Right, PERSO_WIDTH, PERSO_HEIGHT, speed)){
                    sprite.move(speed, 0);
                }else{
                    updateAnim = false;
                    anim.y = gen(rng);
                }
            }
            else if(anim.y == Up){
                updateAnim = true;
                if(!map.isTileWall(sprite.getPosition(), Up, PERSO_WIDTH, PERSO_HEIGHT, speed)){
                    sprite.move(0, -speed);
                }else{
                    updateAnim = false;
                    anim.y = gen(rng);
                }
            }

            if(updateAnim){
                if(m_time.getElapsedTime().asMilliseconds() >= 30){
                    anim.x++;
                    if(anim.x * PERSO_WIDTH >= texture.getSize().x)
                        anim.x = 0;
                    m_time.restart();
                }
            }
            m_i_time.restart();
        }


        sprite.setTextureRect(IntRect(anim.x * PERSO_WIDTH, anim.y * PERSO_HEIGHT, PERSO_WIDTH , PERSO_HEIGHT));
    }

    Sprite sprite;
private:

    Clock m_time;
    Clock m_i_time;
    float speed = 5;
    enum Dir{Down, Left, Right, Up};
    Vector2i anim;
    bool updateAnim = true;
    
    Texture texture;
};


#endif //RPG_PERSO_HPP
