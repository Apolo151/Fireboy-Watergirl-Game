#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
bool z = false;
int main()
{
    RenderWindow window(sf::VideoMode(1000, 700), "Fireboy & Watergirl");
    int x=0,y=0;
    Sprite fireboy,rope,firelake;
    Texture tx,tx1,tx2;
    //fireboy:
    tx.loadFromFile("fire3.png");
    fireboy.setTexture(tx);
    fireboy.setPosition(350, 350);
    fireboy.setScale(1, 1);
    
    //rope:
    tx1.loadFromFile("rope.png");
    rope.setTexture(tx1);
    rope.setPosition(750, 340);
    rope.setScale(0.25, 0.25);
    //firelake:
    tx2.loadFromFile("flake.png");
    firelake.setTexture(tx2);
    firelake.setPosition(550, 350);
    firelake.setScale(0.7, 0.7);

    //for water

    Sprite watergirl, wire, waterlake;
    Texture t, t1, t2;
    //watergirl
    t.loadFromFile("water.png");
    watergirl.setTexture(t);
    watergirl.setPosition(350, 550);
    watergirl.setScale(0.15, 0.15);
    //wirewire.png"
    t1.loadFromFile("wire.png");
    wire.setTexture(t1);
    wire.setPosition(550, 550);
    wire.setScale(0.4, 0.4);
    //waterlake
    t2.loadFromFile("wlake.png");
    waterlake.setTexture(t2);
    waterlake.setPosition(750, 620);
    waterlake.setScale(0.6, 0.6);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Right))
        {
            fireboy.move(0.2, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        {
          
            fireboy.move(-0.2, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Up))
        {
            fireboy.move(0, -0.2);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Down))
        {
            fireboy.move(0, 0.2);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D))
        {
            watergirl.move(0.2, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A))
        {
            watergirl.move(-0.2, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W))
        {
            watergirl.move(0, -0.2);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S))
        {
            watergirl.move(0, 0.2);
        }
        if (fireboy.getGlobalBounds().intersects(waterlake.getGlobalBounds()))
        {
            fireboy.setScale(0, 0);
        }
        if (watergirl.getGlobalBounds().intersects(firelake.getGlobalBounds()))
        {
            watergirl.setScale(0, 0);
        }
        if (fireboy.getGlobalBounds().intersects(rope.getGlobalBounds()))
        {
            z = true;
        }
        if (watergirl.getGlobalBounds().intersects(rope.getGlobalBounds()) && z)
        {
            watergirl.setScale(0, 0);
        }

        window.clear();
        window.draw(fireboy);
        window.draw(firelake);
        window.draw(wire);
        window.draw(watergirl);
        window.draw(waterlake);
        window.draw(rope);
       
        window.display();
    }

    return 0;
}