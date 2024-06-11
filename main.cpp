#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <ctime> 
#include <vector>
#include <unistd.h>
#include <queue>

int main()
{
//setting up variables and their values
    srand(time(0));

    int pixelSize = 25,
        resolution = 750,
        resp = resolution / pixelSize,
        x = (resp-1)/2,
        y = (resp-1)/2,
        counter = 1;

    float time = 1;
    char direction = '\0';
    bool skipRemoval = false;

    sf::RenderWindow window(sf::VideoMode(resolution, resolution), "Snake!", sf::Style::Close);

    sf::Clock clock;

    std::vector<sf::RectangleShape> backGround;
    std::vector<std::vector<char>> map (resp, std::vector<char>(resp, ' '));
    map[x][y]='s';

    std::queue<std::pair<int,int>> tails;

    /*setting a background tiles*/
    for(int i=0; i<=resolution; i+=pixelSize)
    {
        for(int j=0; j<=resolution; j+=pixelSize)
        {  
            sf::RectangleShape pixel(sf::Vector2f(pixelSize,pixelSize));
            pixel.setPosition(sf::Vector2f(i,j));

            if((i/pixelSize + j/pixelSize) % 2 == 0)
                pixel.setFillColor(sf::Color(75, 75, 75));
            else
                pixel.setFillColor(sf::Color(50,50,50));
            
            backGround.push_back(pixel);
        }
    }

    /*setting a start apple*/
    int xx=rand()%resp,yy=rand()%resp;
    while(map[xx][yy]!=' ')
    {
        xx=rand()%resp;
        yy=rand()%resp;
    }
    map[xx][yy]='a';


//main game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::W) direction = 'w';
                if(event.key.code == sf::Keyboard::A) direction = 'a';
                if(event.key.code == sf::Keyboard::S) direction = 's';
                if(event.key.code == sf::Keyboard::D) direction = 'd';
            }
        }

        /*snake speed being set by time variable*/
        if(clock.getElapsedTime().asMilliseconds() < time*1000) continue;
        clock.restart();

        for(int i = 0; i < resp; i++)
        {
            for(int j = 0; j < resp; j++)
            {
                if(map[i][j]=='s')
                {
                    int idelta=0, jdelta=0;
                    switch(direction)
                    {
                        case 'w':
                        jdelta=-1;
                        break;

                        case 'a':     
                        idelta=-1;
                        break;

                        case 's':
                        jdelta=1;
                        break;

                        case 'd':
                        idelta=1;
                        break;
                    }

                    /*if snakes head hit the boundaries or itself*/
                    if(i+idelta==resp || i+idelta==-1 ||
                       j+jdelta==resp || j+jdelta==-1 ||
                       map[i+idelta][j+jdelta]=='S') window.close();

                    /*if the next tile is filled with apple*/
                    if(map[i+idelta][j+jdelta]=='a') 
                    {
                        counter++;
                        skipRemoval=true;
                        time = 0.9*time;

                        /*setting a new apple*/
                        int xx=rand()%resp,yy=rand()%resp;
                        while(map[xx][yy]!=' ')
                        {
                            xx=rand()%resp;
                            yy=rand()%resp;
                        }
                        map[xx][yy]='a';
                    }
                    /*setting new snake head*/
                    map[i+idelta][j+jdelta]='s';

                    /*setting current snake head as the tail*/
                    if(direction!='\0') 
                    {
                        map[i][j]='S';
                        tails.push({i,j});
                    }

                    /*breaking out of the two loops*/
                    i+=resp+1;
                    break;
                }
            }
        }

        /*removing the last part of tail*/
        if(skipRemoval || tails.size()==0) skipRemoval = false;
        else
        {
            map[tails.front().first][tails.front().second]=' ';
            tails.pop();
        }


//drawing graphics
        window.clear();

        /*drawing background tiles*/
        for(auto pixel : backGround) window.draw(pixel);

        /*drawing snake tails and apple*/
        for(int i=0; i<resp; i++)
        {
            for(int j=0; j<resp; j++)
            {
                if(tolower(map[i][j])=='s') /*snake*/
                {
                    sf::RectangleShape pixel(sf::Vector2f(pixelSize,pixelSize));
                    pixel.setPosition(sf::Vector2f(i*pixelSize,j*pixelSize));
                    pixel.setFillColor(sf::Color::Green);

                    window.draw(pixel);
                }
                else if(map[i][j]=='a') /*apple*/
                {
                    sf::RectangleShape pixel(sf::Vector2f(pixelSize,pixelSize));
                    pixel.setPosition(sf::Vector2f(i*pixelSize,j*pixelSize));
                    pixel.setFillColor(sf::Color::Red);

                    window.draw(pixel);
                }
            }
        }

        window.display();
    }

    return 0;
}