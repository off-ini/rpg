//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_PORTE_H
#define RPG_PORTE_H

#include "GameObject.h"

class Porte : public GameObject {
private:
    int position;//quatre positions possibles nord(0) sud(1) est(2) ouest(3)

public:
    Porte();

    Porte(int position);

    int getPosition();

    void setPosition(int);
};


#endif //RPG_PORTE_H
