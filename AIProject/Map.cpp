#include "Map.h"



Map::Map()
{
	for (int x = 0; x < MAX_WIDTH; x++)
	{
		for (int y = 0; y < MAX_HEIGHT; y++)
		{
			this->blockedNodes[x][y] = false;
		}
	}

}


Map::~Map()
{

}

void Map::SetObstructNode(int x, int y, bool state)
{
	if (x < 0 || x >= MAX_WIDTH || y < 0 || y >= MAX_HEIGHT)
		return;
	this->blockedNodes[x][y] = state;
}

bool Map::IsNodeObstructed(int x, int y)
{
	return this->blockedNodes[x][y];
}