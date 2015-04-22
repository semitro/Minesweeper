#include "logic.h"
//Gamer
bool Gamer::isAlive(){
	return _alive;
}
bool Gamer::isWinner(){
	return _winner;
}
void Gamer::kill(){
	_alive = false;
	static sf::Music boom;
	boom.openFromFile("Sounds/explosion.ogg");
	boom.play();
}
void Gamer::lessFlag(int number){
		_flag_number -= number;
}
void Gamer::youAreWin(){
	_winner = true;
}
int Gamer::getFlagsNumber(){
	return _flag_number;
}
//Block
bool Block::isOpen(void){
	return _open;
}
bool Block::Flag()
{
    return _flag;
}
void Block::open(Gamer &gamer)
{
	if(_flag)
		return; // Если поле с флагом - не откроем его никак

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
void Block::addMinesAround(int number){
	_mine_around += number;
}
int Block::getMinesAround(){
	return _mine_around;
}
Block::Block_Type Block::type()
{
	return _type;
}
//Map
Map::Map(int size):_minesIsInited(false){
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
	int elem = i*_size+j; // Массивушка-то одномерный!
		return _blocks[elem];
}
int Map::getNumberBlocks()
{
	return _number_blocks;
}
int Map::getSize(){
	return _size;
}
void Map::init_mines(){
	_minesIsInited = true;
	std::srand(std::time(NULL));
	int number_mines = (_number_blocks*1.2)/10+1; // Количество мин
	for(int i(0);i<number_mines;i++)
	{
		int elem = std::rand()%_number_blocks;
		if(_blocks[elem].type() != Block::MINE || !_blocks[elem].isOpen())
		{
			_blocks[elem].setType(Block::MINE); // А-алгоритм

			if(elem-_size>=0)
				_blocks[elem-_size].addMinesAround();

			if(elem+1 < _number_blocks && (elem+1)%_size!=0) // Не справа
				_blocks[elem+1].addMinesAround();

			if(elem-1 >= 0 && elem % _size !=0) // не слева
				_blocks[elem-1].addMinesAround();

			if(elem-_size-1 >= 0 && elem % _size !=0) //не слева
				_blocks[elem - _size-1].addMinesAround();

			if(elem + _size-1 < _number_blocks && elem % _size !=0) // Не слева
				_blocks[elem + _size-1].addMinesAround();

			if(elem+_size < _number_blocks)
				_blocks[elem + _size].addMinesAround();

			if(elem-_size+1 >=0 && (elem+1)%_size!=0) // Не справа
				_blocks[elem-_size+1].addMinesAround();

			if(elem + _size+1 < _number_blocks && (elem+1)%_size!=0) // Не справа
				_blocks[elem+_size+1].addMinesAround();

		}
		//else
		//	_blocks[std::rand()%_number_blocks].setType(Block::MINE);


	}
}
void Map::left_mouse_click(sf::Vector2i pos,Gamer &gamer,sf::RenderWindow &w){
	if(pos.y/BLOCK_RENDER_SIZE*_size + pos.x/BLOCK_RENDER_SIZE > _number_blocks) // Если клик за пределами поля
		return;
	//getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).open(gamer);
	openBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE,gamer);
	static bool first_click = true;
	if(first_click)
		Map::init_mines();
	first_click = false;
	if(win(gamer)){ // Проверяем, не достиг ли игрок победы этим ходом?
		gamer.youAreWin(); // Если достиг, то он победитель
	}
}
void Map::right_mouse_click(sf::Vector2i pos, Gamer &gamer, sf::RenderWindow &w){

	if(pos.y/BLOCK_RENDER_SIZE*_size + pos.x/BLOCK_RENDER_SIZE > _number_blocks) // Если клик за пределами поля
		return;
	if(getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).isOpen())
		return;

	if( !getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).Flag() ){ // Если флага нет
		gamer.lessFlag();
		getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).setFlag(true);
	}
	else{ // Если флаг есть
		gamer.lessFlag(-1); // Отнимем минус один флаг, т.е, увеличим их к-во на один
		getBlock(pos.y/BLOCK_RENDER_SIZE,pos.x/BLOCK_RENDER_SIZE).setFlag(false);

	}
	if(win(gamer)){ // Проверяем, не достиг ли игрок победы этим ходом?
		gamer.youAreWin(); // Если достиг, то он победитель
	}
}
void Map::openBlock(int elem, Gamer &gamer){
//	_blocks[elem].open(); // Доделать
}
void Map::openBlock(int i, int j, Gamer &gamer){
	getBlock(i,j).open(gamer);
//	int elem = i*_size +j; // Перевод в одномерное матричное исчисление
//	if(_blocks[elem].type() != Block::MINE || !_blocks[elem].isOpen()) // Додумать, доделать
//	{

//	if(elem-_size>=0 && _blocks[elem- size].getMinesAround() == 0)
//			openBlock();
//			_blocks[elem-_size].open(gamer);

//		if(elem+1 < _number_blocks && (elem+1)%_size!=0) // Не справа
//			_blocks[elem+1].addMinesAround();

//		if(elem-1 >= 0 && elem % _size !=0) // не слева
//			_blocks[elem-1].addMinesAround();

//		if(elem-_size-1 >= 0 && elem % _size !=0) //не слева
//			_blocks[elem - _size-1].addMinesAround();

//		if(elem + _size-1 < _number_blocks && elem % _size !=0) // Не слева
//			_blocks[elem + _size-1].addMinesAround();

//		if(elem+_size < _number_blocks)
//			_blocks[elem + _size].addMinesAround();

//		if(elem-_size+1 >=0 && (elem+1)%_size!=0) // Не справа
//			_blocks[elem-_size+1].addMinesAround();

//		if(elem + _size+1 < _number_blocks && (elem+1)%_size!=0) // Не справа
//			_blocks[elem+_size+1].addMinesAround();

//	}

}
bool Map::win(Gamer &gamer){
	if(gamer.getFlagsNumber()  < 0 || !_minesIsInited || !gamer.isAlive())
		return false;

		for(int i(0);i<_number_blocks;i++) //Если остались первозданные поля
			if( _blocks[i].isOpen() == false && _blocks[i].Flag() == false )
				return false; // Не победа то

		for(int i(0);i<_number_blocks;i++)
			if(_blocks[i].type() == Block::MINE && _blocks[i].Flag() == false ) // Если на поле с миной нет флага
					return false; // То не победа

		return true;
}
