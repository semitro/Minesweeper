#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
	//main code
	close();
		Map map(ui->spinBox_mines_number->text().toDouble());
		Gamer gamer;
		RenderWindow w(VideoMode(map.getSize()*BLOCK_RENDER_SIZE,map.getSize()*BLOCK_RENDER_SIZE),"Minesweeper,Night of Sibirian Fairy Tale 2015",sf::Style::Close);
		w.setPosition( Vector2i(50,50) );
		w.setVerticalSyncEnabled(true);//Вертикальная синхронизация
		while(w.isOpen())	// Main loop
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
						if(Mouse::isButtonPressed(Mouse::Left))
							map.left_mouse_click(mouse_temp,gamer,w);
						else
							if(Mouse::isButtonPressed(Mouse::Right))
							map.right_mouse_click(mouse_temp,gamer,w);
					}
			}//w.pollEvent
			w.display();
		}//main loop

}
