

#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h" 

using namespace sf;

float offsetX = 0, offsetY = 0;
float frame = 0;
class Player
{
public:

    float x = 0, y = 0, w = 0, h = 0, dx = 0, dy = 0, speed = 0;
    bool onGround;
    int dir;  //���������� ��������
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    //����������� ������
    Player(String F, int X, int Y, float W, float H) {
        File = F;
        w = W; h = H;
        //name = NAME;
        image.loadFromFile("images/player.png");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(IntRect(w, h, w, h));
        sprite.setPosition(0, 185);
    }
    //�������� �������, ��� ���������� �������� � �������� �������
    void update(float time)
    {
        switch (dir)
        {
        case 0: dx = -speed; dy = 0; break;
        case 1: dx = speed; dy = 0; break;
        case 2: dx = 0; dy = -speed; break;
        case 3: dx = 0; dy = speed; break;
        }

        x += dx * time; y += dy * time;
        //std::cout << dx << ' ' << time << ' ' << dy << std::endl;
        speed = 0;
        sprite.setPosition(x, y);
        //std::cout << x << ' ' << y << std::endl;
    }
};




int main()
{
    RenderWindow window(VideoMode(1510, 270), "start");

    Image map_image;//������ ����������� ��� �����
    map_image.loadFromFile("images/map.png");//��������� ���� ��� �����
    Texture map;//�������� �����
    map.loadFromImage(map_image);//�������� �������� ���������
    Sprite s_map;
    s_map.setTexture(map);//�������� �������� ��������

    Player hero("images/player.png", 0, 185, 32, 96);

    Clock clock;


    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();

        // std::cout << time << std::endl;


        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //����������
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            hero.dir = 0; hero.speed = 0.1;
            //CurrentFrame += 0.005 * time;
            //��������
            frame += 0.02 * time;
            // std::cout << "A is pressed" << std::endl;

        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            hero.dir = 1; hero.speed = 0.1;

        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            hero.dir = 2; hero.speed = 0.1;

        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            if (hero.onGround) { hero.dy = -0.35; hero.onGround = false; }
        }

        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            hero.dir = 3; hero.speed = 0.1;

        }

        hero.update(time);
        // std::cout << hero.x << ' ' << hero.y << std::endl;



        window.clear();

        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(6, 1, 56, 51));
                if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(91, 61, 136, 98));
                if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(0, 55, 38, 100));
                if (TileMap[i][j] == '1') s_map.setTextureRect(IntRect(56, 53, 80, 95));
                if (TileMap[i][j] == '2') s_map.setTextureRect(IntRect(95, 0, 120, 51));


                s_map.setPosition(j * 32, i * 32);// ������ ������� �� ��� �������.

                window.draw(s_map);//������ ���������� �� �����
            }

        window.draw(hero.sprite);
        window.display();


    }

    return 0;
}



