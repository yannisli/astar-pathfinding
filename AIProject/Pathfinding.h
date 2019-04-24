#pragma once

#include <vector>
#include <queue>

#include "Map.h"


struct PathfindNode
{
	int f, g, h, x, y;
	PathfindNode* parent;
	
	PathfindNode(int x, int y, PathfindNode* parent)
	{
		this->x = x;
		this->y = y;
		this->parent = parent;
		this->f = 0;
		this->g = 0;
		this->h = 0;
	}

};

struct CompareNode {
	bool operator()(const PathfindNode* L, const PathfindNode* R) const
	{
		return L->f > R->f;
	}
};

class Pathfinding
{
public:
	static std::vector<int*> FindPathToFrom(int sx, int sy, int gx, int gy, Map inst);
private:
	Pathfinding();
};

