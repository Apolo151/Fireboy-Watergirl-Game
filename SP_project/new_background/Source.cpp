#include <SFML/Graphics.hpp>
#include<iostream>
using namespace sf;
using namespace std;
int main()
{
    RenderWindow window(sf::VideoMode(1280, 900), "Fireboy and watergirl");


    Texture tg;
    tg.loadFromFile("background1.png");
    tg.setRepeated(true);
    
    
    Texture tg2;
    tg2.loadFromFile("background3.png");
    tg2.setRepeated(true);

    Texture tg3;
    tg3.loadFromFile("bground1.png");

    Texture tg4;
    tg4.loadFromFile("bground2.png");

    Texture tbback;
    tbback.loadFromFile("bbackground.png");
    tbback.setRepeated(true);

    Sprite sbback;
    sbback.setTexture(tbback);
    sbback.setTextureRect({ 0, 0,1280, 900 });

    Texture tback;
    tback.loadFromFile("background2.png");
    tback.setRepeated(true);

    Sprite sback;
    sback.setTexture(tback);
    sback.setTextureRect({ 0, 0,1280, 900 });



    sf::VertexArray f1(sf::TriangleStrip, 9);
    f1[0].position = sf::Vector2f(30.f, 605.f);
    f1[1].position = sf::Vector2f(30.f, 630.f);
    f1[2].position = sf::Vector2f(470.f, 605.f);
    f1[3].position = sf::Vector2f(420.f, 630.f);
    f1[4].position = sf::Vector2f(520.f, 680.f);
    f1[5].position = sf::Vector2f(470.f, 705.f);
    f1[6].position = sf::Vector2f(1020.f, 680.f);
    f1[7].position = sf::Vector2f(615.f, 705.f);
    f1[8].position = sf::Vector2f(1045.f, 705.f);

    f1[0].texCoords = sf::Vector2f(30.f, 605.f);
    f1[1].texCoords = sf::Vector2f(30.f, 630.f);
    f1[2].texCoords = sf::Vector2f(470.f, 605.f);
    f1[3].texCoords = sf::Vector2f(420.f, 630.f);
    f1[4].texCoords = sf::Vector2f(520.f, 680.f);
    f1[5].texCoords = sf::Vector2f(470.f, 705.f);
    f1[6].texCoords = sf::Vector2f(1020.f, 680.f);
    f1[7].texCoords = sf::Vector2f(615.f, 705.f);
    f1[8].texCoords = sf::Vector2f(1045.f, 705.f);

    sf::VertexArray f2(sf::TriangleStrip, 8);
    f2[0].position = sf::Vector2f(175.f, 490.f);
    f2[1].position = sf::Vector2f(175.f, 520.f);
    f2[2].position = sf::Vector2f(580.f, 490.f);
    f2[3].position = sf::Vector2f(530.f, 520.f);
    f2[4].position = sf::Vector2f(600.f, 520.f);
    f2[5].position = sf::Vector2f(550.f, 550.f);
    f2[6].position = sf::Vector2f(1280.f, 520.f);
    f2[7].position = sf::Vector2f(1280.f, 550.f);

    f2[0].texCoords = sf::Vector2f(175.f, 490.f);
    f2[1].texCoords = sf::Vector2f(175.f, 520.f);
    f2[2].texCoords = sf::Vector2f(580.f, 490.f);
    f2[3].texCoords = sf::Vector2f(530.f, 520.f);
    f2[4].texCoords = sf::Vector2f(600.f, 520.f);
    f2[5].texCoords = sf::Vector2f(550.f, 550.f);
    f2[6].texCoords = sf::Vector2f(1280.f, 520.f);
    f2[7].texCoords = sf::Vector2f(1280.f, 550.f);

 
    sf::VertexArray f3(sf::TriangleStrip, 4);
    f3[0].position = sf::Vector2f(29.f, 225.f);
    f3[1].position = sf::Vector2f(29.f, 380.f);
    f3[2].position = sf::Vector2f(160.f, 225.f);
    f3[3].position = sf::Vector2f(160.f, 380.f);

    f3[0].texCoords = sf::Vector2f(29.f, 225.f);
    f3[1].texCoords = sf::Vector2f(29.f, 380.f);
    f3[2].texCoords = sf::Vector2f(160.f, 225.f);
    f3[3].texCoords = sf::Vector2f(160.f, 380.f);


    sf::RectangleShape f4(sf::Vector2f(845.f, 35.f));
    f4.setPosition(435, 180);
    f4.setTexture(&tg3);

    sf::VertexArray g1(sf::TriangleStrip, 4);
    g1[0].position = sf::Vector2f(0.f, 0.f);
    g1[1].position = sf::Vector2f(0.f, 900.f);
    g1[2].position = sf::Vector2f(30.f, 0.f);
    g1[3].position = sf::Vector2f(30.f, 900.f);

    g1[0].texCoords = sf::Vector2f(0.f, 0.f);
    g1[1].texCoords = sf::Vector2f(0.f, 900.f);
    g1[2].texCoords = sf::Vector2f(30.f, 0.f);
    g1[3].texCoords = sf::Vector2f(30.f, 900.f);

    sf::VertexArray g2(sf::TriangleStrip, 4);
    g2[0].position = sf::Vector2f(0.f, 870.f);
    g2[1].position = sf::Vector2f(0.f, 900.f);
    g2[2].position = sf::Vector2f(1280.f, 870.f);
    g2[3].position = sf::Vector2f(1280.f, 900.f);

    g2[0].texCoords = sf::Vector2f(0.f, 870.f);
    g2[1].texCoords = sf::Vector2f(0.f, 900.f);
    g2[2].texCoords = sf::Vector2f(1280.f, 870.f);
    g2[3].texCoords = sf::Vector2f(1280.f, 900.f);

    sf::VertexArray g3(sf::TriangleStrip, 4);
    g3[0].position = sf::Vector2f(1250.f, 0.f);
    g3[1].position = sf::Vector2f(1250.f, 900.f);
    g3[2].position = sf::Vector2f(1280.f, 0.f);
    g3[3].position = sf::Vector2f(1280.f, 900.f);

    g3[0].texCoords = sf::Vector2f(1250.f, 0.f);
    g3[1].texCoords = sf::Vector2f(1250.f, 900.f);
    g3[2].texCoords = sf::Vector2f(1280.f, 0.f);
    g3[3].texCoords = sf::Vector2f(1280.f, 900.f);

    sf::VertexArray g4(sf::TriangleStrip, 4);
    g4[0].position = sf::Vector2f(0.f, 0.f);
    g4[1].position = sf::Vector2f(0.f, 30.f);
    g4[2].position = sf::Vector2f(1280.f, 0.f);
    g4[3].position = sf::Vector2f(1280.f, 30.f);

    g4[0].texCoords = sf::Vector2f(0.f, 0.f);
    g4[1].texCoords = sf::Vector2f(0.f, 30.f);
    g4[2].texCoords = sf::Vector2f(1280.f, 0.f);
    g4[3].texCoords = sf::Vector2f(1280.f, 30.f);

    sf::VertexArray block1(sf::TriangleStrip, 5);
    block1[0].position = sf::Vector2f(1150.f, 750.f);
    block1[1].position = sf::Vector2f(1115.f, 795.f);
    block1[2].position = sf::Vector2f(1280.f, 750.f);
    block1[3].position = sf::Vector2f(1115.f, 900.f);
    block1[4].position = sf::Vector2f(1280.f, 900.f);

    block1[0].texCoords = sf::Vector2f(1150.f, 750.f);
    block1[1].texCoords = sf::Vector2f(1115.f, 795.f);
    block1[2].texCoords = sf::Vector2f(1280.f, 750.f);
    block1[3].texCoords = sf::Vector2f(1115.f, 900.f);
    block1[4].texCoords = sf::Vector2f(1280.f, 900.f);

    sf::VertexArray block2(sf::TriangleStrip, 4);
    block2[0].position = sf::Vector2f(155.f, 345.f);
    block2[1].position = sf::Vector2f(155.f, 380.f);
    block2[2].position = sf::Vector2f(520.f, 345.f);
    block2[3].position = sf::Vector2f(520.f, 380.f);

    block2[0].texCoords = sf::Vector2f(155.f, 345.f);
    block2[1].texCoords = sf::Vector2f(155.f, 380.f);
    block2[2].texCoords = sf::Vector2f(520.f, 345.f);
    block2[3].texCoords = sf::Vector2f(520.f, 380.f);

    sf::VertexArray block3(sf::TriangleStrip, 8);
    block3[0].position = sf::Vector2f(515.f, 270.f);
    block3[1].position = sf::Vector2f(515.f, 380.f);
    block3[2].position = sf::Vector2f(705.f, 270.f);
    block3[3].position = sf::Vector2f(850.f, 380.f);
    block3[4].position = sf::Vector2f(850.f, 345.f);
    block3[5].position = sf::Vector2f(900.f, 400.f);
    block3[6].position = sf::Vector2f(1100.f, 345.f);
    block3[7].position = sf::Vector2f(1100.f, 400.f);

    block3[0].texCoords = sf::Vector2f(515.f, 270.f);
    block3[1].texCoords = sf::Vector2f(515.f, 380.f);
    block3[2].texCoords = sf::Vector2f(705.f, 270.f);
    block3[3].texCoords = sf::Vector2f(850.f, 380.f);
    block3[4].texCoords = sf::Vector2f(850.f, 345.f);
    block3[5].texCoords = sf::Vector2f(900.f, 400.f);
    block3[6].texCoords = sf::Vector2f(1100.f, 345.f);
    block3[7].texCoords = sf::Vector2f(1100.f, 400.f);


    sf::VertexArray block4(sf::TriangleStrip, 6);
    block4[0].position = sf::Vector2f(1000.f, 550.f);
    block4[1].position = sf::Vector2f(1020.f, 580.f);
    block4[2].position = sf::Vector2f(1280.f, 550.f);
    block4[3].position = sf::Vector2f(1115.f, 580.f);
    block4[4].position = sf::Vector2f(1280.f, 630.f);
    block4[5].position = sf::Vector2f(1150.f, 630.f);
    
    block4[0].texCoords = sf::Vector2f(1000.f, 550.f);
    block4[1].texCoords = sf::Vector2f(1020.f, 580.f);
    block4[2].texCoords = sf::Vector2f(1280.f, 550.f);
    block4[3].texCoords = sf::Vector2f(1115.f, 580.f);
    block4[4].texCoords = sf::Vector2f(1280.f, 630.f);
    block4[5].texCoords = sf::Vector2f(1150.f, 630.f);


    sf::RectangleShape block5(sf::Vector2f(120.f, 105.f));
    block5.setPosition(315, 180);
    block5.setTexture(&tg4);

    sf::VertexArray block6(sf::TriangleStrip, 8);
    block6[0].position = sf::Vector2f(260.f, 120.f);
    block6[1].position = sf::Vector2f(240.f, 150.f);
    block6[2].position = sf::Vector2f(340.f, 120.f);
    block6[3].position = sf::Vector2f(300.f, 150.f);
    block6[4].position = sf::Vector2f(365.f, 150.f);
    block6[5].position = sf::Vector2f(315.f, 180.f);
    block6[6].position = sf::Vector2f(395.f, 150.f);
    block6[7].position = sf::Vector2f(410.f, 180.f);

    block6[0].texCoords = sf::Vector2f(260.f, 120.f);
    block6[1].texCoords = sf::Vector2f(240.f, 150.f);
    block6[2].texCoords = sf::Vector2f(340.f, 120.f);
    block6[3].texCoords = sf::Vector2f(300.f, 150.f);
    block6[4].texCoords = sf::Vector2f(365.f, 150.f);
    block6[5].texCoords = sf::Vector2f(315.f, 180.f);
    block6[6].texCoords = sf::Vector2f(395.f, 150.f);
    block6[7].texCoords = sf::Vector2f(410.f, 180.f);

    sf::RectangleShape rec1(sf::Vector2f(300.f, 35.f));
    rec1.setPosition(30, 740);
    rec1.setTexture(&tg2);


    // doors
    int waterdoor = 3;

    Texture wdoor;
    wdoor.loadFromFile("water door1.PNG");
    Sprite swdoor;
    swdoor.setTexture(wdoor);
    swdoor.setTextureRect(IntRect(waterdoor, 1, 110, 125));
    swdoor.setPosition(1050, 90);
    swdoor.scale(0.75, 0.75);

    int firedoor = 3;

    Texture fdoor;
    fdoor.loadFromFile("fire door1.PNG");
    Sprite sfdoor;
    sfdoor.setTexture(fdoor);
    sfdoor.setTextureRect(IntRect(firedoor, 1, 110, 125));
    sfdoor.setPosition(1150, 90);
    sfdoor.scale(0.75, 0.75);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                Vector2i mousepo = Mouse::getPosition(window);
                cout << mousepo.x << " " << mousepo.y << endl;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
            {
                swdoor.setTextureRect(IntRect(waterdoor, 1, 110, 125));
                waterdoor += 160;
                waterdoor %= 3040;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
            {
                sfdoor.setTextureRect(IntRect(firedoor, 1, 110, 125));
                firedoor += 160;
                firedoor %= 2720;
            }


        }

        window.clear();
        window.draw(sbback);
        window.draw(sback);
        window.draw(f1, &tg);
        window.draw(f2, &tg);
        window.draw(f3, &tg);
        window.draw(f4);
        window.draw(rec1);
        window.draw(g1, &tg);
        window.draw(g2, &tg);
        window.draw(g3, &tg);
        window.draw(g4, &tg);
        window.draw(block1, &tg);
        window.draw(block2, &tg);
        window.draw(block3, &tg);
        window.draw(block4, &tg);
        window.draw(block5);
        window.draw(block6, &tg);
        window.draw(sfdoor);
        window.draw(swdoor);


        window.display();

    }

    return EXIT_SUCCESS;
}

