//
// Created by benjamin on 18/07/22.
//

#ifndef RPG_PARSER_H
#define RPG_PARSER_H

#include "../modeles/Personnage.h"
#include "../modeles/Druide.h"
#include "../modeles/Ouvrier.h"
#include "../modeles/Soldat.h"
#include "../modeles/Religieux.h"
#include "../modeles/Arme.h"
#include "../modeles/Amulette.h"
#include "../modeles/Potion.h"
#include "../dependances/rapidjson/document.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <typeinfo>

#define FILENAME "../data/level.save"

using namespace std;

class Parser {
public:
    static void test() {
        Personnage *joueur = new Druide("Benjamin", 5, 50);
        joueur->getSac()->addOutil(new Arme("Epée Glamdring", 50, 5));
        joueur->getSac()->addOutil(new Amulette("Baton du magicien", 5, 10));

        Personnage *adversaire = new Ouvrier("Saroumane", 5, 60);
        adversaire->getSac()->addOutil(new Arme("Epée Glamdring", 50, 5));
        adversaire->getSac()->addOutil(new Amulette("Baton du magicien", 5, 10));

        vector<Personnage *> personnages;/* = {joueur, adversaire};*/

        //operation
        //save(personnages);
        //personnages = load();
        /*for (auto personnage: personnages) {
            personnage->print();
        }*/
    }

    static void save(vector<Personnage *> personnages) {
        string json = "{\"personnages\": [";

        //Ouverture du fichier en ecriture
        ofstream fichier;
        fichier.open(FILENAME, ios::trunc | ios::out);
        if (fichier) {
            for (int i = 0; i < personnages.size(); i++) {
                json += personnages[i]->toJson();
                if (i != (personnages.size() - 1)) {
                    json += ", ";
                }
            }
            json += "]}";
            //Ecriture du json
            fichier << json;

            //Fermerture du fichier
            fichier.close();
        }
    }

    static vector<Personnage *> load() {
        string ligne = "";
        string json = "";
        vector<Personnage *> vectorPersonnages;

        //Ouverture du fichier en lecture et lecture du contenu
        ifstream fichier;
        fichier.open(FILENAME, ios::in);
        if (fichier) {
            while (!fichier.eof()) {
                fichier >> ligne;
                json += ligne;
            }
        }

        //Parse a JSON string into DOM.
        rapidjson::Document document;
        const char *chaine = json.c_str();
        document.Parse(chaine);

        //Parcours des personnages du DOM
        const rapidjson::Value &personnages = document["personnages"];
        assert(personnages.IsArray());
        for (rapidjson::SizeType i = 0; i < personnages.Size(); i++) {

            //Récupération des informations atomiques du personnages du DOM
            Personnage *personnage;
            string type_personnage = personnages[i]["type"].GetString();
            string nom = personnages[i]["nom"].GetString();
            int niveauSante = personnages[i]["niveauSante"].GetInt();
            int niveauHabilete = personnages[i]["niveauHabilete"].GetInt();

            //Création du personnage approprié
            if (type_personnage.find("Druide") != std::string::npos) {
                personnage = new Druide(nom, niveauSante, niveauHabilete);
            } else if (type_personnage.find("Soldat") != std::string::npos) {
                personnage = new Soldat(nom, niveauSante, niveauHabilete);
            } else if (type_personnage.find("Religieux") != std::string::npos) {
                personnage = new Religieux(nom, niveauSante, niveauHabilete);
            } else if (type_personnage.find("Ouvrier") != std::string::npos) {
                personnage = new Ouvrier(nom, niveauSante, niveauHabilete);
            }

            //Récupération des outils du sac
            for (auto &o: personnages[i]["sac"].GetArray()) {
                string type_outil = o["type"].GetString();
                string libelle = o["libelle"].GetString();
                Outil *outil;

                if (type_outil.find("Arme") != std::string::npos) {
                    outil = new Arme(libelle, o["point"].GetInt(), o["niveau"].GetInt());
                } else if (type_outil.find("Amulette") != std::string::npos) {
                    outil = new Amulette(libelle, o["portee"].GetInt(), o["puissance"].GetInt());
                } else if (type_outil.find("Potion") != std::string::npos) {
                    outil = new Potion(libelle, o["point"].GetInt());
                }

                personnage->getSac()->addOutil(outil);
            }

            //Vérification de la création du personnage
            vectorPersonnages.push_back(personnage);
        }
        return vectorPersonnages;
    }
};


#endif //RPG_PARSER_H
