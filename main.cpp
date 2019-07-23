#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Maze.h"
//#include <SFML/View.hpp>
//#include <SFML/Sprite.hpp>

using namespace std;

const int kafel=32;
const int krok=1;
const int rozmiar=5;

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, Maze &labirynt)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        int width = labirynt.getWidth();
        int height = labirynt.getHeight();

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = labirynt.field(i,j);

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

//=======================================================================================================================

void druk_lab()
{   /* czas*/srand(time(NULL));
    /* tablica labiryntu*/ int tab[100][100];
    /* ilosc komnat*/ int ilk=rand()%10+9;
    /* wymiary komnaty*/int x=0; int y=0;
    /* lewygorny rog komnaty*/ int lgrx=0; int lgry=0;const int kafel=32;
    int licz=1;
    /* wype³nianie scianami*/for(int i=0;i<30;i++){
        for(int o=0;o<30;o++){
        tab[i][o]=0;
    }
    }
    /* tworzenie komnat*/
    int j=0;
    while(j<ilk){
        lgrx=rand()%23+1; lgry=rand()%23+1; x=rand()%4+3; y=rand()%4+3;
            for(int i=-1;i<=y && licz;i++){
                for(int o=-1;o<=x;o++){

                if(tab[lgrx+i][lgry+o]==1){
                    cout<<"k";
                    licz=0;
                    break;
                }

    }
            }
            if(licz==0){
                licz=1;
                continue;
            }
            for(int i=0;i<y;i++){
        for(int o=0;o<x;o++){
        tab[lgrx+i][lgry+o]=1;
        }}

    j++;
    cout<<j;

    }
    cout<<endl;
    /* drukowanie*/for(int i=0;i<30;i++){
        for(int o=0;o<30;o++){
        cout<<tab[i][o];
    }
    cout<<endl;
    }

}

//===========================================================================

int main()
{

     //--------------------------------
    // Okno powitalne
    //--------------------------------

    sf::RenderWindow powitalne(sf::VideoMode::getDesktopMode(),"aMAZEing BOXer", sf::Style::Fullscreen);

    sf::RectangleShape start(sf::Vector2f(120, 50));

    sf::Texture powit;
//    if (!start.loadFromFile("start.png"));

//    start.setTexture(powit)

    while (powitalne.isOpen()) {
        sf::Event event;

        while (powitalne.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                powitalne.close();
        }


//        window.draw(start);
    }

    int w = 58;
    int h = 30;




    // create the window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "aMAZEing BOXer");


    Maze labirynt(w,h);
    labirynt.generate();

    int ex = labirynt.getEndX();
    int ey = labirynt.getEndY();

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("MAPA.png", sf::Vector2u(32, 32),labirynt))
        return -1;

    int nrTextury = 0;

    sf::Texture texture[3];
    texture[0].loadFromFile("bokser1.png");
    texture[1].loadFromFile("bokser2.png");
    texture[2].loadFromFile("bokser3.png");


    sf::Sprite shape;
    shape.setTexture(texture[nrTextury]);
    shape.setScale(0.5,0.5);
    shape.setPosition((1*48-rozmiar),(1*48-rozmiar));

    shape.setOrigin(48,48);

    while (window.isOpen())
    {
        // handle events
        sf::Event event;

        while (window.pollEvent(event))
        {

            sf::Vector2f pozycja=shape.getPosition();
            pozycja.x+=rozmiar;
            pozycja.y+=rozmiar;

            int x = int (pozycja.x)/kafel;
            int y = int(pozycja.y)/kafel;
            int delta_x = int(pozycja.x)%kafel;
            int delta_y = int(pozycja.y)%kafel;


            if(x==ex && y==ey)
                window.close();


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
               // shape.setRotation(0);
                shape.move(0.0,-krok);
                nrTextury = (nrTextury+1)%3;
                shape.setTexture(texture[nrTextury]);

            if ((labirynt.field(x,y-1)!=2) &&(labirynt.field(x,y-1))!=1&&(delta_y<rozmiar))  shape.move(0,krok);
 }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
               // shape.setRotation(270);
                shape.move(-krok,0.0);
                nrTextury = (nrTextury+1)%3;
                shape.setTexture(texture[nrTextury]);

              if ((labirynt.field(x-1,y)!=2) && (labirynt.field(x-1,y)!=1)&&(delta_x<rozmiar))  shape.move(krok,0.0);
}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
               // shape.setRotation(180);
                shape.move(0.0,krok);
                nrTextury = (nrTextury+1)%3;
                shape.setTexture(texture[nrTextury]);

          if ((labirynt.field(x,y+1)!=2) &&(labirynt.field(x,y+1)!=1)&&((kafel-delta_y)<rozmiar))  shape.move(0,-krok);
}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            //    shape.setRotation(90);
                shape.move(krok,0.0);
                nrTextury = (nrTextury+1)%3;
                shape.setTexture(texture[nrTextury]);

            if ((labirynt.field(x+1,y)!=2) &&(labirynt.field(x+1,y)!=1)&&((kafel-delta_x)<rozmiar))  shape.move(-krok,0.0);
}

        if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(map);
        window.draw(shape);
        window.display();
    }


    //--------------------------------
    // Okno koncowe
    //--------------------------------

    sf::RenderWindow koncowe(sf::VideoMode::getDesktopMode(),"aMAZEing BOXer", sf::Style::Titlebar);

    while (koncowe.isOpen()) {
        sf::Event event;

        while (koncowe.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                koncowe.close();
        }

    }

    return 0;
}
