#include "Game.hpp"

namespace fb
{
	Game::Game() : 
	m_window(sf::VideoMode(WIDTH, HEIGHT), "Boids", sf::Style::Close),
	m_circle(10.f)
	{
		m_window.setVerticalSyncEnabled(true);

		m_circle.setPosition(sf::Vector2f(100.f, 100.f));
		m_circle.setFillColor(sf::Color::Green);
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
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				m_window.close();
			}
		}
	}

	void Game::update(sf::Time dt)
	{	
	}

	void Game::render()
	{
		m_window.clear();

		m_window.draw(m_circle);

		m_window.display();
	}

}