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
				sf::CircleShape boid = sf::CircleShape(10.f, 3);

				// TODO: change origin if needed
				boid.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));
				boid.setFillColor(sf::Color::Green);

				// Add the boid
				m_boids.push_back(boid);
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

		// TODO: use sf::vertex in the end?
		for (const auto& boid : m_boids)
		{
			m_window.draw(boid);
		}

		m_window.display();
	}

}