#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "logic.h"
#include "render.h"
#define WINDOW_WIDTH  640 //N_X*BLOCK_SIZE
#define WINDOW_HEIGHT 640 //N_Y*BLOCK_SIZE

using namespace sf;

int main(){
	Map map(25);
	Gamer gamer;
	RenderWindow w(VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Minesweeper,Night of Sibirian Fairy Tale 2015");
	w.setPosition( Vector2i(50,50) );
	//View w_start_size(w.getView().getCenter(),w.getView().getSize());
	// Main loop
	while(w.isOpen())
	{
		w.clear();
		Mouse mouse;
		Event event;
		Render_field(w,map,gamer); // редндер всего поля
		while(w.pollEvent(event))
		{
			if(event.type == Event::Closed)
				w.close();
			else
				if(event.type == Event::MouseButtonPressed  && gamer.isAlive()){
					Vector2i mouse_temp(mouse.getPosition());
					mouse.getPosition(w);
					mouse_temp.x -= w.getPosition().x;
					mouse_temp.y -= w.getPosition().y;
					mouse_temp.x *= w.getViewport( w.getView() ).width/WINDOW_WIDTH;
					mouse_temp.y *= w.getViewport( w.getView() ).height/WINDOW_HEIGHT;
					if(Mouse::isButtonPressed(Mouse::Left))
						//left_mouse(mouse_temp,w);
						map.left_mouse_click(mouse_temp,gamer,w);
					else
						map.right_mouse_click(mouse_temp,gamer,w);
				}
		}//w.pollEvent
		w.display();
	}//main loop

	return 0;
}
