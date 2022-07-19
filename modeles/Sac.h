//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_SAC_H
#define RPG_SAC_H

#include <vector>
#include <algorithm>
#include "GameObject.h"
#include "Outil.h"

using namespace std;

class Sac : public GameObject {

private:
    vector<Outil *> outils;//outils.size() pour avoir nbreOutils

public:
    Sac();

    Sac(vector<Outil *> outils);

    Sac(const Sac &sac);

    vector<Outil *> getOutils();

    void setOutils(vector<Outil *> outils);

    void addOutil(Outil *outil);

    Sac &operator=(const Sac &sac);

    ~Sac();

    void print();

    string toJson();
};


#endif //RPG_SAC_H
