#include "render.h"
void Render_field(sf::RenderWindow &window,Map &map,Gamer gamer=Gamer() ){

	RectangleShape rs;
	static Texture texture_empty;
	texture_empty.loadFromFile("Images/empty32.png");
	static Sprite sprite_default(texture_empty);

	rs.setFillColor(sf::Color(255,255,255));
	rs.setSize( sf::Vector2f(BLOCK_RENDER_SIZE,BLOCK_RENDER_SIZE) );

	for(int i(0);i<map.getSize();i++)
		for(int j(0);j<map.getSize();j++)
		{
			rs.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);

			//if(arr_isOpen[i][j]) old vers
			if(map.getBlock(i+j).isOpen()) // Здесь будем рендерить открытые поля
			{
				// if(arr[i][j] == MINA) old ver
				if(map.getBlock(i+j).type() == Block::MINE)
					rs.setFillColor( Color(55,172,185) ); // Редер мины
				else
				{
					rs.setFillColor(Color(255,255,255));
				}
			}
			else
			{
				// Тут рендерятся закрытые поля
				//rs.setFillColor(Color(i*7,j*4+40,j*8));
				sprite_default.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);

			}

			window.draw(rs);
			window.draw(sprite_default);

			//if(arr_flag[i][j])
			if(map.getBlock(i+j).isOpen())
			{
				static Texture t;
				t.loadFromFile("Images/flag32.png"); // Добавить анимированный флаг
				static Sprite s(t);
				s.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
				window.draw(s);
			}

		}

	if(!gamer.isAlive()) //?
	{
		Texture texture;
		if(!texture.loadFromFile("Images/mine32.png"))
			;

		Sprite sprite(texture);

		// old
		//            for(int i(0);i<N_X;i++)
		//                 for(int j(0);j<N_Y;j++)
		//                            if(arr[i][j] == MINA && arr_isOpen[i][j] == false)
		//                                {
		//                                    sprite.setPosition(j*BLOCK_SIZE,i*BLOCK_SIZE);
		//                                    window.draw(sprite);
		//                                }
		for(int i(0);i<map.getSize();i++)
			for(int j(0);j<map.getSize();j++)
				if(map.getBlock(i+j).type() == Block::MINE && map.getBlock(i+j).isOpen() == false)
				{
					sprite.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
					window.draw(sprite);
				}

	}
}
