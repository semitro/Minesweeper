#include "logic.h"

void Block::setFlag(bool flag)
{
    _flag = flag;
}
bool Block::isFlag()
{
    return _flag;
}

Block Map::getBlock(int i)
{
   return _blocks[i];
}
int Map::getNumberBlocks()
{
	return _number_blocks;
}

bool Gamer::isAlive(){
	return _alive;
}
