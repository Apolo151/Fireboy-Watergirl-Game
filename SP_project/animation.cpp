#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
    int row1_B = 10, row2_B = 20, StopRow_B = 10;
    double jumpV_B = 0; bool isgrounded_B = false;

    int row1_G = 22, row2_G = 5, StopRow_G = 20;
    double jumpV_G = 0; bool isgrounded_G = false;
    

    // for making window

    RenderWindow window(VideoMode(1500, 1000), "fireboy & watergirl");

    // frame per second 

    window.setFramerateLimit(15);

    // for making rectangle for jumping on it

   RectangleShape rect(Vector2f(1500 , 50));
   rect.setPosition(0, 700);

    // for charachter fireboy

    Texture load_photo1;
    load_photo1.loadFromFile("sprites/FIREBOY SPRITE.PNG");
    Sprite fireboy;
    fireboy.setTexture(load_photo1);
    fireboy.setTextureRect(IntRect(467,277 , 55, 100));
    fireboy.setPosition(700, 500);
    fireboy.scale(1, 1);

    // for charachter watergirl

    Texture load_photo2;
    load_photo2.loadFromFile("sprites/WATERGIRL SPRITE.PNG");
    Sprite watergirl;
    watergirl.setTexture(load_photo2);
    watergirl.setTextureRect(IntRect(340, 472, 56, 86));
    watergirl.setPosition(350, 100);
    watergirl.scale(1, 1);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // fireboy controls :

        if (Keyboard::isKeyPressed(Keyboard::Key::Right)) 
        {
           fireboy.move(10, 0);
           fireboy.setTextureRect(IntRect(row1_B, -22 , 70, 100));
            row1_B += 80;
           row1_B %= 320;
        }
           

        else if (Keyboard::isKeyPressed(Keyboard::Key::Left)) 
        {
          fireboy.move(-10, 0);
          fireboy.setTextureRect(IntRect(row2_B, 78, 70, 100));
          row2_B +=80;
          row2_B %= 320;
        }

        else
        {
            fireboy.setTextureRect(IntRect(StopRow_B, 400, 55, 100));
            StopRow_B += 80;
            StopRow_B %= 400;
        }
       
        // wategirl controls :

        if (Keyboard::isKeyPressed(Keyboard::Key::A))
        {
            watergirl.move(-10, 0);
            watergirl.setTextureRect(IntRect(row1_G, 18, 90, 80));
            row1_G += 100;
            row1_G %= 400;
        }

        else if (Keyboard::isKeyPressed(Keyboard::Key::D))
             {
               watergirl.move(10, 0);
               watergirl.setTextureRect(IntRect(row2_G, 118, 96, 80));
               row2_G += 100;
               row2_G %= 400;
             }
        else
        {
              watergirl.setTextureRect(IntRect(StopRow_G, 472, 56, 86));
              StopRow_G += 80;
              StopRow_G %= 320;
        }

        // fire boy jumping code
       
        if (rect.getGlobalBounds().intersects(fireboy.getGlobalBounds()))
        {
            isgrounded_B = true;
            jumpV_B = 0;

            if (Keyboard::isKeyPressed(Keyboard::Key::Up))
            {
                jumpV_B = 20;
            }
        }
        else
        {
            isgrounded_B = false;
            jumpV_B -= 1.5;
        }

        // water girl jumping code 

        if (rect.getGlobalBounds().intersects(watergirl.getGlobalBounds()))
        {
            isgrounded_G = true;
            jumpV_G = 0;

            if (Keyboard::isKeyPressed(Keyboard::Key::W))
            {
                jumpV_G = 20;
            }
        }
        else
        {
            isgrounded_G = false;
            jumpV_G -= 1.5;
        }

        //for execute

        window.clear();
        window.draw(rect);
        window.draw(fireboy);
        window.draw(watergirl);
        fireboy.move(0, -jumpV_B);
        watergirl.move(0, -jumpV_G);
        window.display();

    }

    return 0;
}



