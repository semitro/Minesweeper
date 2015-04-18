#include "render.h"
void Render_field(sf::RenderWindow &window,Map &map,Gamer gamer=Gamer() ){

	RectangleShape rs;

	// Спрайт для неоткрытого поля
	static Texture texture_notOpened;
	texture_notOpened.loadFromFile("Images/notOpen32.png");
	static Sprite sprite_default(texture_notOpened);
	// Спрайт для открытого пустого поля
	static Texture texture_empty_opened;
	texture_empty_opened.loadFromFile("Images/empty32.png");
	static Sprite sprite_empty_opened(texture_empty_opened);
	// Спрайт для мины
	static Texture texutre_sprite;
	texutre_sprite.loadFromFile("Images/mine32.png");
	static Sprite sprite_mine(texutre_sprite);

	rs.setFillColor(sf::Color(255,255,255));
	rs.setSize( sf::Vector2f(BLOCK_RENDER_SIZE,BLOCK_RENDER_SIZE) );

	for(int i(0);i<map.getSize();i++)
		for(int j(0);j<map.getSize();j++)
		{
			rs.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);

			//if(arr_isOpen[i][j]) old vers
			if(map.getBlock(i,j).isOpen()) // Здесь будем рендерить открытые поля
			{
				// if(arr[i][j] == MINA) old ver
				if(map.getBlock(i,j).type() == Block::MINE)
					rs.setFillColor( Color(55,172,185) ); // Редер мины
				else
				{
					//rs.setFillColor(Color(255,255,255));
					sprite_empty_opened.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
					window.draw(sprite_empty_opened);
				}
			}
			else
			{	// Тут рендерятся закрытые поля
				//rs.setFillColor(Color(i*7,j*4+40,j*8));
				sprite_default.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);

			}

		//	window.draw(rs);
			window.draw(sprite_default);

			//if(arr_flag[i][j])
			if(map.getBlock(i,j).isFlag())
			{
				static Texture t;
				t.loadFromFile("Images/flag32.png"); // Добавить анимированный флаг
				static Sprite s(t);
				s.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
				window.draw(s);
			}

		}

	if(!gamer.isAlive())
	{
		Texture texture;
		texture.loadFromFile("Images/mine32.png");


		Sprite sprite(texture);

		window.draw(sprite);

		for(int i(0);i<map.getNumberBlocks();i++) // Цикл по всем блокам
			if(map.getBlock(i).type() == Block::MINE && map.getBlock(i).isOpen() == false)
			{
				sprite.setPosition(map.getBlock(i).getJ()*BLOCK_RENDER_SIZE,map.getBlock(i).getI()*BLOCK_RENDER_SIZE);
				window.draw(sprite);
			}
	}
}
