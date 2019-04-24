// AIProject.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <future>
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Pathfinding.h"


void findPath(int x, int y, Map* map, std::vector<sf::RectangleShape>* render) {
	render->clear();
	std::vector<int*> path = Pathfinding::FindPathToFrom(1, 1, x / NODE_SIZE, y / NODE_SIZE, *map);

	while (path.empty() == false)
	{
		int* cur = path.back();

		//std::cout << cur[0] << ", " << cur[1] << "\n";



		sf::RectangleShape rectangle;

		rectangle.setSize(sf::Vector2f(NODE_SIZE, NODE_SIZE));
		rectangle.setFillColor(sf::Color::Green);
		//rectangle.setOutlineThickness(1);
		rectangle.setPosition(sf::Vector2f(cur[0] * NODE_SIZE, cur[1] * NODE_SIZE));

		render->push_back(rectangle);

		delete cur;

		path.pop_back();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "A* Pathfinding");

	Map* map = new Map();

	

	std::vector<sf::RectangleShape> rectangles;

	std::thread t;
	for (int i = 0; i < 16384*4; i++)
	{
		int randomX = rand() % MAX_WIDTH;
		int randomY = rand() % MAX_HEIGHT;

		if (randomX == 1 && randomY == 1)
			continue;
		map->SetObstructNode(randomX, randomY, true);
		sf::RectangleShape rectangle;

		rectangle.setSize(sf::Vector2f(NODE_SIZE, NODE_SIZE));
		rectangle.setFillColor(sf::Color::Blue);
		rectangle.setPosition(sf::Vector2f(randomX * NODE_SIZE, randomY * NODE_SIZE));

		rectangles.push_back(rectangle);
	}

	std::vector<sf::RectangleShape> pathToRender;

	
	std::cout << "end\n";
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				t.detach();
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					
					if (t.joinable())
						t.join();
					
					t = std::thread(findPath, event.mouseButton.x, event.mouseButton.y, map, &pathToRender);;

					
				}
			}
		}

		window.clear();

		for each(sf::RectangleShape rect in rectangles)
		{
			window.draw(rect);
		}
		for(int i = 0; i < pathToRender.size(); i++)
		{
			sf::RectangleShape rect = pathToRender[i];
			window.draw(rect);
		}
		window.display();
	}

    return 0;
}

