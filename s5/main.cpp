#include <SFML\Graphics.hpp>
#include "Vector2.h"
#include "Figures.h"
#include <vector>

Vector2 GetDeltaP(Ball ball1, Ball ball2) {
	Vector2 d;

	d = ball1.position - ball2.position;

	if (d.len() <= ball1.radius + ball2.radius && (ball1.velocity - ball2.velocity) * d <= 0) {
		return (2 * (ball1.velocity - ball2.velocity) / (1 / ball1.mass + 1 / ball2.mass) * d.norm()) * d.norm();
	}
	else
		return Vector2(0, 0);
}

int main() {
	const int windowX = 800, windowY = 600;
	std::vector<Ball> balls;
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "My window");
	sf::Clock clock;
	float dt, t0 = 0;

	while (window.isOpen()) {
		sf::Event event;
		sf::Time t = clock.getElapsedTime();
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left) {
						Ball ball;
						ball.position = Vector2(event.mouseButton.x, event.mouseButton.y);
						ball.radius = rand() % 30 + 25;
						ball.mass = ball.radius / 5;
						balls.push_back(ball);
					}
					break;
			}
		}
		window.clear(sf::Color::White);

		dt = t.asSeconds() - t0;
		t0 = t.asSeconds();

		for (auto i = 0; i < balls.size(); ++i) {
			sf::CircleShape ball(balls[i].radius);
			ball.setFillColor(sf::Color::Black);
			ball.setOrigin(balls[i].radius, balls[i].radius);
			ball.setPosition(balls[i].position.x, balls[i].position.y);
			window.draw(ball);
			balls[i].UpdatePosition(dt);

			if (balls[i].position.x - balls[i].radius <= 0 || balls[i].position.x + balls[i].radius > windowX) {
				balls[i].velocity.x *= -1;
			}
			if (balls[i].position.y - balls[i].radius <= 0 || balls[i].position.y + balls[i].radius > windowY) {
				balls[i].velocity.y *= -1;
			}

			for (auto j = 0; j < balls.size(); ++j) {
				if (i != j) {
					Vector2 dp;
					dp = GetDeltaP(balls[i], balls[j]);
					balls[j].velocity += dp / balls[j].mass;
					balls[i].velocity -= dp / balls[i].mass;
				}
			}
		}

		window.display();
	}
	return 0;
}