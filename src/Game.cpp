#include "Game.hpp"
#include "utils/Utility.hpp"

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
				sf::CircleShape body = sf::CircleShape(BOID_SIZE, 3);
				utils::centerOrigin(body);
				body.setPosition(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
				body.setFillColor(sf::Color::Green);

				m_boids.push_back(Boid(body));

				//const auto pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

				//// Construct triangle (boid) from position
				//m_boids.push_back(sf::Vertex(sf::Vector2f(pos.x - BOID_SIZE, pos.y), sf::Color::Green));
				//m_boids.push_back(sf::Vertex(sf::Vector2f(pos.x, pos.y - BOID_SIZE), sf::Color::Green));
				//m_boids.push_back(sf::Vertex(sf::Vector2f(pos.x + BOID_SIZE, pos.y), sf::Color::Green));
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
		for (const auto& boid : m_boids)
		{
			m_window.draw(boid.body);
		}

		//m_window.draw(m_boids.data(), m_boids.size(), sf::Triangles);

		m_window.display();
	}

	sf::Vector2f Game::computeAlignment(const Boid& targetBoid)
	{
		sf::Vector2f v = sf::Vector2f(0.f, 0.f);
		int neighbors = 0;

		for (const auto& boid : m_boids)
		{
			if (boid.body.getPosition() != targetBoid.body.getPosition())
			{
				if (utils::distance(targetBoid.body.getPosition(), boid.body.getPosition()) < BOID_RADIUS)
				{
					v += boid.velocity;
					neighbors++;
				}
			}
		}

		// Return null vector
		if (neighbors == 0)
		{
			return v;
		}

		// Direction vector to nearby boids
		v /= static_cast<float>(neighbors);
		v = utils::normalize(v);

		return v;
	}

	sf::Vector2f Game::computeCohesion(const Boid& targetBoid)
	{
		sf::Vector2f v = sf::Vector2f(0.f, 0.f);
		int neighbors = 0;

		for (const auto& boid : m_boids)
		{
			if (boid.body.getPosition() != targetBoid.body.getPosition())
			{
				if (utils::distance(targetBoid.body.getPosition(), boid.body.getPosition()) < BOID_RADIUS)
				{
					v += boid.body.getPosition();
					neighbors++;
				}
			}
		}

		// Return null vector
		if (neighbors == 0)
		{
			return v;
		}

		// Direction vector towards the center of mass
		v /= static_cast<float>(neighbors);
		v -= targetBoid.body.getPosition();
		v = utils::normalize(v);

		return v;
	}

	sf::Vector2f Game::computeSeparation(const Boid& targetBoid)
	{
		sf::Vector2f v = sf::Vector2f(0.f, 0.f);
		int neighbors = 0;

		for (const auto& boid : m_boids)
		{
			if (boid.body.getPosition() != targetBoid.body.getPosition())
			{
				if (utils::distance(targetBoid.body.getPosition(), boid.body.getPosition()) < BOID_RADIUS)
				{
					v += boid.body.getPosition() - targetBoid.body.getPosition();
					neighbors++;
				}
			}
		}

		// Return null vector
		if (neighbors == 0)
		{
			return v;
		}

		// Direction vector away from the nearby boids
		v /= static_cast<float>(neighbors);
		v *= -1.f;
		v = utils::normalize(v);

		return v;
	}
}