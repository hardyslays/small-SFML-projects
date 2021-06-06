#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#define SIZE 1000
#define gravity 0.6     //GRAVITY
#define FORCE 15        //FORCE
#define DRAG 2        //AAIR DRAG DECELLARATION
#define MASS 10         //MASS IS 10 KG
using namespace sf;

int main()
{
    RenderWindow app(VideoMode(SIZE, SIZE), "BOX IN BOX");
    app.setFramerateLimit(60);

    RectangleShape bigBox(Vector2f(SIZE/2, SIZE/2));
    bigBox.setFillColor(Color::White);
    bigBox.setOrigin(SIZE/4, SIZE/4);
    bigBox.setPosition(SIZE/2, SIZE/2);

    RectangleShape smallBox(Vector2f(SIZE/40, SIZE/40));
    smallBox.setFillColor(Color::Blue);
    // smallBox.setOrigin(SIZE/250, SIZE/250);
    smallBox.setPosition(SIZE/2, SIZE/2);

    float ax = 0, ay = 0, vx = 0, vy = 0, fx = 0, fy = 0;
    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if(e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                app.close();    
        }

        //BOX FORCE BY USER
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            fy = -FORCE;
        }
        // if (Keyboard::isKeyPressed(Keyboard::S))
        // // {
        // //     fy = FORCE;
        // // }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            fx = -FORCE;
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            fx = FORCE;
        }


        //MOVEMENT
            //CALC OF FORCE
        fy += MASS*gravity;
            //CALC OF ACC.
        ax += fx;
        ay += fy;
            //RESETTING THE FORCE
        fx = 0;
        fy = 0;
            //CALC OF VELOCITY
        vx += ax;
        vy += ay;
            //DRAG
        if(ax < 0)
        {
            ax += DRAG;
            if(ax >0) ax = 0;
        }

        smallBox.move(vx, vy);

        //COLLISION
        if( (smallBox.getPosition().x) <= bigBox.getPosition().x - bigBox.getSize().x/2 )
        {
            if(ax < 0)ax = -ax;
            vx = -(vx/2);
            smallBox.setPosition(bigBox.getPosition().x - bigBox.getSize().x/2, smallBox.getPosition().y);
        }
        if( (smallBox.getPosition().x ) >= bigBox.getPosition().x + bigBox.getSize().x/2 - smallBox.getSize().x)
        {
            if(ax > 0)ax = -ax;
            vx = -(vx/2);   
            smallBox.setPosition(bigBox.getPosition().x + bigBox.getSize().x/2 - smallBox.getSize().x, smallBox.getPosition().y);
        }
        if( (smallBox.getPosition().y) <= bigBox.getPosition().y - bigBox.getSize().y/2 )
        {
            if(ay < 0)ay = -(ay/2);
            vy = 0;
            smallBox.setPosition(smallBox.getPosition().x, bigBox.getPosition().y - bigBox.getSize().y/2);
        }
        if( (smallBox.getPosition().y) >= bigBox.getPosition().y + bigBox.getSize().y/2 - smallBox.getSize().y)
        {
            if(ay > 0)ay = -(ay/2);
            vy = 0;
            smallBox.setPosition(smallBox.getPosition().x, bigBox.getPosition().y + bigBox.getSize().y/2 - smallBox.getSize().y);
        }


        //DRAW
        app.clear();

        app.draw(bigBox);
        app.draw(smallBox);

        app.display();
    }
    
    return 0;
}