#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>
#define MAX 15
#define TIMER 8
using namespace sf;

int state = 0, size = 1, grid = 50, dir = 1;

struct pos
{
    int x = -100, y = -100;
}snake[MAX * MAX], pt;

int main()
{
    srand(time(NULL));

    RenderWindow app(VideoMode(grid*MAX, grid*MAX), "THE SNAKE GAME");
    app.setFramerateLimit(60);

    RectangleShape body(Vector2f(grid, grid)), bg(Vector2f(grid *MAX, grid * MAX)), point(Vector2f(grid, grid));
    Texture bodybg;
    std::cout << bodybg.loadFromFile("body.png");
    int moveTimer{TIMER};

    body.setTexture(&bodybg);
    bg.setFillColor(Color(239, 226, 79));
    point.setFillColor(Color::Red);

    Font f;
    if(!f.loadFromFile("./font.ttf"))std::cout << " FONT CANNOT BE LOADED.\n";
    Text t, p;
    t.setFont(f);
    t.setCharacterSize(MAX*2);
    t.setString("Press SPACEBAR to restart");
    t.setPosition( (grid*MAX/2)-MAX*14, (grid*MAX/2) - MAX*3 );
    p.setFont(f);
    p.setCharacterSize(MAX*2);
    p.setPosition( (grid*MAX/2)- MAX*5 , MAX );

    while(app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if(e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                app.close();

            if(Keyboard::isKeyPressed(Keyboard::W) && dir != 2)dir = 4;
            if(Keyboard::isKeyPressed(Keyboard::S) && dir != 4)dir = 2;
            if(Keyboard::isKeyPressed(Keyboard::A) && dir != 1)dir = 3;
            if(Keyboard::isKeyPressed(Keyboard::D) && dir != 3)dir = 1;   
        }
        
        app.clear();


        if(state == 0)
        {
            p.setFillColor(Color::Red);
            
            dir = 1;
            size = 1;
            snake[0].x = 4;
            snake[0].y = 4;
            pt.x = 7;
            pt.y = 4;
            state = 1;
            continue;
        }

        if(state == 1)
        {
            //COLLISION
            for (int i = 1; i < size; i++)
            {
                if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
                {
                    state = -1;
                    break;
                }
            }
            
            if(snake[0].x >= MAX){
                snake[0].x = 9;
                state = -1;
            }
            if(snake[0].x < 0){
                snake[0].x = 0;
                state = -1;
            }
            if(snake[0].y >= MAX){
                snake[0].y = 9;
                state = -1;
            }
            if(snake[0].y < 0){
                snake[0].y = 0;
                state = -1;
            }
            
            //MOVINGSNAKE
            if(moveTimer)
            {
                moveTimer--;
            }
            else
            {
		        //MOVING REST OF BODY
                for (int i = size-1; i > 0; i--)
                {
                    snake[i].x = snake[i-1].x;
                    snake[i].y = snake[i-1].y;
                }
                
		        //MOVING FIRST PART OF BODY
                if(dir == 1)snake[0].x++;
                if(dir == 3)snake[0].x--;
                if(dir == 2)snake[0].y++;
                if(dir == 4)snake[0].y--;
                
                moveTimer = TIMER;
            }

            //DRAWING STUFF
            app.draw(bg);
            for (int i = 0; i < size; i++)
            {
                body.setPosition((float)snake[i].x * grid, (float)snake[i].y * grid);
                app.draw(body);
            }
            point.setPosition(pt.x*grid, pt.y*grid);
            app.draw(point);
            p.setString("POINTS: " + std::to_string(size-1) );
            app.draw(p);

            //POINT GAINING
            if(snake[0].x == pt.x && snake[0].y == pt.y)
            {
                size++;
                snake[size-1].x = -1;
                snake[size-1].y = -1;
                bool f = 1;
                while(f)
                {
                    pt.x = rand()%MAX;
                    pt.y = rand()%MAX;
                    f = 0;
                    for (int i = 0; i < size; i++)
                    {
                        if(pt.x == snake[i].x && pt.y == snake[i].y)
                        {
                            f = 1;
                            break;
                        }
                    }
                }
            }

            
            
            

        }
    
        if(state == -1)
        {

            p.setFillColor(Color::White);
            app.draw(t);
            app.draw(p);
            if(Keyboard::isKeyPressed(Keyboard::Space))
            {
                state = 0;
            }
        }

        app.display();
    
    }

    return 0;
}
