#include "logic.h"
//Gamer
bool Gamer::isAlive(){
	return _alive;
}
void Gamer::kill(){
	_alive = false;
}
void Gamer::lessFlag(int number){
	if(_flag_number - number >=0 )
		_flag_number -= number;
}
//Block
bool Block::isOpen(void){
	return _open;
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
void Block::setFlag(bool flag){
	_flag = flag;
}
Block::Block_Type Block::type()
{
	return _type;
}
//Map
Map::Map(int size){
	_size = size;
	_number_blocks = size*size;
	_blocks = new Block[_number_blocks];
	for(int i(0);i < size;i++)
		for(int j(0); j< size; j++)
			 _blocks[i] = Block(i,j);
}
Map::~Map(){
	delete[] _blocks;
}
Block& Map::getBlock(int number)
{
   return _blocks[number];
}
Block& Map::getBlock(int i, int j){
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

void Map::left_mouse_click(sf::Vector2i pos,Gamer &gamer,sf::RenderWindow &w){
	getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).open(gamer);
	// Чтобы мины инициализировались только после первого клика
	static bool first_click = true;
	if(first_click)
		Map::init_mines();
	first_click = false;
}
void Map::right_mouse_click(sf::Vector2i pos, Gamer &gamer, sf::RenderWindow &w){
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
