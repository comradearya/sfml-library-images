#include "lab03.hpp"

int main()
{
    pool* pool1 = pool_create();
    img* poolImgs[10];
    int poolBlockSize = sizeof(tga)+256*256*sizeof(COL);
    for (int i = 0; i <= 9; i++)
    {
        poolImgs[i] = pool_new(pool1, poolBlockSize);
        create_header(&(poolImgs[i]->header));
        create_color((poolImgs[i]->matrix), i); 
    }

    Image images[10];
    Texture textures[10];
    Sprite sprites[10];
    for(int i = 0; i <= 9; i++)
    {
        images[i].loadFromMemory(poolImgs[i], poolBlockSize);
        textures[i].loadFromImage(images[i]);
        sprites[i].setTexture(textures[i]);

        int topSprX = ((i + 1) * 4) + i * 256;
        int bottomSprX = 256 * (i - 5) + (i - 5 + 1) * 4;
        int topSprY = 30;
        int bottomSprY = 256 + 4 + 30;
        if(i < 5)
        {
            sprites[i].setPosition(topSprX, topSprY);
        }
        else
        {
            sprites[i].setPosition(bottomSprX, bottomSprY);
        }
    }

    RenderWindow window(sf::VideoMode(1304, 576), "lab03");
	while (window.isOpen())	
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
            if (event.type == Event::Resized) {
                float width = static_cast<float>(event.size.width);
                float heigh = static_cast<float>(event.size.height); 
                float hor_offset = (width - 5 * 256) / 6;
                float vert_offset = (heigh - 2 * 256  - 60) / 3;  
                sf::View view(sf::FloatRect(0, 0, width, heigh));      
                window.setView(view);
                if(width < 1304)
                {
                    window.setSize(Vector2u(1304, heigh));
                }
                if(heigh < 536)
                {
                    window.setSize(Vector2u(width, 576));
                }
                for (int i = 0; i < 10; i++)
                {
                    int curr_topSprX = (i + 1) * hor_offset + i * 256;
                    int curr_bottomSprX = (i - 5 + 1) * hor_offset + (i - 5) * 256;
                    int curr_topSprY = vert_offset + 30;
                    int curr_bottomSprY = 2 * vert_offset  + 256 + 30;
                    if(i < 5)
                    {
                        sprites[i].setPosition(curr_topSprX, curr_topSprY);
                    }
                    else
                    {
                        sprites[i].setPosition(curr_bottomSprX, curr_bottomSprY);
                    }
                }     
            }
		}
		window.clear();
        for (int i = 0; i < 10; i++)
        {
            window.draw(sprites[i]);
        }
		window.display();
	}
    poolObjdelete(pool1);
	return 0;
}


