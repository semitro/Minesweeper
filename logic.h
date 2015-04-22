#ifndef LOGIC_H
#define LOGIC_H
//Непосредственно логика игры
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <time.h>
#include <qdebug.h>
#define BLOCK_RENDER_SIZE 32
class Gamer
{
public:
	Gamer(int flag_number=20):_alive(true), _flag_number(flag_number),_winner(false){}
	bool isAlive();
	bool isWinner();
	void kill();
	void youAreWin();
	void lessFlag(int number=1);
	int getFlagsNumber();
private:
	bool _alive;
	bool _winner;// Победил уже?
	int _flag_number;
};
class Block{
public:
    enum Block_Type{ // Что таит одна клетка?
		EMPTY_, // Без мины
		MINE // Поле с миной
    };
	Block(int i=0, int j=0,Block_Type type=EMPTY_):
		_i(i), _j(j), _type(type), _open(false), _flag(false),_mine_around(0)
	{}

	Block_Type type();
	bool isOpen(void);
	bool Flag(void);
	void setType(Block_Type type);
	void setFlag(bool flag=true);
	void addMinesAround(int number=1);
	void open(Gamer &gamer);
	int getMinesAround();

private:
    int _i; // Позиция блока в большом поле
	int _j; // Честно говоря, нахрен не нужна
    Block_Type _type;
    bool _open;
    bool _flag;
	int _mine_around; // Сколько мин в соседних блоках?
};
class Map // Всё поле
{
public:
	Map(int size=20);
	~Map();
	int getSize();
	int getNumberBlocks();
	Block& getBlock(int number);
	Block& getBlock(int i, int j);
	void init_mines();
	void left_mouse_click(sf::Vector2i pos, Gamer &gamer, sf::RenderWindow &w);
	void right_mouse_click(sf::Vector2i pos, Gamer &gamer, sf::RenderWindow &w);
	bool win(Gamer &gamer);
private:
	void openBlock(int i, int j,Gamer &gamer);
	void openEmptyBlocksAround(int elem,Gamer &gamer);
    Block *_blocks; //Динамический массив для хранения клеток поля
	int _number_blocks; // Количество клеток поля
    int _size; // Количество клеток (не в квадрате)
	bool _minesIsInited; // Проинициализированы ли уже мины? (Фиксит баг с победой при первом ходе)
};

#endif // LOGIC_H

