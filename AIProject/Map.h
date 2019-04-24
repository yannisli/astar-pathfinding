#pragma once

#define MAX_WIDTH	512
#define MAX_HEIGHT	512
#define NODE_SIZE	2
class Map
{
public:
	Map();
	~Map();

	void SetObstructNode(int x, int y, bool state);

	bool IsNodeObstructed(int x, int y);

	
private:

	bool blockedNodes[MAX_WIDTH][MAX_HEIGHT];
};

