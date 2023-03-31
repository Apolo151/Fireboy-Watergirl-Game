#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1200, 800), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        
        if(Keyboard::isKeyPressed(Keyboard::Key::A)){
            cout << "LOL";
        }
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}