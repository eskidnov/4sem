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
			if (E.charges[i].value < 0) {
				minus.setPosition(E.charges[i].pos.x, E.charges[i].pos.y);
				window.draw(minus);
			}
			if (E.charges[i].value > 0) {
				plus.setPosition(E.charges[i].pos.x, E.charges[i].pos.y);
				window.draw(plus);
			}

			Charge q1, q2, q3, q4;
			q1 = q2 = q3 = q4 = E.charges[i];
			q1.pos += Vector2(plusSize.x / 2, 0);
			q2.pos += Vector2(0, plusSize.y / 2);
			q3.pos += Vector2(-(int)(plusSize.x / 2), 0);
			q4.pos += Vector2(0, -(int)(plusSize.y / 2));
			
			for (auto k = 0; k < 2000; ++k) {

				//LineOfForce lof;
				//lof.positiveBranch.push_back(E.findForce(q1).norm());
				//lof.negativeBranch.push_back(-E.findForce(q).norm());
				//E.lines.push_back(lof);

				Vector2 F1 = E.findForce(q1).norm();
				Vector2 F2 = E.findForce(q2).norm();
				Vector2 F3 = E.findForce(q3).norm();
				Vector2 F4 = E.findForce(q4).norm();

				sf::Vertex line1[] = {
					sf::Vertex(sf::Vector2f(q1.pos.x, q1.pos.y)),
					sf::Vertex(sf::Vector2f(q1.pos.x + F1.x, q1.pos.y + F1.y))
				};
				q1.pos += F1;
				window.draw(line1, 2, sf::Lines);

				sf::Vertex line2[] = {
					sf::Vertex(sf::Vector2f(q2.pos.x, q2.pos.y)),
					sf::Vertex(sf::Vector2f(q2.pos.x + F2.x, q2.pos.y + F2.y))
				};
				q2.pos += F2;
				window.draw(line2, 2, sf::Lines);

				sf::Vertex line3[] = {
					sf::Vertex(sf::Vector2f(q3.pos.x, q3.pos.y)),
					sf::Vertex(sf::Vector2f(q3.pos.x + F3.x, q3.pos.y + F3.y))
				};
				q3.pos += F3;
				window.draw(line3, 2, sf::Lines);

				sf::Vertex line4[] = {
					sf::Vertex(sf::Vector2f(q4.pos.x, q4.pos.y)),
					sf::Vertex(sf::Vector2f(q4.pos.x + F4.x, q4.pos.y + F4.y))
				};
				q4.pos += F4;
				window.draw(line4, 2, sf::Lines);
			}
		}
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