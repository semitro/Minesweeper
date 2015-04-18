#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstdlib>
#include "logic.h"
#include "render.h"
using namespace sf;

#define N_X 20
#define N_Y 20
#define MINA -2
#define EMPTY 0
#define BLOCK_SIZE 32

#define WINDOW_WIDTH  640 //N_X*BLOCK_SIZE
#define WINDOW_HEIGHT 640 //N_Y*BLOCK_SIZE
//char arr[N_X][N_Y]; // массив для рендера


bool gamer_alive;
int arr[N_X][N_Y];
bool arr_isOpen[N_X][N_Y];
bool arr_flag[N_X][N_Y];
std::ofstream fout;


void game_over(RenderWindow &window){

	gamer_alive = false;
}

void open(int i,int j,bool start=false){

	static bool mina_detected = false;
	if(start) mina_detected = false;
	if(mina_detected)
		return;

	if(i < 0 || j <0 || i>=N_X || j >= N_Y)
		return;


	if(arr[i][j] == MINA)
	{
		mina_detected = true;
		return;
	}

	if(arr_isOpen[i][j])
		return;

	arr_isOpen[i][j] = true;

	/* if(i+1<N_X && j+1 <N_Y && arr[i+1][j+1] != MINA )
		open(i+1,j+1);
	if(i-1>=0 && j-1>=0 && arr[i-1][j+1] !=MINA)
		open(i-1,j-1);
	if(i+1 < N_X && j-1 >=0 && arr[i+1][j-1] != MINA)
		open(i+1,j-1);
	if(i-1>=0 && j+1 <N_Y && arr[i-1][j+1] != MINA)
	 open(i-1,j+1);*/
	if(
			!(
				arr[i+1][j] == EMPTY && arr[i][j+1] == EMPTY
				&&
				arr[i+1][j+1] == EMPTY && arr[i+1][j-1] == EMPTY
				&&
				arr[i-1][j] == EMPTY && arr[i-1][j-1] == EMPTY
				&&
				arr[i-1][j+1] == EMPTY && arr[i][j-1] == EMPTY
				)
			)
	{
		open(i+1,j); //
		open(i,j+1); //
		open(i+1,j+1); //
		open(i+1,j-1); //
		open(i-1,j); //
		open(i-1,j-1);//
		open(i-1,j+1); //
		open(i,j-1); //
	}



}
void left_mouse(sf::Vector2i pos,RenderWindow &w){


	if(pos.x/BLOCK_SIZE < N_X && pos.y/BLOCK_SIZE < N_Y)
	{
		if(!arr_flag[pos.y/BLOCK_SIZE][pos.x/BLOCK_SIZE])
		{
			if(arr[pos.y/BLOCK_SIZE][pos.x/BLOCK_SIZE] == MINA)
				game_over(w);

			// arr_isOpen[pos.y/BLOCK_SIZE][pos.x/BLOCK_SIZE] = true;
			open(pos.y/BLOCK_SIZE,pos.x/BLOCK_SIZE,true);
		}
	}



	//if(arr[pos.x/8][pos.y/8] == MINA);


}
void rigth_mouse(Vector2i pos,RenderWindow &w){
	arr_flag[pos.y/BLOCK_SIZE][pos.x/BLOCK_SIZE] = !arr_flag[pos.y/BLOCK_SIZE][pos.x/BLOCK_SIZE];
}

int main(){


	Map map(25);
	Gamer gamer;


	RenderWindow w(VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Minesweeper,Night of Sibirian Fairy Tale 2015");

	View w_start_size(w.getView().getCenter(),w.getView().getSize());

	w.setPosition( Vector2i(50,50) );
	// Main loop
	while(w.isOpen())
	{

		w.clear();
		Mouse mouse;
		Event event;
		Render_field(w,map,gamer);

		while(w.pollEvent(event))
		{

			//  if(event.type == Event::Resized)
			//    w.setView(w_start_size);
			//w.getView().setSize(25,25);


			if(event.type == Event::Closed)
				w.close();
			else
				if(event.type == Event::MouseButtonPressed  && gamer.isAlive())
				{

					Vector2i mouse_temp(mouse.getPosition());

					mouse.getPosition(w);
					fout <<"Mouse: " << mouse_temp.x <<"  " << mouse_temp.y <<std::endl;
					mouse_temp.x -= w.getPosition().x;
					mouse_temp.y -= w.getPosition().y;

					mouse_temp.x *= w.getViewport( w.getView() ).width/WINDOW_WIDTH;
					mouse_temp.y *= w.getViewport( w.getView() ).height/WINDOW_HEIGHT;

					fout << "Позиция окна: " << w.getPosition().x <<" "<<w.getPosition().y;
					if(Mouse::isButtonPressed(Mouse::Left))
						//left_mouse(mouse_temp,w);
						map.left_mouse_click(mouse_temp,gamer,w);
					else
						map.right_mouse_click(mouse_temp,gamer,w);

				}

		}





		w.display();


	}


	return 0;
}
