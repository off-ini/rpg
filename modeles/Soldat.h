//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_SOLDAT_H
#define RPG_SOLDAT_H

#include "Personnage.h"

using namespace std;

class Soldat : public Personnage {
public:
    Soldat();

    Soldat(string nom, int niveauSante, int niveauHabilite);

    void print(void);
};


#endif //RPG_SOLDAT_H
