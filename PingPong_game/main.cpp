#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <random>
#define SIZE 1000           //SIZE OF BOARD
#define MAX_POINT 3         //MAXIMUM POINT NEEDED TO WIN THE MATCH
#define MAX_SPEED 10.0      //MAXIMUM Y SPEED OF BALL
using namespace sf;

int state = 0;

int main()
{
    RenderWindow app(VideoMode(SIZE, SIZE), "PING PONG GAME");
    app.setFramerateLimit(60);

    Font styles;
    if(!styles.loadFromFile("font.ttf"))std::cout << "FONT CANNOT BE LOADED\n";
    RectangleShape p1(Vector2f(SIZE/50,SIZE/8)), p2(Vector2f(SIZE/50,SIZE/8)), bg(Vector2f(SIZE,SIZE));
    CircleShape ball(SIZE/100);
    Text score;
    score.setFont(styles);
    score.setCharacterSize(SIZE/20);
    score.setFillColor(Color::Black);
    float vel1 = 0, vel2 = 0;
    float ballx, bally;

    int s1, s2;

    p1.setFillColor(Color::Green);
    p2.setFillColor(Color::Green);
    ball.setFillColor(Color::Red);
    bg.setFillColor(Color::White);


    while (app.isOpen())
    {
        Event e;
        while(app.pollEvent(e))
        {
            if(e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                app.close();
        }

        app.clear();

        app.draw(bg);
        

        //STATE ): The welcome page of the game
        if(state == 0)
        {
            s1 = 0;
            s2 = 0;

            Text welcome;
            welcome.setFont(styles);
            welcome.setCharacterSize(SIZE/20);
            welcome.setFillColor(Color::Black);            
            welcome.setString("CLASSIC PING PONG");
            welcome.setPosition(SIZE/2 - welcome.getGlobalBounds().width/2, SIZE/2 - welcome.getGlobalBounds().height/2);
            app.draw(welcome);
            welcome.setString("Press ENTER to start the game");
            welcome.setPosition(SIZE/2 - welcome.getGlobalBounds().width/2, SIZE/2 + welcome.getGlobalBounds().height);
            app.draw(welcome);

            if(Keyboard::isKeyPressed(Keyboard::Enter))state = 2;
        }

        //STATE 2: If the game has just started or the Left player has scored point in last round
        if(state == 2)
        {
            bg.setFillColor(Color(136, 135, 134));

            //INITIALIZE
            p1.setPosition(0, (SIZE - p1.getGlobalBounds().height)/2);
            p2.setPosition(SIZE - p2.getGlobalBounds().width, (SIZE - p2.getGlobalBounds().height)/2);
            ball.setPosition(app.getSize().x/2 - ball.getRadius(), app.getSize().y/2 - ball.getRadius());
            vel1 = 0;
            vel2 = 0;
            ballx = -(rand()%6 + 5);
            bally = rand()%6 + 3;
            if(rand()%2)bally = - bally;

            sleep(milliseconds(500));
            state = 1;
        }
        
        //STATE 3: If right player has scored in last round
        if(state == 3)
        {
            //INITIALIZE
            p1.setPosition(0, (SIZE - p1.getGlobalBounds().height)/2);
            p2.setPosition(SIZE - p2.getGlobalBounds().width, (SIZE - p2.getGlobalBounds().height)/2);
            ball.setPosition(app.getSize().x/2 - ball.getRadius(), app.getSize().y/2 - ball.getRadius());
            vel1 = 0;
            vel2 = 0;
            ballx = rand()%6 + 5;
            bally = rand()%6 + 3;
            if(rand()%2)bally = - bally;

            sleep(milliseconds(500));
            state = 1;
        }

        //If the round is currently going on
        if(state == 1)
        {
            //PLAYER ONE MOVEMENT
            if(Keyboard::isKeyPressed(Keyboard::W))vel1 -= 1.5;
            if(Keyboard::isKeyPressed(Keyboard::S))vel1 += 1.5;
            p1.move(0, vel1);
            if(vel1 > 0)
            {
                vel1 -= 1;
                if(vel1 < 0)vel1 = 0;
            }
            if(vel1 < 0)
            {
                vel1 += 1;
                if(vel1 > 0)vel1 = 0;
            }

            //PLAYER ONE COLLISION WITH WALLS
            if(p1.getPosition().y < 0)p1.setPosition(0, 0);
            if(p1.getPosition().y > SIZE - p1.getSize().y)p1.setPosition(0, SIZE - p1.getSize   ().y);
            
            //PLAYER 2 MOVEMENTS
            if(Keyboard::isKeyPressed(Keyboard::Up))vel2 -= 1.5;
            if(Keyboard::isKeyPressed(Keyboard::Down))vel2 += 1.5;
            p2.move(0, vel2);
            if(vel2 > 0)
            {
                vel2 -= 1;
                if(vel2 < 0)vel2 = 0;
            }
            if(vel2 < 0)
            {
                vel2 += 1;
                if(vel2 > 0)vel2 = 0;
            }

            //PLAYER TWO COLLISION WITH WALLS
            if(p2.getPosition().y < 0)p2.setPosition(SIZE - p2.getGlobalBounds().width, 0);
            if(p2.getPosition().y > SIZE - p2.getSize().y)p2.setPosition(SIZE - p2.getGlobalBounds().width, SIZE - p2.getSize().y);
            
            //BALL MOVEMENT
            ball.move(ballx, bally);

            //BALL COLISION
            //UP
            if(ball.getPosition().y <= 0)bally = -bally;
            //DOWN
            if(ball.getPosition().y > SIZE - 2*ball.getRadius())bally = -bally;
            //RIGHT WALL
            if(ball.getPosition().x < ball.getRadius())
            {
                state = 2;
                s2++;
            }
            //LEFT WALL
            if(ball.getPosition().x > SIZE - ball.getRadius())
            {
                state = 3;
                s1++;
            }
            //PLAYER 1
            if(ball.getGlobalBounds().intersects(p1.getGlobalBounds()))
            {
                ballx = -ballx;
                bally += vel1;
                if(bally > MAX_SPEED)bally = MAX_SPEED;
                if(bally < -MAX_SPEED)bally = -MAX_SPEED;

            }
            //PLAYER 2
            if(ball.getGlobalBounds().intersects(p2.getGlobalBounds()))
            {
                ballx = -ballx;
                bally += vel2;
                if(bally > MAX_SPEED)bally = MAX_SPEED;
                if(bally < -MAX_SPEED)bally = -MAX_SPEED;
            }
            
            //DISPLAY SCORE
            score.setString((char)(s1+48));
            score.setPosition(SIZE/4, score.getGlobalBounds().height*2);
            app.draw(score);

            score.setString((char)(s2+48));
            score.setPosition(3*SIZE/4, score.getGlobalBounds().height*2);
            app.draw(score);

            //CHECKING WINNER
            if(s1 == MAX_POINT || s2 == MAX_POINT)state = 4;

            //DRAWING STUFF
            app.draw(p1);
            app.draw(p2);
            app.draw(ball);
        }

        //If any one player has won
        if(state == 4)
        {
            //DISPLAY SCORE
            score.setString((char)(s1+48));
            score.setPosition(SIZE/4 - SIZE/40, SIZE/20);
            app.draw(score);

            score.setString((char)(s2+48));
            score.setPosition(3*SIZE/4 - SIZE/40, SIZE/20);
            app.draw(score);


            if(s1 == MAX_POINT)
            {    
                score.setString("PLAYER ONE WINS THE MATCH.");
                score.setPosition(SIZE/2 - score.getGlobalBounds().width/2, SIZE/2 - score.getGlobalBounds().height);
                app.draw(score);
            }
            else if(s2 == MAX_POINT)
            {    
                score.setString("PLAYER TWO WINS THE MATCH.");
                score.setPosition(SIZE/2 - score.getGlobalBounds().width/2, SIZE/2 - score.getGlobalBounds().height);
                app.draw(score);
            }

            score.setString("Press ENTER to restart the game");
                score.setPosition(SIZE/2 - score.getGlobalBounds().width/2, SIZE/2 + score.getGlobalBounds().height);
            app.draw(score);

            if(Keyboard::isKeyPressed(Keyboard::Enter))state = 0;
        }

        app.display();
    }
    return 0;
}