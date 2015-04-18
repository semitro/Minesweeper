#ifndef LOGIC_H
#define LOGIC_H
//Непосредственно логика игры
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <qdebug.h>
#define BLOCK_RENDER_SIZE 32
class Gamer
{
public:
	Gamer():_alive(true){}
	bool isAlive();
	void kill();
private:
	bool _alive;
};

class Block{
public:
    enum Block_Type{ // Что таит одна клетка?
        EMPTY_, // Без мины / флага
        MINE // Поле с миной
    };
	Block(int i=0, int j=0,Block_Type type=EMPTY_):
		_i(i), _j(j), _type(type), _open(false), _flag(false)
	{

	}
    int getI(void){
        return _i;
    }
    int getJ(void){
     return _j;
    }
    Block_Type type()
    {
        return _type;
    }
    bool isOpen(void){
        return _open;
    }
    bool isFlag(void);
    void setFlag(bool flag=true);
	void open(Gamer &gamer);

private:
    int _i; // Позиция блока в большом поле
    int _j;
    Block_Type _type;
    bool _open;
    bool _flag;
};
class Map // Всё поле
{
public:
    Map(int size=20){
        _size = size;
        _number_blocks = size*size;
        _blocks = new Block[_number_blocks];
        for(int i(0);i < size;i++)
            for(int j(0); j< size; j++)
                 _blocks[i] = Block(i,j);
    }
    ~Map(){
        delete[] _blocks;
    }
	int getSize();
	int getNumberBlocks();
	Block& getBlock(int number);
	Block& getBlock(int i, int j);
	void left_mouse_click(sf::Vector2i pos, Gamer &gamer, sf::RenderWindow &w);
private:
    Block *_blocks; //Динамический массив для хранения клеток поля
	int _number_blocks; // Количество клеток поля
    int _size; // Количество клеток (не в квадрате)
};

#endif // LOGIC_H

