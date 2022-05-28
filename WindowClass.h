#pragma once

#include <SFML/Graphics.hpp>
#include "TriangleClass.h"
class Window {

	sf::RenderWindow* window = nullptr;
	CAP::RenderMap *map;
	sf::VertexArray vertexarray;

	void update()
	{
		
		map->Rotate(0.001, 0, 0);
		map->MoveBy(0, 1, 0);
		for (int i = 0; i < map->vertices; i++)
		{
			sf::Vertex* vertex = &vertexarray[i * 3];
			for (int j = 0; j < 3; j++)
			{
				vertex[j].position = sf::Vector2f(map->triangles[i].corners[j].x, map->triangles[i].corners[j].y);

			}
		}
		


		window->clear();
		window->draw(vertexarray);
		window->display();
	}

	void close() {

		delete window;
	}

	void loop()
	{
		sf::Event event;
		while (window->isOpen())
		{
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();

				}


			}
			update();


		}
		close();


	}


public:


	void start(unsigned int Width, unsigned int Height, const char* Title)
	{

		window = new sf::RenderWindow(sf::VideoMode(Width, Height), Title);
		window->setFramerateLimit(144);

	
		map = new CAP::RenderMap(20, 20);


		vertexarray.setPrimitiveType(sf::Triangles);
		vertexarray.resize(map->vertices * 3);

		for (int i = 0; i < map->vertices; i++)
		{
			vertexarray[i * 3].color = sf::Color::Red;
			vertexarray[i * 3 + 1].color = sf::Color::Blue;
			vertexarray[i * 3 + 2].color = sf::Color::Green;

		}
		map->MoveBy(100, 100, 0);



		loop();

	}

};