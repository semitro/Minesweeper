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

	if(_type == MINE)
		gamer.kill();
}
void Block::setType(Block_Type type){
	_type = type;
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
void Map::init_mines(){
	std::srand(std::time(NULL));
	int number_mines = _number_blocks/10; // Количество мин
	for(int i(0);i<number_mines;i++)
	{
		int elem = std::rand()%_number_blocks;
		if(_blocks[elem].type() == Block::MINE)
			_blocks[elem].setType(Block::MINE); // А-алгоритм
		else
			_blocks[std::rand()%_number_blocks].setType(Block::MINE);


	}

}

void Map::left_mouse_click(sf::Vector2i pos,Gamer &gamer,sf::RenderWindow &w)
{
	static bool first_click = true;
	if(first_click)
		Map::init_mines();
	first_click = false;
	getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).open(gamer); //Правильно

}
void Map::right_mouse_click(sf::Vector2i pos, Gamer &gamer, sf::RenderWindow &w)
{

	if(getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).isOpen())
		return;
	if( !getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).isFlag() ){
		gamer.lessFlag();
		getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).setFlag(true);
	}
	else{
		gamer.lessFlag(-1); // Отнимем минус один флаг, т.е, увеличим их к-во на один
		getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).setFlag(false);
	}
}

bool Gamer::isAlive(){
	return _alive;
}
void Gamer::kill()
{
	_alive = false;
}
void Gamer::lessFlag(int number)
{
	if(_flag_number - number >=0 )
		_flag_number -= number;
}
