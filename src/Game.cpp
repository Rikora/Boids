#include "Game.hpp"

namespace fb
{
	Game::Game() : 
	m_window(sf::VideoMode(WIDTH, HEIGHT), "Boids", sf::Style::Close, sf::ContextSettings(0, 0, 8))
	{
		m_window.setVerticalSyncEnabled(true);
	}

	void Game::run()
	{
		sf::Clock clock;

		while (m_window.isOpen())
		{
			pollEvents();
			update(clock.restart());
			render();
		}
	}

	void Game::pollEvents()
	{
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				auto pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
				
				// Construct triangle (boid) from position
				m_boids.push_back(sf::Vertex(sf::Vector2f(pos.x - BOID_SIZE, pos.y), sf::Color::Green));
				m_boids.push_back(sf::Vertex(sf::Vector2f(pos.x, pos.y - BOID_SIZE), sf::Color::Green));
				m_boids.push_back(sf::Vertex(sf::Vector2f(pos.x + BOID_SIZE, pos.y), sf::Color::Green));
			}


			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				m_window.close();
			}
		}
	}

	void Game::update(sf::Time dt)
	{
		// Do nothing by default...
	}

	void Game::render()
	{
		m_window.clear();

		// Draw boids
		m_window.draw(m_boids.data(), m_boids.size(), sf::Triangles);

		m_window.display();
	}

}