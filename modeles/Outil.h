//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_OUTIL_H
#define RPG_OUTIL_H

#include "GameObject.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Outil : public GameObject {

protected:
    string libelle;

    Texture textureMini;

public:
    Outil();

    Outil(string libelle);

    string getLibelle();

    void setLibelle(string libelle);

    void load(int x, int y);
    void setPosition(float x, float y);
    bool onMouseEnter(RenderWindow& window);
    void setRectColor(Color color);

    virtual  int getPoint() = 0;

    virtual void setPoint(int point) = 0;

    virtual int getNiveau() = 0;

    virtual void setNiveau(int niveau) = 0;

    /*virtual int getPortee() = 0;

    virtual void setPortee(int portee) = 0;

    virtual int getPuissance() = 0;

    virtual void setPuissance(int puissance) = 0;*/

    virtual void print();

    virtual string toJson();

    RectangleShape rectangle;
    Sprite spriteMini;
};


#endif //RPG_OUTIL_H