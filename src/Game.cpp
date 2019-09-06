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
			}

			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				m_window.close();
			}
		}
	}

	void Game::update(sf::Time dt)
	{	
		// Update boids
		for (auto& boid : m_boids)
		{			
			checkBoundaries(boid);

			// Add the rules to the velocity of the boid
			boid.velocity += 0.01f * cohesion(boid) + 0.8f * alignment(boid) + separation(boid);
			boid.velocity = utils::normalize(boid.velocity) * BOID_VELOCITY * dt.asSeconds();

			boid.body.setPosition(boid.body.getPosition() + boid.velocity);
		}
	}

	void Game::render()
	{
		m_window.clear();

		// Draw boids
		for (const auto& boid : m_boids)
		{
			m_window.draw(boid.body);
		}

		m_window.display();
	}

	void Game::checkBoundaries(Boid& boid)
	{
		// Reset position of a boid if it's outside the window
		if (boid.body.getPosition().x > static_cast<float>(WIDTH + 10))
		{
			boid.body.setPosition(0.f, boid.body.getPosition().y);
		}
		else if (boid.body.getPosition().x < 0.f)
		{
			boid.body.setPosition(static_cast<float>(WIDTH), boid.body.getPosition().y);
		}

		if (boid.body.getPosition().y > static_cast<float>(HEIGHT + 10))
		{
			boid.body.setPosition(boid.body.getPosition().x, 0.f);
		}
		else if (boid.body.getPosition().y < 0.f)
		{
			boid.body.setPosition(boid.body.getPosition().x, static_cast<float>(HEIGHT));
		}
	}

	// Rule 1: alignment
	sf::Vector2f Game::alignment(const Boid& targetBoid)
	{
		sf::Vector2f v = sf::Vector2f(0.f, 0.f);
		int neighbors = 0;

		for (const auto& boid : m_boids)
		{
			if (boid.body.getPosition() != targetBoid.body.getPosition())
			{
				v += boid.velocity;
				neighbors++;
			}
		}

		if (neighbors == 0)
		{
			return sf::Vector2f(0.f, 0.f);
		}

		// Direction vector to nearby boids
		v /= static_cast<float>(neighbors);
		v = utils::normalize(v);

		return v;
	}

	// Rule 2: cohesion
	sf::Vector2f Game::cohesion(const Boid& targetBoid)
	{
		sf::Vector2f v = sf::Vector2f(0.f, 0.f);
		int neighbors = 0;

		for (const auto& boid : m_boids)
		{
			if (boid.body.getPosition() != targetBoid.body.getPosition())
			{
				v += boid.body.getPosition();
				neighbors++;
			}
		}

		if (neighbors == 0)
		{
			return sf::Vector2f(0.f, 0.f);
		}

		// Direction vector towards the center of mass
		v /= static_cast<float>(neighbors);
		v -= targetBoid.body.getPosition();
		v = utils::normalize(v);

		return v;
	}

	// Rule 3: separation
	sf::Vector2f Game::separation(const Boid& targetBoid)
	{
		sf::Vector2f v = sf::Vector2f(0.f, 0.f);
		int neighbors = 0;

		for (const auto& boid : m_boids)
		{
			if (boid.body.getPosition() != targetBoid.body.getPosition())
			{
				if (utils::distance(targetBoid.body.getPosition(), boid.body.getPosition()) < BOID_RADIUS)
				{
					v -= boid.body.getPosition() - targetBoid.body.getPosition();
					neighbors++;
				}
			}
		}

		if (neighbors == 0)
		{
			return sf::Vector2f(0.f, 0.f);
		}

		v = utils::normalize(v);

		return v;
	}
}