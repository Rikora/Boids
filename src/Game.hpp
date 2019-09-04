#pragma once

#include <SFML/Graphics.hpp>

#define WIDTH 600U
#define HEIGHT 480U
#define BOID_SIZE 10.f
#define BOID_VELOCITY 50.f
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

		// Rules
		sf::Vector2f computeAlignment(const Boid& targetBoid);
		sf::Vector2f computeCohesion(const Boid& targetBoid);
		sf::Vector2f computeSeparation(const Boid& targetBoid);

		sf::RenderWindow m_window;
		//std::vector<sf::Vertex> m_boids;
		std::vector<Boid> m_boids;
	};
}