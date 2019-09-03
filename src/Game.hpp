#pragma once

#include <SFML/Graphics.hpp>

#define WIDTH 600U
#define HEIGHT 480U
#define BOID_SIZE 10.f

namespace fb
{
	class Game
	{
	public:
		Game();

		void run();

	private:
		void render();
		void pollEvents();
		void update(sf::Time dt);

		sf::RenderWindow m_window;
		std::vector<sf::Vertex> m_boids;
	};
}