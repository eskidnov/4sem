#include <SFML\Graphics.hpp>
#include <vector>

// clusters
#include "Clasters.h"

int main() {
	sf::Texture texture;
	texture.loadFromFile("pic.png");
	auto im = texture.copyToImage();
	

	const int K = 16;
	const int iterationCount = 30;

	Centroids centroids = initializeCentroids(im, K);

	for (int it = 0; it < iterationCount; ++it) {
		ClosestCentroidIndices ids = findClosestCentroids(im, centroids);
		centroids = computeMeans(im, ids, K);
	}

	changeColors(im, centroids);

	im.saveToFile("Result.png");
	texture.update(im);


	sf::Sprite pic(texture);
	sf::RenderWindow window(sf::VideoMode(im.getSize().x, im.getSize().y), "");
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear(sf::Color::White);
		window.draw(pic);
		window.display();
	}

	return 0;
}
