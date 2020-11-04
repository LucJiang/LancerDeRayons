#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>

#include "object.hpp"


int main()
{


    Point campos(0,0,0);
    Point camori(0,1,0);
    Camera cam(campos, camori, 0, 1);

    Point objpos(0,200,0);
    Sphere obj(objpos, 100, 255, 0, 0);

    std::vector<Sphere> spheres;
    spheres.push_back(obj);

    Point litpos(0,150,400);
    Light lit(litpos);
    std::vector<Light> lights;
    lights.push_back(lit);

    sf::Uint8* pixels = new sf::Uint8[width*height*4];

    World world(cam, spheres, lights, pixels);
    /*
    float t = -1;
    int idobj = -1;
    std::cout << world.ray(campos, camori, &t, &idobj) << std::endl;
    */
    world.raytracing();

    //std::cout << t << ", " << idobj << std::endl;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::Image image;
    texture.loadFromFile("Thunw_griffon.png");
    //image.create(width, height, world.getpixels());

    //texture.update(pixels);

    std::cout << "done" << std::endl;
    std::cout << 'A' << std::endl;
    std::cout << pixels[width*height*4-1] << std::endl;

    sf::RenderWindow window(sf::VideoMode(width, height), "My test window");
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //texture.update(image);
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();

    }

    return 0;
}

