#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace std;

void drawSquares(sf::RenderWindow *window, int drawFrom, int drawTo)
{
    cout<<"Running thread 1 (t1)"<<endl;
    int windowHeight,windowWidth;
    windowHeight = window->getSize().y;
    windowWidth = window->getSize().x;
    cout<<"Window height: "<<windowHeight<<" Window width: "<<windowWidth<<endl;

    //* Chess window has 8 rows and 8 columns
    int widthofsquare = windowWidth/8;
    int heightofsquare = windowHeight/8;

    sf::RectangleShape square(sf::Vector2f(widthofsquare,heightofsquare));

    //* Storing in a vector
    vector<sf::RectangleShape>chessSquare;  //At position 0 stores black square and at 1 stores white square
    square.setFillColor(sf::Color::Black);  //Changing color to black
    chessSquare.push_back(square);

    square.setFillColor(sf::Color::White);  //Changing color to white
    chessSquare.push_back(square);

    int index1=1,index2=0,xpos=0,ypos = drawFrom*heightofsquare;
    for(int j=drawFrom; j<drawTo; j++)
    {
        for(int i=0; i<8 ;i++)
        {
            if(i%2==0)
            {
                chessSquare[index1].setPosition(xpos,ypos);
                window->draw(chessSquare[index1]);
            }
            else
            {
                chessSquare[index2].setPosition(xpos,ypos);
                window->draw(chessSquare[index2]);
            }
            xpos = xpos + widthofsquare;
        }

        //* Change the color of the square in next line
        if(index1 == 1)
        {
            index1 = 0;
            index2 = 1;
        }
        else
        {
            index1 = 1;
            index2 = 0;
        }
        
        xpos = 0;
        ypos = ypos + heightofsquare;
    }

    return;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600,600),"Chess");
    window.setFramerateLimit(60);

    sf::Event event;
    while(window.isOpen()){
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
            }
        }
        window.clear(sf::Color::Magenta);
        thread t1(drawSquares, &window, 0, 4);
        t1.join();
        thread t2(drawSquares, &window, 4, 8);
        t2.join();
        window.display();
    }

    return 0;
}
