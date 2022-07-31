//
// Created by benjamin on 02/07/22.
//

#include "Soldat.h"
#include "../utils/distribution.h"
#include "Bouclier.h"
#include "Epee.h"
#include "Hache.h"
#include "PotionRegeneration.h"

Soldat::Soldat(): Personnage("Solda", Gen::distNumber(50, 90), Gen::distNumber(2, 5)) {
    int number = Gen::distNumber(1, 2);
    load(number);
    getSac()->addOutil(new Bouclier);
    getSac()->addOutil(new Epee);
    getSac()->addOutil(new Hache);
    getSac()->addOutil(new PotionRegeneration(15));
}

Soldat::Soldat(string nom, int niveauSante, int niveauHabilite) : Personnage(nom, niveauSante, niveauHabilite) {}

void Soldat::print(void) {
    string ecran = "Soldat[nom: " + this->nom + ", niveauSante:  " + to_string(this->niveauSante)
                   + ", niveauHabilete:  " + to_string(this->niveauHabilite) + ", ";
    cout << endl << ecran;
    this->sac->print();
    cout << "]" << endl;
}

string Soldat::toJson() {
    string type = &(typeid(*this).name()[1]);
    string json;
    json = "{\"type\": \"" + type + "\", \"nom\": \"" + this->nom + "\", \"niveauSante\": " +
           to_string(this->niveauSante)
           + ", \"niveauHabilete\": " + to_string(this->niveauHabilite) + ", \"sac\": [";
    json += this->sac->toJson();
    json += "]}";
    return json;
}