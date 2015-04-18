#include "logic.h"

void Block::setFlag(bool flag)
{
    _flag = flag;
}
bool Block::isFlag()
{
    return _flag;
}
void Block::open(Gamer &gamer)
{

	if(_flag == false)
		_open = true;
	if(_open && _type == MINE)
		gamer.kill();
}

Block &Map::getBlock(int number)
{
   return _blocks[number];
}
Block& Map::getBlock(int i, int j)
{
	// Подумать
	int elem = i*_size+j;
//	qDebug() << "\nnumber: " << elem;
	if(elem < _number_blocks)
		return _blocks[elem];
	else
		throw("Map: getBlock(i,j): out of range!");
}

int Map::getNumberBlocks()
{
	return _number_blocks;
}
int Map::getSize(){
	return _size;
}
void Map::left_mouse_click(sf::Vector2i pos,Gamer &gamer,sf::RenderWindow &w)
{


		//if(!getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).isFlag()) // Открываем поле без флага
		//{
			//if(getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).type() == Block::MINE)
			//	gamer.kill();

			getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).open(gamer); //Правильноы
			//qDebug() << "y: "<<pos.y / BLOCK_RENDER_SIZE << " pos.x / r.s"<< pos.x / BLOCK_RENDER_SIZE << endl;
		//}

}

bool Gamer::isAlive(){
	return _alive;
}
void Gamer::kill()
{
	_alive = false;
}
