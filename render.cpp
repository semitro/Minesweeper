#include "render.h"
void Render_flag_animated(int i, int j, sf::RenderWindow &window){
	static sf::Clock clock;
	static float time = clock.getElapsedTime().asMicroseconds();

	static float current_frame = 0;
	static IntRect rect;
	rect.height = 32;
	rect.width = 32;

	current_frame += time;
	if(current_frame > 4)
		current_frame=0;

	rect.left = int(current_frame)*32;
	static Texture texture;
	texture.loadFromFile("Images/flag_animated.png");
	static Sprite sprite(texture);
	sprite.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
	sprite.setTextureRect(rect);
	window.draw(sprite);
		time += clock.getElapsedTime().asMilliseconds();
		time /= 200;
		clock.restart();
}
void Render_explosion_animated(int i, int j, sf::RenderWindow &window){
	static sf::Clock clock;
	static float time = clock.getElapsedTime().asMicroseconds();
	static IntRect rect;
	rect.height = 64;
	rect.width = 32;
	static float current_frame = 0;
	current_frame += time;
	current_frame += 0.072;
	if(current_frame > 5)
		current_frame=0;
	rect.left = int(current_frame)*32;
	static Texture texture;
	texture.loadFromFile("Images/explosion_many.png");
	static Sprite sprite(texture);
	sprite.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE-BLOCK_RENDER_SIZE);
	sprite.setTextureRect(rect);
	window.draw(sprite);
	time += clock.getElapsedTime().asMilliseconds();
	time /= 200;
	clock.restart();

}
void Render_field(sf::RenderWindow &window,Map &map,Gamer gamer=Gamer() ){
	RectangleShape rs;
	rs.setFillColor(sf::Color(255,255,255));
	rs.setSize( sf::Vector2f(BLOCK_RENDER_SIZE,BLOCK_RENDER_SIZE) );
	static bool first = true; // Чтобы загрузить текстуры только раз, не мучить хдд

	// Спрайт для неоткрытого поля
	static Texture texture_notOpened;
	if(first)
		texture_notOpened.loadFromFile("Images/notOpen32.png");
	static Sprite sprite_default(texture_notOpened);

	// Спрайт для открытого пустого поля
	static Texture texture_empty_opened;
	if(first)
		texture_empty_opened.loadFromFile("Images/empty32.png");
	static Sprite sprite_empty_opened(texture_empty_opened);

	// Спрайт для мины
	static Texture texutre_mine;
	if(first)
		texutre_mine.loadFromFile("Images/mine32.png");
	static Sprite sprite_mine(texutre_mine);
	//цифра один
	static Texture texture_1;
	if(first)
		texture_1.loadFromFile("Images/1_32.png");
	static Sprite sprite_1(texture_1);
	// 2
	static Texture texture_2;
	if(first)
		texture_2.loadFromFile("Images/2_32.png");
	static Sprite sprite_2(texture_2);
	// 3
	static Texture texture_3;
	if(first)
		texture_3.loadFromFile("Images/3_32.png");
	static Sprite sprite_3(texture_3);
	// 4
	static Texture texture_4;
	if(first)
		texture_4.loadFromFile("Images/4_32.png");
	static Sprite sprite_4(texture_4);
	// Взрыв
	static Texture texture_explosion;
	if(first)
		texture_explosion.loadFromFile("Images/explosion_main.png");
	static Sprite sprite_explosion(texture_explosion);
	first = false;

	static int explosion_point_i(0), explosion_point_j(0);
	for(int i(0);i<map.getSize();i++)
		for(int j(0);j<map.getSize();j++)
		{
			rs.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
			if(map.getBlock(i,j).isOpen()){ // Здесь будем рендерить открытые поля

				if(map.getBlock(i,j).type() == Block::MINE){
					// рендер мины

					sprite_mine.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
					window.draw(sprite_mine);
				//	Render_explosion_animated(i,j,window);
					explosion_point_i = i;
					explosion_point_j = j;
				}else{
					// Редер пустого поля
					sprite_empty_opened.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
					window.draw(sprite_empty_opened);
					// Рендер количества мин рядом
					switch(map.getBlock(i,j).getMinesAround()){
						case 1:
							sprite_1.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
							window.draw(sprite_1);
							break;
						case 2:
							sprite_2.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
							window.draw(sprite_2);
							break;
						case 3:
							sprite_3.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
							window.draw(sprite_3);
							break;
						case 4:
							sprite_4.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
							window.draw(sprite_4);
							break;
					}

				}
			}else{	// Тут рендерятся закрытые поля
				sprite_default.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
				window.draw(sprite_default);
			}
			if(map.getBlock(i,j).isFlag())// Реднерим флаги
				Render_flag_animated(i,j,window);

		}
	if(!gamer.isAlive())
	{ // Вскрываем карты
		for(int i(0);i<map.getSize();i++)
			for(int j(0);j<map.getSize();j++)
				if(map.getBlock(i,j).type() == Block::MINE){
					sprite_mine.setPosition(j*BLOCK_RENDER_SIZE,i*BLOCK_RENDER_SIZE);
					window.draw(sprite_mine);
				}
		Render_explosion_animated(explosion_point_i,explosion_point_j,window);
	}

}

