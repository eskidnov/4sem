#include "main.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	sf::Texture plusImg, minusImg;
	ElectricField E;
	Charge Q;

	plusImg.loadFromFile("plus.png");
	sf::Sprite plus(plusImg);
	sf::Vector2u plusSize = plus.getTexture()->getSize();
	plus.setOrigin(plusSize.x / 2, plusSize.y / 2);

	minusImg.loadFromFile("minus.png");
	sf::Sprite minus(minusImg);
	sf::Vector2u minusSize = minus.getTexture()->getSize();
	minus.setOrigin(minusSize.x / 2, minusSize.y / 2);

	Q.value = 1;
	Q.pos = Vector2(0, 0);
	bool f = false;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Right) {
						Charge q;
						q.value = -1;
						q.pos = Vector2(event.mouseButton.x, event.mouseButton.y);
						E.charges.push_back(q);
					}
					if (event.mouseButton.button == sf::Mouse::Left) {
						Charge q;
						q.value = 1;
						q.pos = Vector2(event.mouseButton.x, event.mouseButton.y);
						E.charges.push_back(q);
						f = true;
					}
					break;

				default:
					break;
			}
			
		}


		window.clear(sf::Color::Black);

		for (auto i = 0; i < E.charges.size(); ++i) {
			Charge q[LINES_NUMBER];
			for (auto j = 0; j < LINES_NUMBER; ++j) {
				q[j] = E.charges[i];
				q[j].pos += Vector2(((float) plusSize.x) / 2 * cos((float)j / LINES_NUMBER * 3.14 * 2),
								   ((float) plusSize.y) / 2 * sin((float)j / LINES_NUMBER * 3.14 * 2));
			}
			
			/* что за магическое число 100? */
			for (auto k = 0; k < 1000; ++k) {
				Vector2 F[LINES_NUMBER];

				for (auto j = 0; j < LINES_NUMBER; ++j) {
					F[j] = E.findForce(q[j]).norm();

					sf::Vertex line[] = {
						sf::Vertex(sf::Vector2f(q[j].pos.x, q[j].pos.y)),
						sf::Vertex(sf::Vector2f(q[j].pos.x + F[j].x, q[j].pos.y + F[j].y))
					};
					q[j].pos += F[j];
					window.draw(line, 2, sf::Lines);
				}
			}

			if (E.charges[i].value < 0) {
				minus.setPosition(E.charges[i].pos.x, E.charges[i].pos.y);
				window.draw(minus);
			}
			if (E.charges[i].value > 0) {
				plus.setPosition(E.charges[i].pos.x, E.charges[i].pos.y);
				window.draw(plus);
			}
		}
				//LineOfForce lof;
				//lof.positiveBranch.push_back(E.findForce(q1).norm());
				//lof.negativeBranch.push_back(-E.findForce(q).norm());
				//E.lines.push_back(lof);
		/*for (auto i = 0; i < 200; ++i) {
			//if (f) std::cout << E.charges[0].pos << "\n";

			q1.pos += lof.positiveBranch[i];
			window.draw(positiveLine, 2, sf::Lines);

			sf::Vertex negativeLine[] = {
				sf::Vertex(sf::Vector2f(q2.pos.x, q2.pos.y)),
				sf::Vertex(sf::Vector2f(q2.pos.x + lof.negativeBranch[i].x, q2.pos.y + lof.negativeBranch[i].y))
			};
			q2.pos += lof.negativeBranch[i];
			window.draw(negativeLine, 2, sf::Lines);
		}*/
		window.display();
	}
	return 0;
}
