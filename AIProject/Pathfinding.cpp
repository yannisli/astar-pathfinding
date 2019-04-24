#include "Pathfinding.h"

#include <iostream>
#include <stdio.h>

// Find a path to Node at [gx, gy] from starting point [sx, sy] and return a Vector of int arrays containing x and y at 0, 1 index
std::vector<int*> Pathfinding::FindPathToFrom(int sx, int sy, int gx, int gy, Map inst)
{	
	// Return path
	std::vector<int*> returnPath;
	// Check to see if the goal is obstructed first, if it is then there will be no path
	if (inst.IsNodeObstructed(gx, gy))
		return returnPath;
	// Priority queue
	std::priority_queue<PathfindNode*, std::vector<PathfindNode*>, CompareNode> openSet;

	// Closed set
	bool closedNodes[MAX_WIDTH][MAX_HEIGHT];


	
	// Start node
	PathfindNode* start = new PathfindNode(sx, sy, nullptr);
	
	start->f = abs(gx - sx) + abs(gy - sy);
	start->parent = nullptr;
	// Push to open set
	openSet.push(start);
	// Start looping
	while (!openSet.empty())
	{
		// Current node we're looking at
		PathfindNode* current = openSet.top();
		
		// Debug stuff ovo
		//std::cout << current->x << ", " << current->y << "\n";

		//std::cout << start->parent << "\n";
		//std::cout << current->parent << "\n";
		
		// If current node is the goal
		if (current->x == gx && current->y == gy)
		{
			// Reconstructerino path
			std::cout << "Found the goal\n";

			PathfindNode* parent = current;
			// Trace back until we get to start node (it has no parent)
			while (parent != nullptr)
			{
				//std::cout << "Add " << cur->x << ", " << cur->y << "\n";

				// Add current node position to the return path
				int* pos = new int[2];
				pos[0] = parent->x;
				pos[1] = parent->y;

				returnPath.push_back(pos);

				parent = parent->parent;
			}
			
		

			break;
		}
		else
		{
			// Remove from open set
			openSet.pop();
			// Change to closed set
			closedNodes[current->x][current->y] = true;
			// Debug stuff
			//std::cout << "Looking at " << current->x << ", " << current->y << "\n";
			//std::cout << "This has an F score of " << current->f << "\n";
			/*if(current->parent != nullptr)
				std::cout << "The parent has coords of " << current->parent->x << ", " << current->parent->y << "\n";*/
			// Find neighbours around
			for (int x = -1; x < 2; x++)
			{
				for (int y = -1; y < 2; y++)
				{
					int cx = current->x + x;
					int cy = current->y + y;

					//std::cout << cx << ", " << cy << "\n";

					// Make sure not out of bounds of map
					if (cx < 0 || cx >= MAX_WIDTH || cy < 0 || cy >= MAX_HEIGHT)
						continue;
					// Make sure we're not looking at the current node
					if (cx == current->x && cy == current->y)
						continue;
					// Is this neighbor node obstructed?
					if (inst.IsNodeObstructed(cx, cy))
						continue;
					// Was this already checked previously
					if (closedNodes[cx][cy] == true)
						continue;

					//std::cout << "Push?\n";

					// Calculate total combined score
					PathfindNode* tentative = new PathfindNode(cx, cy, current);
					// Movement cost is previous node + 1
					tentative->g = current->g + 1;
					// Heuristic cost
					tentative->h = abs(gx - cx) + abs(gy - cy);
					// Combined cost
					tentative->f = tentative->g + tentative->h;
					// Parent node of this node is the previous one
					tentative->parent = current;
					// Add to open set
					openSet.push(tentative);
				}
			}
		}
	}

	while (!openSet.empty())
	{
		delete openSet.top();

		openSet.pop();
	}

	delete start;
	// return the found path
	return returnPath;
}