//
// Created by infini on 13/07/22.
//

#ifndef RPG_TILEMAP_H
#define RPG_TILEMAP_H
#include <SFML/Graphics.hpp>

#include "consts.hpp"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap(const std::string& tileset, const int* tiles)
    {
        m_tileset_name = tileset;
        m_tiles = tiles;

        m_tileSize.x = TILE_SIZE_X;
        m_tileSize.y = TILE_SIZE_Y;
        m_width = TILE_WIDTH;
        m_height = TILE_HEIGHT;
    }

    TileMap(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        m_tileset_name = tileset;
        m_tileSize = tileSize;
        m_tiles = tiles;
        m_width = width;
        m_height = height;
    }

    bool load()
    {
        // on charge la texture du tileset
        if (!m_tileset.loadFromFile(m_tileset_name))
            return false;

        // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(m_width * m_height * 4);

        // on remplit le tableau de vertex, avec un quad par tuile
        for (unsigned int i = 0; i < m_width; ++i)
            for (unsigned int j = 0; j < m_height; ++j)
            {
                // on récupère le numéro de tuile courant
                int tileNumber = m_tiles[i + j * m_width];

                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (m_tileset.getSize().x / m_tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / m_tileSize.x);

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &m_vertices[(i + j * m_width) * 4];

                // on définit ses quatre coins
                quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
                quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);

                // on définit ses quatre coordonnées de texture
                quad[0].texCoords = sf::Vector2f(tu * m_tileSize.x, tv * m_tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
            }

        return true;
    }
    bool isTileWall(const sf::Vector2f& posChar,const int& dir, const int& width, const int& height, const int& speed)
    {
        int middle_x = width / 2;
        int middle_y = height / 2;

        for(int i = 0; i < 3; i++){
            // Je récupère la position de mon personnage
            sf::Vector2f destination(posChar.x , posChar.y);

            // Je modifie ses coordonnées selon la destination du personnage pour récupérer la destination
            switch (dir)
            {    case 0 :
                    //Vers le bas , j'augmente Y de 32 (une tile fait 32x32)
                    destination.x += (i * middle_x);
                    destination.y += height + speed;
                    break;

                case 1 :
                    //Vers la gauche, je diminue X de 1 (la vitesse de deplacement)
                    destination.y += (i * middle_y);
                    destination.x -= speed;
                    break;

                case 2 :
                    //Vers la droite, j'augmente X de 32
                    destination.y += (i * middle_x);
                    destination.x += width + speed;
                    break;

                case 3 :
                    //Vers le haut, je diminue Y de 1
                    destination.x += (i * middle_x);
                    destination.y -= speed;
                    break;

                default : break;

            }
            //Je recupere les coordonnées du tile qui correspond a la destination
            int tx = destination.x/m_tileSize.x;
            int ty = destination.y/m_tileSize.y;

            //Si je sors de la fenetre, il y a collision
            if(destination.x < 0 || destination.y < 0 || destination.x > m_width*m_tileSize.x || destination.y > m_height*m_tileSize.y)
                return true;

            //Si j'en suis la c'est que je ne suis pas sorti de la fenetre, alors je cherche quel
            //numero dans le tableau correspond a cette tile
            switch(m_tiles[tx + ty*m_width])
            {
                case 0 :
                case 2 :
                case 3 :
                case 4 :
                    //return false;
                    break;
                    // Si le numero est compris entre 0 et 4, c'est un sol
                    // Sinon c'est un mur
                default : return true;
                    break;
            }
        }

        return false;

    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &m_tileset;

        // et on dessine enfin le tableau de vertex
        target.draw(m_vertices, states);
    }

    std::string m_tileset_name;
    sf::Vector2u m_tileSize;
    const int* m_tiles;
    unsigned int m_width;
    unsigned int m_height;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif //RPG_TILEMAP_H
