#pragma once

#include <SFML/Graphics.hpp>

#define WIDTH 1000U
#define HEIGHT 600U
#define BOID_SIZE 7.f
#define BOID_VELOCITY 30.f
#define BOID_RADIUS 100.f

namespace fb
{
	struct Boid
	{
		Boid(const sf::CircleShape& body, const sf::Vector2f& velocity = sf::Vector2f(BOID_VELOCITY, BOID_VELOCITY)) : 
			body(body), velocity(velocity) {}

		sf::CircleShape body;
		sf::Vector2f velocity;
	};

	class Game
	{
	public:
		Game();

		void run();

	private:
		void render();
		void pollEvents();
		void update(sf::Time dt);
		void checkBoundaries(Boid& boid);

		// Rules
		sf::Vector2f alignment(const Boid& targetBoid);
		sf::Vector2f cohesion(const Boid& targetBoid);
		sf::Vector2f separation(const Boid& targetBoid);

		sf::RenderWindow m_window;
		std::vector<Boid> m_boids;
	};
}