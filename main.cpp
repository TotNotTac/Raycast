#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>


int main()
{


    int biggestindex = 0;
    int biggestindex2 = 0;


    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    sf::Clock counter;

    sf::Clock timer;
    double skippedTime = 0;

    float pi = atan(1)*4;
    double angle;



    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(40,20));
    rect.setPosition(240,250);
    rect.setOrigin(20,10);


    sf::CircleShape emitter;
    emitter.setRadius(10);
    emitter.setOrigin(10,10);

    double angledifferences[rect.getPointCount()];



    sf::VertexArray lines[rect.getPointCount()];
    sf::VertexArray middleline(sf::Lines,2);


    for (std::size_t i = 0; i < rect.getPointCount() + 1 ; i++) {
        lines[i] = sf::VertexArray(sf::LineStrip,3);
        lines[i][0].color = sf::Color(255,0,0);
        lines[i][1].color = lines[i][0].color;
        lines[i][2].color = lines[i][0].color;
    }
    middleline[0].color = sf::Color(0,255,0);
    middleline[1].color = middleline[0].color;



    while (window.isOpen())
    {
        const double elapsedTime = timer.restart().asMicroseconds() / 1000.;
        skippedTime += elapsedTime;

        int biggest = 0;

        while (skippedTime > 15)  {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.mouseButton.button == sf::Mouse::Left)
                {

                }
            }

            emitter.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

            middleline[0].position = emitter.getPosition();
            middleline[1].position = rect.getPosition();


            angle = atan2((middleline[1].position.x - middleline[0].position.x),(middleline[1].position.y - middleline[0].position.y));

            angle = angle * 180 / pi;
            angle += 180;

            for (size_t i = 0; i < rect.getPointCount(); i++) {
                //std::cout << lines[i].getVertexCount() << std::endl;
                sf::Vector2f emitpos = emitter.getPosition();
                lines[i][0].position = emitpos;

                sf::Vector2f targetpos = rect.getPoint(i) + rect.getPosition() - rect.getOrigin();

                lines[i][1].position = targetpos;

                double angle2 = atan2((lines[i][1].position.x - lines[i][0].position.x),(lines[i][1].position.y - lines[i][0].position.y));

                lines[i][2].position = sf::Vector2f(sin(angle2)*100,cos(angle2)*100) + lines[i][1].position;

                angle2 = angle2 * 180 / pi;
                angle2 += 180;

                double difference;
                //double difference = std::abs(angle - angle2);
                difference = 180 - std::abs(std::abs(angle - angle2) - 180);
                if (angle < angle2) {
                    difference = difference * -1;
                }

                //std::cout << angle << " --> " << angle2 << std::endl;





                //double difference = 180 - abs(abs(angle - angle2) - 180);
                //angledifferences[i] = std::abs(difference);
                angledifferences[i] = difference;

            }
            //std::cout << angledifferences[1] << std::endl;

            biggestindex2 = 0;
            double biggest2 = 0;

            biggest = angledifferences[0];
            for (int i = 0; i < rect.getPointCount() ; i++) {
                if (angledifferences[i] > 0){
                    if (angledifferences[i] > biggest) {

                        biggest = angledifferences[i];
                        biggestindex = i;
                    }
                } else {
                    if (angledifferences[i] < biggest2) {
                        biggest2 = angledifferences[i];
                        biggestindex2 = i;
                    }
                }
            }





            //std::cout << biggestindex << "  " << biggestindex2 << std::endl;




        skippedTime -= 1.5;
        }

        window.clear();
        window.draw(rect);
        //window.draw(emitter);
        /*for (std::size_t i = 0; i < rect.getPointCount(); i++) {
            window.draw(lines[i]);
        }*/
        window.draw(lines[biggestindex]);
        window.draw(lines[biggestindex2]);
        window.draw(middleline);
        window.display();
    }

    return 0;
}
